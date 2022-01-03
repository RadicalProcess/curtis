#pragma once

#include <memory>

#include "IProcessor.h"

namespace rp::trevor
{
    class IHoldProcessor : public IProcessor
    {
    public:
        virtual ~IHoldProcessor() = default;

        virtual void setThreshold(float threshold) = 0;

        virtual void setBoost(float boost) = 0;

        virtual void setGate(float gate) = 0;
    };

    using HoldProcessorPtr = std::unique_ptr<IHoldProcessor>;
}
