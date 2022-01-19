#include "HoldProcessor.h"

namespace rp::trevor
{
    HoldProcessor::HoldProcessor()
    : hold_({hold_create(), [](Hold* hold){ hold_destroy(hold);}})
    {
    }

    void HoldProcessor::process(Buffer& buffer)
    {
        hold_process(hold_.get(), buffer.data(), buffer.size());
    }

    void HoldProcessor::setThreshold(float threshold)
    {
        hold_set_thresh(hold_.get(), threshold);
    }

    void HoldProcessor::setBoost(float boost)
    {
        hold_set_boost(hold_.get(), boost);
    }

    void HoldProcessor::setGate(float gate)
    {
        hold_set_gate(hold_.get(), gate);
    }
}
