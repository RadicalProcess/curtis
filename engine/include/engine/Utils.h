#pragma once

#include <cmath>

namespace rp::trevor::utils
{
    inline
    float decibelToGain(float decibel)
    {
        return std::powf(10.f, decibel / 20.f);
    }
}
