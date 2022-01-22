#pragma once

#include <string>
#include <array>

namespace rp::curtis
{
    struct Preset
    {
        const std::string name;
    };

    extern const std::array<Preset, 5> presets;
}
