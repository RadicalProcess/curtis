#pragma once

#include <cstdio>
#include "IEngine.h"

namespace rp::curtis
{
    class Engine : public IEngine
    {
    public:
        ~Engine() override = default;

        void process(float** samples, size_t size) override;

        void setParameter(size_t id, float value) override;
    };
}
