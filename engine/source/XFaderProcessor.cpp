#include "XFaderProcessor.h"

namespace rp::trevor
{
    XFaderProcessor::XFaderProcessor(float initialMix)
    : xFader_(xfader_create(initialMix), [](XFader* xFader){ xfader_destroy(xFader);})
    {}

    void XFaderProcessor::setDryWet(float dryWet)
    {
        xfader_set_dry_wet(xFader_.get(), dryWet);
    }

    void XFaderProcessor::process(Buffer& buffer, const Buffer& reference)
    {
        xfader_process(xFader_.get(), buffer.data(), reference.data(), buffer.size());
    }
}
