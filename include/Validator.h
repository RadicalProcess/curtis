#pragma once

namespace rp::curtis
{
    class Validator
    {
    public:
        Validator(float sampleRate)
        : validity_(sampleRate >= 44100.0f)
        {
        }

        bool isValid() const
        {
            return validity_;
        }

        const bool validity_;
    };
}
