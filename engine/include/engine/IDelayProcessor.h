#pragma once

#include <memory>

#include <engine/IProcessor.h>

namespace rp::trevor
{
    class IDelayProcessor : public IProcessor
    {
    public:
        virtual ~IDelayProcessor() = default;
    };

    using DelayProcessorPtr = std::unique_ptr<IDelayProcessor>;
}
