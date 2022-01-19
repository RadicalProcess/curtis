#pragma once

#include "VisualizationData.h"

namespace rp::trevor
{
    class IVisualizationDataProvider
    {
    public:
        virtual ~IVisualizationDataProvider() = default;

        virtual VisualizationData getVisualizationData(size_t channel) = 0;
    };
}
