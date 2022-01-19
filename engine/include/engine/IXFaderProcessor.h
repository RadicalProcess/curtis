#pragma once

#include <memory>

#include "IProcessor.h"

namespace rp::trevor
{
    class IXFaderProcessor
    {
    public:
        virtual ~IXFaderProcessor() = default;

        virtual void process(Buffer& buffer, const Buffer& reference) = 0;

        virtual void setDryWet(float dryWet)  = 0;
    };

    using XFaderProcessorPtr = std::unique_ptr<IXFaderProcessor>;
}



