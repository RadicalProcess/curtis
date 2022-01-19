#pragma once

#include <gmock/gmock.h>

#include <engine/IParameterSetter.h>

namespace rp::trevor {

    class ParameterSetterMock : public IParameterSetter {
    public:
        ~ParameterSetterMock() = default;
        MOCK_METHOD(void, setParameter, (size_t id, float value), (override));
    };

}  // namespace rp::trevor
