#include "EngineManager.h"

#include "ParameterSpecSet.h"

namespace rp::trevor
{
    EngineManager::EngineManager(size_t channels, size_t timeout, float sampleRate, size_t bufferSize, const IFactory& factory)
    {
        for(auto i = static_cast<size_t>(0); i < channels; ++i)
        {
            engines_.emplace_back(factory.createEngine(i, timeout, sampleRate, bufferSize));
            visualizationData_.emplace_back(VisualizationData(Constants::visualDataSize));
        }

        for(auto& engine : engines_)
            engine->addListener(this);
    }

    EngineManager::~EngineManager()
    {
        for(auto& engine : engines_)
            engine->removeListener(this);
    }

    void EngineManager::process(float** buffer, size_t size)
    {
        updateParameters();
        for(auto i = static_cast<size_t>(0); i < engines_.size(); ++i)
            engines_[i]->process(buffer[i], size);
    }

    void EngineManager::setParameter(size_t id, float value)
    {
        messageQueue_.push(Message{id, value});
    }

    VisualizationData EngineManager::getVisualizationData(size_t channel)
    {
        const auto&& lock = std::lock_guard<std::mutex>(mutex_);
        return visualizationData_[channel];
    }

    void EngineManager::updateParameters()
    {
        messageQueue_.consume_all([this](Message& message)
                                  {
                                      auto itr = std::find_if(parameterSpecSet.begin(), parameterSpecSet.end(),
                                                              [&message](const ParameterSpec& parameterSpec)
                                                              {
                                                                  return parameterSpec.hash == message.hash;
                                                              });
                                      for(auto& engine : engines_)
                                          itr->setter(*engine, message.value);
                                  });
    }

    void EngineManager::onVisualizationDataFilled(size_t channel, const VisualizationData& data)
    {
        const auto&& lock = std::lock_guard<std::mutex>(mutex_);
        visualizationData_[channel] = data;
    }
}
