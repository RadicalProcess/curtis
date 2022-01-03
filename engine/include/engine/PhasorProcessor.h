#pragma once

#include <functional>

#include <dsp.h>

#include "IPhasorProcessor.h"

namespace rp::trevor
{
    class PhasorProcessor : public IPhasorProcessor
    {
    public:
        PhasorProcessor();

        ~PhasorProcessor() override = default;

        void process(Buffer& buffer) override;

        void setDutyCycle(float dc) override;

    private:
        std::unique_ptr<Phasor, std::function<void(Phasor*)>> phasor_;
    };
}
