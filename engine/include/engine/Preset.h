#pragma once

#include <string>
#include <array>

namespace rp::trevor
{
    struct Preset
    {
        const std::string name;
        const int skip;
        const float minLength;
        const float harmonic1;
        const float harmonic2;
        const float harmonic3;
        const float harmonic4;
        const float harmonic5;
        const float dutyCycle;
        const float threshold;
        const float boost;
        const float gate;
        const float dry;
        const float wet;
    };

    extern const std::array<Preset, 5> presets;
}
