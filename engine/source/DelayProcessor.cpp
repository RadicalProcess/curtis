#include "DelayProcessor.h"


namespace rp::trevor
{
    DelayProcessor::DelayProcessor(size_t delayTime)
    :delay_({delay_create(delayTime), [](Delay* delay){ delay_destroy(delay);}})
    {}

    void DelayProcessor::process(Buffer& buffer)
    {
        delay_process(delay_.get(), buffer.data(), buffer.size());
    }
}
