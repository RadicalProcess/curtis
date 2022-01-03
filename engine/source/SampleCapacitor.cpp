#include "SampleCapacitor.h"

#include <utility>

namespace rp::trevor
{
    SampleCapacitor::SampleCapacitor(size_t blockSize,  std::function<void(Buffer&)> func)
    : tempBuffer_(blockSize, 0.0f)
    , inRingBuffer_(blockSize * 2)
    , outRingBuffer_(blockSize * 2)
    , func_(std::move(func))
    {
        outRingBuffer_.push(tempBuffer_);
    }

    void SampleCapacitor::process(Buffer& buffer)
    {
        inRingBuffer_.push(buffer);
        if(inRingBuffer_.tryConsume(tempBuffer_))
        {
            func_(tempBuffer_);
            outRingBuffer_.push(tempBuffer_);
        }
        outRingBuffer_.tryConsume(buffer);
    }
}
