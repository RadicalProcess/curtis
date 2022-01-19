#pragma once

namespace rp::curtis
{
    class IParameterSetter
    {
    public:
        virtual ~IParameterSetter() = default;

        virtual void setParameter(size_t id, float value) = 0;
    };
}
