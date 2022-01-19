#pragma once

#include <cstdlib>
#include <functional>

#include "Buffer.h"
#include "RingBuffer.h"

namespace rp::trevor
{
    class SampleCapacitor
    {
    public:
        SampleCapacitor(size_t blockSize, std::function<void(Buffer&)> func);

        void process(Buffer& buffer);

    private:
        Buffer tempBuffer_;
        RingBuffer inRingBuffer_;
        RingBuffer outRingBuffer_;
        std::function<void(Buffer&)> func_;
    };
}
