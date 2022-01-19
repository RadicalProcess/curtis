#pragma once

#include <vector>
#include <stdexcept>

#include "Buffer.h"

namespace rp::trevor
{
    struct VisualizationData
    {
        inline
        explicit VisualizationData(size_t size)
        : original(size)
        , generated(size)
        , mixed(size)
        , zeroCrosses(size)
        {
            original.clear();
            generated.clear();
            mixed.clear();
            zeroCrosses.clear();
        }

        inline
        size_t size() const
        {
            return original.size();
        }

        inline
        VisualizationData& operator=(const VisualizationData& visualizationData)
        {
            if(size() != visualizationData.size())
                throw std::out_of_range("trying to copy visualization data with different sizes");

            original = visualizationData.original;
            generated = visualizationData.generated;
            mixed = visualizationData.mixed;
            zeroCrosses = visualizationData.zeroCrosses;
            return *this;
        }

        Buffer original;
        Buffer generated;
        Buffer mixed;
        Buffer zeroCrosses;
    };
}
