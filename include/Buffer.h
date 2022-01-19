#pragma once

#include <cstddef>

namespace rp::trevor
{
    enum class DownSampleMethod
    {
        Binarize,
        Skip
    };

    class Buffer
    {
    public:
        explicit Buffer(size_t size);

        explicit Buffer(size_t size, float filler);

        Buffer(float* data, size_t size);

        Buffer(const Buffer& buffer);

        Buffer& operator=(const Buffer& buffer);

        ~Buffer();

        void copyTo(size_t index, const Buffer& buffer);

        void multiply(const Buffer& buffer);

        void clear();

        const float& operator[](size_t index) const;

        float& operator[](size_t index);

        size_t size() const;

        float* data();

        const float* data() const;

        bool owned() const;

        Buffer downSample(size_t newSize, DownSampleMethod downSampleMethod) const;

    private:
        float* data_;
        size_t size_;
        bool owned_ {false };
    };
}
