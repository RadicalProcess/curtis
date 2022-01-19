#pragma once

#include <vector>

#include "Buffer.h"

namespace rp::trevor
{
    class RingBuffer
    {
    public:
        explicit RingBuffer(size_t capacity);

        bool push(Buffer& buffer);

        bool tryConsume(Buffer& buffer);

    private:
        std::vector<float> internalBuffer_;
        size_t writeHead_;
        size_t readHead_;
        size_t distance_;
    };
}
