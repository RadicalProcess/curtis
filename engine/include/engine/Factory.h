#pragma once

#include "IFactory.h"

namespace rp::trevor
{
    class Factory : public IFactory
    {
    public:
        ~Factory() override = default;

        VisualizationCachePtr createVisualizationCache(size_t cacheSize, size_t outputSize) const override;

        EnginePtr createEngine(size_t id, size_t timeout, float sampleRate, size_t bufferSize) const override;

        AdditiveProcessorPtr createAdditiveProcessor() const override;

        DelayProcessorPtr createDelayProcessor(size_t delayTime) const override;

        HoldProcessorPtr createHoldProcessor() const override;

        PhasorProcessorPtr createPhasorProcessor() const override;

        XFaderProcessorPtr createXFaderProcessor(float initialMix) const override;

        ZeroXProcessorPtr createZeroXProcessor(size_t timeout) const override;

        ParameterSyncPtr
        createParameterSync(IParameterSource& parameterStateSource, size_t parameterHash,
                            IParameterSetter& parameterSetter) const override;
    };
}
