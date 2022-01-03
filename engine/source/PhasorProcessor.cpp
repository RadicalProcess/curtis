#include "PhasorProcessor.h"

namespace rp::trevor
{
    PhasorProcessor::PhasorProcessor()
    : phasor_(phasor_create(), [](Phasor* phasor){ phasor_destroy(phasor);})
    {
    }

    void PhasorProcessor::process(Buffer& buffer)
    {
        phasor_process(phasor_.get(), buffer.data(), buffer.size());
    }

    void PhasorProcessor::setDutyCycle(float dc)
    {
        phasor_set_duty_cycle(phasor_.get(), dc);
    }
}
