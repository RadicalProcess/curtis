#pragma once

#include <gmock/gmock.h>

#include <engine/IParameterSource.h>

namespace rp::trevor {

    class ParameterStateSourceMock : public IParameterSource {
    public:
        ~ParameterStateSourceMock() = default;
        MOCK_METHOD(void, addListener, (Listener* listener), (override));
        MOCK_METHOD(void, removeListener, (Listener* listener), (override));
    };

}  // namespace rp::trevor
