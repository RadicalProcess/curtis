#pragma once

#include <engine/IEngine.h>

namespace rp::trevor {

    class EngineMock : public IEngine {
    public:
        ~EngineMock() override = default;
        MOCK_METHOD(void, process, (float* buffer, size_t size), (override));
        MOCK_METHOD(float, getSampleRate, (), (const, override));
        MOCK_METHOD(IZeroXProcessor&, getZeroXProcessor, (), (override));
        MOCK_METHOD(IAdditiveProcessor&, getAdditiveProcessor, (), (override));
        MOCK_METHOD(IPhasorProcessor&, getPhasorProcessor, (), (override));
        MOCK_METHOD(IHoldProcessor&, getHoldProcessor, (), (override));
        MOCK_METHOD(void, setDryGain, (float), (override));
        MOCK_METHOD(void, setWetGain, (float), (override));
        MOCK_METHOD(void, addListener, (Listener* listener), (override));
        MOCK_METHOD(void, removeListener, (Listener* listener), (override));
    };

    class EngineListenerMock : public IEngine::Listener{
    public:
        ~EngineListenerMock() override = default;
        MOCK_METHOD(void, onVisualizationDataFilled, (size_t channel, const VisualizationData& data), (override));
    };

}  // namespace rp::trevor

