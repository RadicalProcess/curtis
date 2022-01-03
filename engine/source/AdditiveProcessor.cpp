#include "AdditiveProcessor.h"

namespace rp::trevor
{
    AdditiveProcessor::AdditiveProcessor()
    : additive_({additive_create(), [](Additive* additive){ additive_destroy(additive);}})
    {
    }

    void AdditiveProcessor::process(Buffer& buffer)
    {
        additive_process(additive_.get(), buffer.data(), buffer.size());
    }

    void AdditiveProcessor::setAdditiveHarmonic(size_t index, float amp)
    {
        additive_harm(additive_.get(), index, amp);
    }
}
