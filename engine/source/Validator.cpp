#include "Validator.h"
#include "Constants.h"

namespace rp::trevor
{
    Validator::Validator(float sampleRate, size_t blockSize)
    : validity_( Constants::minSampleRate <= sampleRate && sampleRate <= Constants::maxSampleRate && blockSize <= Constants::maxBlockSize)
    {
    }

    bool Validator::isValid() const
    {
        return validity_;
    }
}
