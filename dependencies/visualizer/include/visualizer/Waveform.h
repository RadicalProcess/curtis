#pragma once

#include <curtis_core/Buffer.h>

#include "Vbo.h"

namespace rp::curtis
{
    class Waveform
    {
    public:
        Waveform(size_t size);

        void update();

        void bind();

       GLsizei getNumVertices() const;

       std::vector<Position>& getPosition();

    private:
        std::vector<Position> positions_;
        Vbo vbo_;
    };
}
