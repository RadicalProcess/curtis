#pragma once

#include <set>

#include "IFactory.h"
#include "IEngine.h"
#include "IVisualizationCache.h"

#include "Buffer.h"
#include "SampleCapacitor.h"

namespace rp::trevor
{
    class Engine : public IEngine
                 , public IVisualizationCache::Listener
    {
    public:
        Engine(size_t id, size_t timeout, float sampleRate, size_t bufferSize, const IFactory& factory);

        Engine( const Engine& ) = delete;

        Engine& operator=( const Engine& ) = delete;

        ~Engine() override;

        void process(float* buffer, size_t size) override;

        float getSampleRate() const override;

        IZeroXProcessor& getZeroXProcessor() override;

        IAdditiveProcessor& getAdditiveProcessor() override;

        IPhasorProcessor& getPhasorProcessor() override;

        IHoldProcessor& getHoldProcessor() override;

        void setDryGain(float gain) override;

        void setWetGain(float gain) override;

        void addListener(IEngine::Listener* listener) override;

        void removeListener(IEngine::Listener* listener) override;

    private:
        void onCacheFilled(const VisualizationData& data) override;



        const size_t id_;
        const float sampleRate_;

        float dryGain_ { 0.0f };
        float wetGain_ { 1.0f };

        ZeroXProcessorPtr zeroXProcessor_;
        AdditiveProcessorPtr additiveProcessor_;
        PhasorProcessorPtr phasorProcessor_;
        HoldProcessorPtr holdProcessor_;
        DelayProcessorPtr inputDelayProcessor_;
        DelayProcessorPtr dryDelayProcessor_;
        DelayProcessorPtr zeroXDelayProcessor_;

        VisualizationData visualizerData_;
        VisualizationCachePtr visualizationCache_;

        Buffer bufferForDrySignal_;
        Buffer bufferForHold_;
        Buffer bufferForDelay_;

        SampleCapacitor sampleCapacitor_;

        std::set<IEngine::Listener*> listeners_;
    };
}
