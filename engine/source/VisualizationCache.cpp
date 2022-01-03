#include "VisualizationCache.h"

namespace rp::trevor
{
    VisualizationCache::VisualizationCache(size_t cacheSize, size_t outputSize)
    : cacheCount_(0)
    , visualizationDataCache_(cacheSize)
    , outputSize_(outputSize)
    {
    }

    void VisualizationCache::push(const VisualizationData& data)
    {
        visualizationDataCache_.original.copyTo(cacheCount_, data.original);
        visualizationDataCache_.generated.copyTo(cacheCount_, data.generated);
        visualizationDataCache_.mixed.copyTo(cacheCount_, data.mixed);
        visualizationDataCache_.zeroCrosses.copyTo(cacheCount_, data.zeroCrosses);

        cacheCount_ += data.size();

        if(cacheCount_ == visualizationDataCache_.size())
        {
            auto downSampledData = VisualizationData(outputSize_);
            downSampledData.original.copyTo(0, visualizationDataCache_.original.downSample(outputSize_, DownSampleMethod::Skip));
            downSampledData.generated.copyTo(0, visualizationDataCache_.generated.downSample(outputSize_, DownSampleMethod::Skip));
            downSampledData.mixed.copyTo(0, visualizationDataCache_.mixed.downSample(outputSize_, DownSampleMethod::Skip));
            downSampledData.zeroCrosses.copyTo(0, visualizationDataCache_.zeroCrosses.downSample(outputSize_, DownSampleMethod::Binarize));

            for(auto* listener : listeners_)
                listener->onCacheFilled(downSampledData);
            cacheCount_ = 0;
        }
    }

    void VisualizationCache::addListener(IVisualizationCache::Listener* listener)
    {
        listeners_.insert(listener);
    }

    void VisualizationCache::removeListener(IVisualizationCache::Listener* listener)
    {
        listeners_.erase(listener);
    }
}
