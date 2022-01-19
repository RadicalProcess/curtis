#pragma once

#include <memory>

#include "Buffer.h"

namespace rp::trevor
{
    class IProcessor
    {
    public:
        virtual ~IProcessor() = default;

        virtual void process(Buffer& buffer) = 0;
    };

    using ProcessorPtr = std::unique_ptr<IProcessor>;
}
