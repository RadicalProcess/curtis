#pragma once

#include <memory>

#include "VisualizationData.h"

namespace rp::trevor
{
    class IVisualizationCache
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;

            virtual void onCacheFilled(const VisualizationData& data) = 0;
        };

    public:
        virtual ~IVisualizationCache() = default;

        virtual void push(const VisualizationData& data) = 0;

        virtual void addListener(Listener* listener) = 0;

        virtual void removeListener(Listener* listener) = 0;
    };

    using VisualizationCachePtr = std::unique_ptr<IVisualizationCache>;
}

