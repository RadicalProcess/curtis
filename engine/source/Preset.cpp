#include "Preset.h"

namespace rp::trevor
{
    const std::array<Preset, 5> presets = {
            Preset{"wave set distortion", 1, 0.f, 100.f, 0.f, 0.f, 0.f, 0.f, 100.f, 0.f, 0.f, 0.f, -96.f, -3.f},
            Preset{"chocked guy", 0, 0.f, 100.f, 50.f, 25.f, 12.5f, 5.f, 35.f, 0.f, 0.1f, 0.f, -96.f, -9.f},
            Preset{"broken radio", 1, 0.f, 100.f, 60.f, 25.f, 0.f, 45.f, 90.f, 0.f, 100.f, 0.f, -96.f, -12.f},
            Preset{"synthesized", 3, 1000.f, 0.f, 25.f, 50.f, 50.f, 90.f, 100.f, 0.f, 0.f, 0.f, -96.f, -12.f},
            Preset{"gate punch", 2, 0.f, 100.f, 70.0f, 50.f, 40.0f, 50.0f, 100.f, 15.f, 90.f, 15.f, -20.f, -10.f}
    };
}
