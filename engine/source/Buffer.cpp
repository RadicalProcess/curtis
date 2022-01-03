#include "Buffer.h"

#include <cstring>
#include <stdexcept>

namespace rp::trevor
{
    Buffer::Buffer(size_t size)
    : size_(size)
    , owned_(true)
    {
        data_ = new float[size];
    }

    Buffer::Buffer(size_t size, float filler)
    : Buffer(size)
    {
        for(auto i = static_cast<size_t>(0) ; i < size_; ++i)
            data_[i] = filler;
    }

    Buffer::Buffer(float* data, size_t size)
    : data_(data)
    , size_(size)
    , owned_(false)
    {
    }

    Buffer::Buffer(const Buffer& buffer)
    {
        data_ = new float[buffer.size_];
        memcpy(data_, buffer.data_, buffer.size_ * sizeof(float));
        owned_ = true;
        size_ = buffer.size_;
    }

    Buffer& Buffer::operator=(const Buffer& buffer)
    {
        if(size_ != buffer.size())
            throw std::out_of_range("trying to copy buffer with different sizes");

        memcpy(data_, buffer.data_, size_ * sizeof(float));
        return *this;
    }

    Buffer::~Buffer()
    {
        if(owned_)
            delete data_;
    }

    const float& Buffer::operator[](size_t index) const
    {
        if(size_ <= index)
            throw std::out_of_range("index exceeds the buffer capacity");
        return data_[index];
    }

    float& Buffer::operator[](size_t index)
    {
        if(size_ <= index)
            throw std::out_of_range("index exceeds the buffer capacity");
        return data_[index];
    }

    void Buffer::copyTo(size_t index, const Buffer& buffer)
    {
        if(size_ < index + buffer.size_)
            throw std::out_of_range("excess the size of this buffer");

        memcpy(&data_[index], buffer.data_, buffer.size_ * sizeof(float));
    }

    void Buffer::multiply(const Buffer& other)
    {
        for(auto i = static_cast<size_t>(0); i < size_; ++i)
            data_[i] *= other[i];
    }

    void Buffer::clear()
    {
        for(auto i = static_cast<size_t>(0); i < size_; ++i)
            data_[i] = 0.0f;
    }

    float* Buffer::data()
    {
        return data_;
    }

    const float* Buffer::data() const
    {
        return data_;
    }

    size_t Buffer::size() const
    {
        return size_;
    }

    bool Buffer::owned() const
    {
        return owned_;
    }

    Buffer Buffer::downSample(size_t newSize, DownSampleMethod downSampleMethod) const
    {
        if (newSize >= size_ || newSize == 0)
            throw std::out_of_range("newSize must be not zero and smaller than the size of this buffer");

        if (size_ % newSize != 0)
            throw std::logic_error("new Size cannot divide current size");

        auto&& buffer = Buffer(newSize);
        const auto ratio = size_ / newSize;

        switch (downSampleMethod)
        {
            case DownSampleMethod::Binarize:
            {
                for(auto i = static_cast<size_t>(0); i < newSize; i++)
                {
                    const auto offset = i * ratio;
                    buffer[i] = 0.0f;
                    for(auto j = static_cast<size_t>(0); j < ratio; j++)
                    {
                        if(data_[offset + j] > 0.0)
                        {
                            buffer[i] = 1.0f;
                            break;
                        }
                    }
                }
                break;
            }
            case DownSampleMethod::Skip:
            {
                for(auto i = static_cast<size_t>(0); i < newSize; i++)
                    buffer[i] = data_[i*ratio];
                break;
            }
        }
        return buffer;
    }


}
