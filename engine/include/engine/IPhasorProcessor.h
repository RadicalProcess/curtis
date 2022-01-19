#pragma once

#include <memory>

#include "IProcessor.h"

namespace rp::trevor
{
    class IPhasorProcessor : public IProcessor
    {
    public:
        virtual ~IPhasorProcessor() = default;

        virtual void setDutyCycle(float dc) = 0;
    };

    using PhasorProcessorPtr = std::unique_ptr<IPhasorProcessor>;
}
