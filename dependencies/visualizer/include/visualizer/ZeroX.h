#pragma once

#include "Vbo.h"

namespace rp::curtis
{
    class ZeroX
    {
    public:
        ZeroX(size_t samples);

        void render(const std::vector<size_t>& indices);

    private:
        float tick_;
    };
}
