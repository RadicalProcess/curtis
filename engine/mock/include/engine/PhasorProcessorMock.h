#pragma once

#include <gmock/gmock.h>

#include <engine/IPhasorProcessor.h>

namespace rp::trevor {

    class PhasorProcessorMock : public IPhasorProcessor {
    public:
        ~PhasorProcessorMock() override = default;

        MOCK_METHOD(void, setDutyCycle, (float dc), (override));

        MOCK_METHOD(void, process, (Buffer& buffer), (override));
    };

}  // namespace rp::trevor
