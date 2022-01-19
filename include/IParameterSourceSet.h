#pragma once

#include <string>
#include <memory>

namespace rp::curts
{
    class IParameterSourceSet
    {
    public:
        class Listener
        {
        public:
            ~Listener() = default;

            virtual void onParameterChanged(std::string& parameterId, float value);
        };

    public:
        virtual ~IParameterSourceSet() = default;

        virtual void addListener(const std::string& parameterId, IParameterSourceSet::Listener* listener) = 0;

        virtual void removeListener(const std::string& parameterId, IParameterSourceSet::Listener* listener) = 0;
    };

    using ParameterSourceSetPtr = std::unique_ptr<IParameterSourceSet>;
}
