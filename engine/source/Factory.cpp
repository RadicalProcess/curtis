#include "Factory.h"

#include "VisualizationCache.h"
#include "Engine.h"
#include "AdditiveProcessor.h"
#include "DelayProcessor.h"
#include "HoldProcessor.h"
#include "PhasorProcessor.h"
#include "XFaderProcessor.h"
#include "ZeroXProcessor.h"
#include "ParameterSync.h"

namespace rp::trevor
{
    VisualizationCachePtr Factory::createVisualizationCache(size_t cacheSize, size_t outputSize) const
    {
        return std::make_unique<VisualizationCache>(cacheSize, outputSize);
    }

    EnginePtr Factory::createEngine(size_t id, size_t timeout, float sampleRate, size_t bufferSize) const
    {
        return std::make_unique<Engine>(id, timeout, sampleRate, bufferSize, *this);
    }

    AdditiveProcessorPtr Factory::createAdditiveProcessor() const
    {
        return std::make_unique<AdditiveProcessor>();
    }

    DelayProcessorPtr Factory::createDelayProcessor(size_t delayTime) const
    {
        return std::make_unique<DelayProcessor>(delayTime);
    }

    HoldProcessorPtr Factory::createHoldProcessor() const
    {
        return std::make_unique<HoldProcessor>();
    }

    PhasorProcessorPtr Factory::createPhasorProcessor() const
    {
        return std::make_unique<PhasorProcessor>();
    }

    XFaderProcessorPtr Factory::createXFaderProcessor(float initialMix) const
    {
        return std::make_unique<XFaderProcessor>(initialMix);
    }

    ZeroXProcessorPtr Factory::createZeroXProcessor(size_t timeout) const
    {
        return std::make_unique<ZeroXProcessor>(timeout);
    }

    ParameterSyncPtr
    Factory::createParameterSync(IParameterSource& parameterStateSource, size_t parameterHash,
                                 IParameterSetter& parameterSetter) const
    {
        return std::make_unique<ParameterSync>(parameterStateSource, parameterHash, parameterSetter);
    }
}
