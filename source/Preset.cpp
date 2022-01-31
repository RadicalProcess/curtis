#include "Preset.h"

namespace rp::curtis
{
    const std::array<Preset, 13> presets = {
        Preset{"wider particles", -100.f, 125.f, 0, 10, 100, true, 0.f, 0.f, 0.f, 0.f, -0.1f, 0.1f, -1.0f, 1.0f, -10.f, 0.f },
        Preset{"broken robot", -100.f, 60.f, 10, 3, 70, false, 0.f, 0.f, 0.f, 0.f, -0.1f, 0.1f, 0.0f, 0.0f, -80.f, 0.f },
        Preset{"random access memory", -100.f, 40.f, 0, 30, 100, false, -12.f, 12.f, 0.f, 0.f, -1.f, 1.f, 0.0f, 0.0f, -80.f, 0.f },
        Preset{"rain drop", -100.f, 25.f, 0, 30, 25, true, 18.f, 24.f, -12.f, -24.0f, -0.25f, 0.25f, -0.5f, 0.5f, -80.f, 0.f},
        Preset{"come to daddy", -100.f, 25.f, 0, 3, 100, true, -1.f, 1.f, -1.f, 1.f, -0.5f, 0.5f, -0.5f, 0.5f, -80.f, 0.f},
        Preset{"convergence", -100.f, 100.f, 0, 0, 100, true, -3.f, 3.f, 0.f, 0.f, -1.f, 1.f, 0.f, 0.f, -70.f, 0.f},
        Preset{"toxic infant", -100.f, 10.f, 0, 0, 100, true, 11.0f, 13.0f, 11.0f, 13.0f, -0.1f, 0.1f, -0.1f, 0.1f, -10.f, 0.f},
        Preset{"Granpa", -100.f, 10.f, 0, 0, 100, true, -13.0f, -11.0f, -13.0f, -11.0f, -0.1f, 0.1f, -0.05f, 0.05f, -10.f, 0.f},
        Preset{"retro shooter", -100.f, 30.f, 0, 5, 100, true, 12.f, 24.f, -24.0f, -12.0f, -1.f, 1.f, -1.f, 1.f, -80.f, 0.f},
        Preset{"chatter", -100.f, 250.f, 0, 10, 100, true, -24.f, 24.f, 24.0f, 24.0f, -1.f, 1.f, -1.f, 1.f, -80.f, 0.f},
        Preset{"time travel", -100.f, 500.f, 0, 30, 100, true, -24.f, 0.0f, 0.0f, 24.0f, 0.f, 0.f, -1.f, 1.f, -80.f, 0.f},
        Preset{"vader", -100.f, 10.f, 0, 30, 100, false, -24.f, -24.f, -24.f, -24.f, 0.f, 0.f, 0.f, 0.f, -8.f, 0.f},
        Preset{"max glisson", -100.f, 5.f, 0, 0, 100, true, -24.f, 24.f, -24.f, 24.f, -1.f, 1.f, -1.f, 1.f, -80.f, 0.f}
    };
}
