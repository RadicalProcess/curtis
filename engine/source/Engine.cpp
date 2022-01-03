#include "Engine.h"
#include "VisualizationData.h"
#include "Constants.h"

namespace rp::trevor
{
    Engine::Engine(size_t id, size_t timeout, float sampleRate, size_t blockSize, const IFactory& factory)
    : id_(id)
    , sampleRate_(sampleRate)
    , dryGain_(0.0f)
    , wetGain_(1.0f)
    , zeroXProcessor_(factory.createZeroXProcessor(timeout))
    , phasorProcessor_(factory.createPhasorProcessor())
    , additiveProcessor_(factory.createAdditiveProcessor())
    , holdProcessor_(factory.createHoldProcessor())
    , inputDelayProcessor_(factory.createDelayProcessor(timeout))
    , dryDelayProcessor_(factory.createDelayProcessor(timeout))
    , zeroXDelayProcessor_(factory.createDelayProcessor(timeout))
    , visualizerData_(blockSize)
    , visualizationCache_(factory.createVisualizationCache(timeout, Constants::visualDataSize))
    , bufferForDrySignal_(blockSize)
    , bufferForDelay_(blockSize)
    , bufferForHold_(blockSize)
    , sampleCapacitor_(blockSize,
    [this](Buffer& inputBuffer){
            inputDelayProcessor_->process(inputBuffer);
            bufferForDrySignal_ = inputBuffer;
            zeroXProcessor_->process(inputBuffer);
            bufferForHold_ = inputBuffer;
            bufferForDelay_ = inputBuffer;
            zeroXDelayProcessor_->process(bufferForDelay_);
            visualizerData_.zeroCrosses = bufferForDelay_;
            phasorProcessor_->process(inputBuffer);
            additiveProcessor_->process(inputBuffer);
            holdProcessor_->process(bufferForHold_);
            inputBuffer.multiply(bufferForHold_);
            visualizerData_.generated = inputBuffer;
            dryDelayProcessor_->process(bufferForDrySignal_);
            visualizerData_.original = bufferForDrySignal_;
            for(auto i = 0; i < inputBuffer.size(); ++i)
                inputBuffer[i] = inputBuffer[i] * wetGain_ + bufferForDrySignal_[i] * dryGain_;
            visualizerData_.mixed = inputBuffer;
            visualizationCache_->push(visualizerData_);
    })
    {
        visualizationCache_->addListener(this);
    }

    Engine::~Engine()
    {
        visualizationCache_->removeListener(this);
    }

    void Engine::process(float* buffer, size_t size)
    {
        auto&& inputBuffer = Buffer(buffer, size);
        sampleCapacitor_.process(inputBuffer);
    }

    float Engine::getSampleRate() const
    {
        return sampleRate_;
    }

    IZeroXProcessor& Engine::getZeroXProcessor()
    {
        return *zeroXProcessor_;
    }

    IAdditiveProcessor& Engine::getAdditiveProcessor()
    {
        return *additiveProcessor_;
    }

    IPhasorProcessor& Engine::getPhasorProcessor()
    {
        return *phasorProcessor_;
    }

    IHoldProcessor& Engine::getHoldProcessor()
    {
        return *holdProcessor_;
    }

    void Engine::setDryGain(float gain)
    {
        dryGain_ = gain;
    }

    void Engine::setWetGain(float gain)
    {
        wetGain_ = gain;
    }

    void Engine::addListener(IEngine::Listener* listener)
    {
        listeners_.insert(listener);
    }

    void Engine::removeListener(IEngine::Listener* listener)
    {
        listeners_.erase(listener);
    }

    void Engine::onCacheFilled(const VisualizationData& data)
    {
        for(auto* listener: listeners_)
            listener->onVisualizationDataFilled(id_, data);
    }
}
