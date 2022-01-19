#pragma once

#include <gmock/gmock.h>

#include <engine/IZeroXProcessor.h>

namespace rp::trevor {

    class ZeroXProcessorMock : public IZeroXProcessor {
    public:
        ~ZeroXProcessorMock() override = default;
        MOCK_METHOD(void, setSkip, (size_t skip), (override));
        MOCK_METHOD(void, setMinLength, (size_t samples), (override));

        MOCK_METHOD(void, process, (Buffer& buffer), (override));
    };

}  // namespace rp::trevor

