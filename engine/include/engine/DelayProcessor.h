#include <functional>

#include <dsp.h>

#include "IDelayProcessor.h"

namespace rp::trevor
{
    class DelayProcessor : public IDelayProcessor
    {
    public:
        DelayProcessor(size_t delayTime);

        ~DelayProcessor() override = default;

        void process(Buffer& buffer) override;

    private:
        std::unique_ptr<Delay, std::function<void(Delay*)>> delay_;
    };
}
