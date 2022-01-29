#pragma once

#include <vector>
#include <boost/lockfree/spsc_queue.hpp>
#include <curtis_core/Curtis.h>
#include "Message.h"
#include "IParameterSetter.h"

namespace rp::curtis
{
    class EngineManager : public IParameterSetter
    {
    public:
        EngineManager(float sampleRate, size_t blockSize);

        void process(float** buffer, size_t size);

        void setParameter(size_t id, float value) override;

        void updateParameters();

    private:
        std::unique_ptr<Curtis> curtis_;
        boost::lockfree::spsc_queue<Message> messageQueue_{ 1024 };

    };
}
