#include "IHoldProcessor.h"

#include <functional>

#include <dsp.h>

namespace rp::trevor
{
    class HoldProcessor : public IHoldProcessor
    {
    public:
        HoldProcessor();

        ~HoldProcessor() override = default;


        void setThreshold(float threshold) override;

        void setBoost(float boost) override;

        void setGate(float gate) override;

        void process(Buffer& buffer) override;

    private:
        std::unique_ptr<Hold, std::function<void(Hold*)>> hold_;

    };
}
