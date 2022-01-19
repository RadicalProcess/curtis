#pragma once

#include "VisualizationData.h"
#include "IVisualizationDataProvider.h"
#include "IParameterSetter.h"

namespace rp::trevor
{
    class IEngineManager : public IParameterSetter
                         , public IVisualizationDataProvider
    {
    public:
        virtual ~IEngineManager() = default;

        virtual void process(float** buffer, size_t size) = 0;

    };

    using EngineManagerPtr = std::unique_ptr<IEngineManager>;
}
