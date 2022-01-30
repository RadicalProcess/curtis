#pragma once

#include <curtis_core/Buffer.h>

#include "Vbo.h"

namespace rp::curtis
{
    class Waveform
    {
    public:
        Waveform(size_t size);

        void update(const Buffer& buffer);

        void bind();

       GLsizei getNumVertices() const;

    private:
        std::vector<Position> positions_;
        Vbo vbo_;
    };
}
