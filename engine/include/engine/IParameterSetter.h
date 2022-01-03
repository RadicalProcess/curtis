#pragma once

namespace rp::trevor
{
    class IParameterSetter
    {
    public:
        virtual ~IParameterSetter() = default;

        virtual void setParameter(size_t id, float value) = 0;
    };
}
