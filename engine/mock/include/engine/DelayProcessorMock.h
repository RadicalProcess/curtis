#pragma once

#include <gmock/gmock.h>

#include <engine/IDelayProcessor.h>

namespace rp::trevor {

    class DelayProcessorMock : public IDelayProcessor {
    public:
        ~DelayProcessorMock() override = default;

        MOCK_METHOD(void, process, (Buffer& buffer), (override));
    };

}  // namespace rp::trevor
