#include "ZeroXProcessor.h"

namespace rp::trevor
{
    ZeroXProcessor::ZeroXProcessor(size_t timeout)
    : zeroX_({zerox_create(timeout), [](ZeroX* zeroX){ zerox_destroy(zeroX);}})
    {
    }

    void ZeroXProcessor::setSkip(size_t skip)
    {
        zerox_set_skip(zeroX_.get(), skip);
    }

    void ZeroXProcessor::setMinLength(size_t samples)
    {
        zerox_set_min_length(zeroX_.get(), samples);
    }

    void ZeroXProcessor::process(Buffer& buffer)
    {
        zerox_process(zeroX_.get(), buffer.data(), buffer.size());
    }
}
