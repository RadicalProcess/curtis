#include "EngineManager.h"

#include <memory>
#include "ParameterSpecSet.h"
#include "Consts.h"

namespace rp::curtis
{
    EngineManager::EngineManager(float sampleRate, size_t blockSize, size_t visualizationCacheSize)
    : visualizationDataSets_(Consts::visualizerDataSize, {0.f, 0.f, 0.f, 0.f, false})
    , curtis_(std::make_unique<Curtis>(sampleRate, blockSize, visualizationCacheSize))
    , visualizationDataCompressor_(Consts::visualizerDataSize)
    {
        curtis_->addListener(this);
    }

    EngineManager::~EngineManager()
    {
        curtis_->removeListener(this);
    }

    void EngineManager::process(float** buffer, size_t size)
    {
        updateParameters();
        auto leftBuffer = curtis::Buffer(buffer[0], size);
        auto rightBuffer = curtis::Buffer(buffer[1], size);
        curtis_->process(leftBuffer, rightBuffer);
    }

    void EngineManager::setParameter(size_t id, float value)
    {
        messageQueue_.push(Message{id, value});
    }

    void EngineManager::updateParameters()
    {
        messageQueue_.consume_all([this](Message& message)
        {
            auto itr = std::find_if(parameterSpecSet.begin(), parameterSpecSet.end(),
                                    [&message](const ParameterSpec& parameterSpec)
                                    {
                                        return parameterSpec.hash == message.hash;
                                    });
            itr->setter(*curtis_, message.value);
        });
    }

    const std::vector<VisualizationDataSet>& EngineManager::getVisualizationDataSets()
    {
        const std::lock_guard<std::mutex> lock(mutex_);
        return visualizationDataSets_;
    }

    void EngineManager::onVisualizationDataCacheFilled(const std::vector<VisualizationDataSet>& cache)
    {
        visualizationDataCompressor_.compress(cache);
        const std::lock_guard<std::mutex> lock(mutex_);
        visualizationDataSets_ = visualizationDataCompressor_.getCompressed();
    }
}
