#pragma once

#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

#include <boost/lockfree/spsc_queue.hpp>

#include "IEngineManager.h"

#include "Factory.h"
#include "Constants.h"
#include "Engine.h"
#include "Message.h"
#include "VisualizationData.h"


namespace rp::trevor
{
    class EngineManager : public IEngineManager,
                          public IEngine::Listener
    {
    public:
        EngineManager(size_t channels, size_t timeout, float sampleRate, size_t bufferSize, const IFactory& factory = Factory());

        ~EngineManager() override;

        void process(float** buffer, size_t size) override;

        void setParameter(size_t id, float value) override;

        VisualizationData getVisualizationData(size_t channel) override;

    private:
        void updateParameters();

        void onVisualizationDataFilled(size_t channel, const VisualizationData& data) override;

        std::vector<EnginePtr> engines_;
        boost::lockfree::spsc_queue<Message> messageQueue_{ Constants::messageQueueSize };

        std::mutex mutex_;
        std::vector<VisualizationData> visualizationData_;
    };

}
