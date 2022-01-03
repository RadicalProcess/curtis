#pragma once

#include "IAdditiveProcessor.h"

#include <functional>

#include <dsp.h>

namespace rp::trevor
{
    class AdditiveProcessor : public IAdditiveProcessor
    {
    public:
        AdditiveProcessor();

        ~AdditiveProcessor() = default;

        void process(Buffer& buffer) override;

        void setAdditiveHarmonic(size_t index, float amp) override;

    private:
        std::unique_ptr<Additive, std::function<void(Additive*)>> additive_;
    };
}
