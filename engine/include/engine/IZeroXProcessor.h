#pragma once

#include "IProcessor.h"

namespace rp::trevor
{
    class IZeroXProcessor : public IProcessor
    {
    public:
        virtual ~IZeroXProcessor() = default;

        virtual void setSkip(size_t skip) = 0;

        virtual void setMinLength(size_t samples) = 0;
    };

    using ZeroXProcessorPtr = std::unique_ptr<IZeroXProcessor>;
}
