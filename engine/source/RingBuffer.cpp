#include "RingBuffer.h"

namespace rp::trevor
{
    RingBuffer::RingBuffer(size_t capacity)
    : internalBuffer_(capacity, 0.0f)
    , writeHead_(0)
    , readHead_(0)
    , distance_(0)
    {
    }

    bool RingBuffer::push(Buffer& buffer)
    {
        if(distance_ + buffer.size() > internalBuffer_.size())
            return false;

        if(writeHead_ + buffer.size() < internalBuffer_.size())
        {
            std::memcpy(&internalBuffer_[writeHead_], buffer.data(), buffer.size() * sizeof(float));
            writeHead_ += buffer.size();
        }
        else
        {
            const auto capacity = internalBuffer_.size();
            const auto tillEnd = capacity - writeHead_;
            const auto excess = writeHead_ + buffer.size() - capacity;

            std::memcpy(&internalBuffer_[writeHead_], buffer.data(), tillEnd * sizeof(float));
            std::memcpy(internalBuffer_.data(), buffer.data(), excess * sizeof(float));

            writeHead_ = (writeHead_ + buffer.size()) % capacity;
        }
        distance_ += buffer.size();
        return true;
    }

    bool RingBuffer::tryConsume(Buffer& buffer)
    {
        if(distance_ < buffer.size())
            return false;

        std::memcpy(buffer.data(), &internalBuffer_[readHead_], buffer.size() * sizeof(float));
        readHead_ = (readHead_ + buffer.size()) % internalBuffer_.size();
        distance_ -= buffer.size();
        return true;
    }
}
