#pragma once

#include <cstdlib>

namespace rp::trevor
{
    class Validator
    {
    public:
        Validator(float sampleRate, size_t blockSize);

        bool isValid() const;

    private:
        const bool validity_;
    };
}
