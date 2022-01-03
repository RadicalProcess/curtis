#pragma once


#include "IZeroXProcessor.h"
#include "IAdditiveProcessor.h"
#include "IPhasorProcessor.h"
#include "IHoldProcessor.h"
#include "IXFaderProcessor.h"

#include "VisualizationData.h"

namespace rp::trevor
{
    class IEngine
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;

            virtual void onVisualizationDataFilled(size_t channel, const VisualizationData& data) = 0;
        };

    public:
        virtual ~IEngine() = default;

        virtual void process(float* buffer, size_t size) = 0;

        virtual float getSampleRate() const = 0;

        virtual IZeroXProcessor& getZeroXProcessor() = 0;

        virtual IAdditiveProcessor& getAdditiveProcessor() = 0;

        virtual IPhasorProcessor& getPhasorProcessor() = 0;

        virtual IHoldProcessor& getHoldProcessor() = 0;

        virtual void setDryGain(float gain) = 0;

        virtual void setWetGain(float gain) = 0;

        virtual void addListener(Listener* listener) = 0;

        virtual void removeListener(Listener* listener) = 0;
    };

    using EnginePtr = std::unique_ptr<IEngine>;
}


