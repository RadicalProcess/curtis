#pragma once

#include <memory>

namespace rp::trevor
{
    class IParameterSync
    {
    public:
        virtual ~IParameterSync() = default;
    };

    using ParameterSyncPtr = std::unique_ptr<IParameterSync>;
}
