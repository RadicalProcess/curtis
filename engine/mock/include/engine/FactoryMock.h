#pragma once

#include <gmock/gmock.h>

#include <engine/IFactory.h>

namespace rp::trevor {

    class FactoryMock : public IFactory {
    public:
        MOCK_METHOD(VisualizationCachePtr, createVisualizationCache, (size_t cacheSize, size_t outputSize), (const, override));
        MOCK_METHOD(EnginePtr, createEngine, (size_t id, size_t timeout, float sampleRate, size_t bufferSize), (const, override));

        MOCK_METHOD(AdditiveProcessorPtr, createAdditiveProcessor, (), (const, override));
        MOCK_METHOD(DelayProcessorPtr, createDelayProcessor, (size_t delayTime), (const, override));
        MOCK_METHOD(HoldProcessorPtr, createHoldProcessor, (), (const, override));
        MOCK_METHOD(PhasorProcessorPtr, createPhasorProcessor, (), (const, override));
        MOCK_METHOD(XFaderProcessorPtr, createXFaderProcessor, (float initialMix), (const, override));
        MOCK_METHOD(ZeroXProcessorPtr, createZeroXProcessor, (size_t timeout), (const, override));
        MOCK_METHOD(ParameterSyncPtr, createParameterSync, (IParameterSource & parameterStateSource, size_t parameterHash, IParameterSetter & parameterSetter), (const, override));
    };

}  // namespace rp::trevor
