#pragma once

#include <memory>

#include "IProcessor.h"

namespace rp::trevor
{
    class IAdditiveProcessor : public IProcessor
    {
    public:
        virtual ~IAdditiveProcessor() = default;

        virtual void setAdditiveHarmonic(size_t index, float amp) = 0;
    };

    using AdditiveProcessorPtr = std::unique_ptr<IAdditiveProcessor>;
}
