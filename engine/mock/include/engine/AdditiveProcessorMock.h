#pragma once

#include <gmock/gmock.h>

#include <engine/IAdditiveProcessor.h>

namespace rp::trevor {

    class AdditiveProcessorMock : public IAdditiveProcessor {

    public:
        ~AdditiveProcessorMock() override =default;

        MOCK_METHOD(void, setAdditiveHarmonic, (size_t index, float amp), (override));

        MOCK_METHOD(void, process, (Buffer& buffer), (override));
    };

}  // namespace rp::trevor
