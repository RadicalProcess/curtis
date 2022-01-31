#pragma once

#include <string>
#include <array>

namespace rp::curtis
{
    struct Preset
    {
        const std::string name;
        const float inputMix;
        const float segmentMin;
        const int repeat;
        const int random;
        const int density;
        const bool glisson;
        const float startPitchA;
        const float startPitchB;
        const float endPitchA;
        const float endPitchB;
        const float startPositionA;
        const float startPositionB;
        const float endPositionA;
        const float endPositionB;
        const float dry;
        const float wet;
    };

    extern const std::array<Preset, 13> presets;
}
