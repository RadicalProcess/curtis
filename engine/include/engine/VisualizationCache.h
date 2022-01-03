#pragma once

#include <set>

#include "IVisualizationCache.h"

namespace rp::trevor
{
    class VisualizationCache : public IVisualizationCache
    {
    public:
        VisualizationCache(size_t cacheSize, size_t outputSize);

        ~VisualizationCache() override = default;

        void push(const VisualizationData& data) override;

        void addListener(Listener *listener) override;

        void removeListener(Listener *listener) override;

    private:
        size_t cacheCount_;
        VisualizationData visualizationDataCache_;
        size_t outputSize_;
        std::set<Listener*> listeners_;
    };

}
