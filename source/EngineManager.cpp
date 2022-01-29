#include "EngineManager.h"

#include <memory>
#include "ParameterSpecSet.h"

namespace rp::curtis
{
    EngineManager::EngineManager(float sampleRate, size_t blockSize)
    : curtis_(std::make_unique<Curtis>(sampleRate, blockSize))
    {}

    void EngineManager::process(float** buffer, size_t size)
    {
        updateParameters();
        auto leftBuffer = curtis::Buffer(buffer[0], size);
        auto rightBuffer = curtis::Buffer(buffer[1], size);
        curtis_->process(leftBuffer, rightBuffer);
    }

    void EngineManager::setParameter(size_t id, float value)
    {
        messageQueue_.push(Message{id, value});
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
            itr->setter(*curtis_, message.value);
        });
    }
}
