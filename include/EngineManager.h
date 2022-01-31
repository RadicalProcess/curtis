#pragma once

#include <vector>
#include <mutex>
#include <boost/lockfree/spsc_queue.hpp>
#include <curtis_core/Curtis.h>
#include "Message.h"
#include "IParameterSetter.h"
#include "VisualizationDataCompressor.h"

namespace rp::curtis
{
    class EngineManager : public IParameterSetter
                        , public IVisualizationDataCache::Listener
    {
    public:
        EngineManager(float sampleRate, size_t blockSize, size_t visualizationCacheSize);

        ~EngineManager() override;

        void process(float** buffer, size_t size);

        void setParameter(size_t id, float value) override;

        void updateParameters();

        const std::vector<VisualizationDataSet>& getVisualizationDataSets();

        void onVisualizationDataCacheFilled(const std::vector<VisualizationDataSet>& cache) override;

    private:
        std::mutex mutex_;
        std::vector<VisualizationDataSet> visualizationDataSets_;
        std::unique_ptr<Curtis> curtis_;
        boost::lockfree::spsc_queue<Message> messageQueue_{ 1024 };
        VisualizationDataCompressor visualizationDataCompressor_;
    };
}
