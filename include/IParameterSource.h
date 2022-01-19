#pragma once

#include <memory>

namespace rp::trevor
{
    class IParameterSource
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;

            virtual void onParameterChanged(float value) = 0;
        };

    public:
        virtual ~IParameterSource() = default;

        virtual void addListener(Listener* listener) = 0;

        virtual void removeListener(Listener* listener) = 0;
    };

    using ParameterSourcePtr = std::unique_ptr<rp::trevor::IParameterSource>;
}
