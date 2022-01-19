#pragma once

#include <functional>

#include <dsp.h>

#include "IZeroXProcessor.h"

namespace rp::trevor
{
    class ZeroXProcessor : public IZeroXProcessor
    {
    public:
        explicit ZeroXProcessor(size_t timeout);

        ~ZeroXProcessor() = default;

        void setSkip(size_t skip) override;

        void setMinLength(size_t samples) override;

        void process(Buffer& buffer) override;

    private:
        std::unique_ptr<ZeroX, std::function<void(ZeroX*)>> zeroX_;
    };
}
