#pragma once

#include <memory>

#include "IVisualizationCache.h"
#include "IEngine.h"
#include "IAdditiveProcessor.h"
#include "IDelayProcessor.h"
#include "IHoldProcessor.h"
#include "IPhasorProcessor.h"
#include "IXFaderProcessor.h"
#include "IZeroXProcessor.h"
#include "IParameterSync.h"
#include "IParameterSource.h"
#include "IParameterSetter.h"
#include "ParameterSpec.h"

namespace rp::trevor
{
    class IFactory
    {
    public:
        virtual ~IFactory() = default;

        virtual VisualizationCachePtr createVisualizationCache(size_t cacheSize, size_t outputSize) const = 0;

        virtual EnginePtr createEngine(size_t id, size_t timeout, float sampleRate, size_t bufferSize) const = 0;

        virtual AdditiveProcessorPtr createAdditiveProcessor() const = 0;

        virtual DelayProcessorPtr createDelayProcessor(size_t delayTime) const = 0;

        virtual HoldProcessorPtr createHoldProcessor() const = 0;

        virtual PhasorProcessorPtr createPhasorProcessor() const = 0;

        virtual XFaderProcessorPtr createXFaderProcessor(float initialMix) const = 0;

        virtual ZeroXProcessorPtr createZeroXProcessor(size_t timeout) const = 0;

        virtual ParameterSyncPtr createParameterSync(IParameterSource& parameterStateSource, size_t parameterHash, IParameterSetter& parameterSetter) const = 0;
    };

    using FactoryPtr = std::unique_ptr<IFactory>;
}
