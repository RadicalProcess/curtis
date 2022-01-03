#pragma once

#include <gmock/gmock.h>

#include <engine/IHoldProcessor.h>

namespace rp::trevor {

    class HoldProcessorMock : public IHoldProcessor {
    public:
        MOCK_METHOD(void, setThreshold, (float threshold), (override));
        MOCK_METHOD(void, setBoost, (float boost), (override));
        MOCK_METHOD(void, setGate, (float gate), (override));

        MOCK_METHOD(void, process, (Buffer& buffer), (override));
    };

}  // namespace rp::trevor
