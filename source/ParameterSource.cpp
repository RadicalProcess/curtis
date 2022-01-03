#include "ParameterSource.h"

namespace rp::trevor
{
    ParameterSource::ParameterSource(juce::AudioProcessorValueTreeState& apvts, const std::string& parameterId)
    : apvts_(apvts)
    , parameterId_(parameterId)
    {
        apvts_.addParameterListener(parameterId_, this);
    }

    ParameterSource::~ParameterSource()
    {
        apvts_.removeParameterListener(parameterId_, this);
    }

    void ParameterSource::addListener(IParameterSource::Listener* listener)
    {
        listeners_.insert(listener);
    }

    void ParameterSource::removeListener(IParameterSource::Listener* listener)
    {
        listeners_.erase(listener);
    }

    void ParameterSource::parameterChanged(const juce::String&, float value)
    {
        for(auto* listener : listeners_)
            listener->onParameterChanged(value);
    }
}
