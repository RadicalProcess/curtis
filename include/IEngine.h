#pragma once

#include "IParameterSetter.h"

namespace rp::curtis
{

    class IEngine : public IParameterSetter
    {
    public:
        virtual ~IEngine() = default;

        virtual void process(float** samples, size_t size)  = 0;

    };

    using EnginePtr = std::unique_ptr<IEngine>;
}
