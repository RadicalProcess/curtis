#pragma once

#include <functional>

#include <dsp.h>

#include "IXFaderProcessor.h"

namespace rp::trevor
{
    class XFaderProcessor : public IXFaderProcessor
    {
    public:
        explicit XFaderProcessor(float initialMix);

        ~XFaderProcessor() override = default;

        void process(Buffer& buffer, const Buffer& reference) override;


        void setDryWet(float dryWet) override;

    private:
        std::unique_ptr<XFader, std::function<void(XFader*)>> xFader_;
    };
}
