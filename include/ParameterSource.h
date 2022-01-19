#pragma once

#include <set>

#include <juce_audio_utils/juce_audio_utils.h>

#include "IParameterSource.h"

namespace rp::curtis
{
    class ParameterSource : public IParameterSource
                          , public juce::AudioProcessorValueTreeState::Listener
    {
    public:
        ParameterSource(juce::AudioProcessorValueTreeState& apvts, const std::string& parameterId);

        ~ParameterSource() override;

        void addListener(IParameterSource::Listener* listener) override;

        void removeListener(IParameterSource::Listener* listener) override;

        void parameterChanged(const juce::String& parameterID, float value) override;

    private:
        juce::AudioProcessorValueTreeState& apvts_;

        const std::string parameterId_;

        std::set<IParameterSource::Listener*> listeners_;
    };
}
