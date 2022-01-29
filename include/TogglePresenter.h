#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include <UICore/ToggleButton.h>

namespace rp::curtis
{
    class TogglePresenter : public juce::Button::Listener
                            , public juce::AudioProcessorValueTreeState::Listener
    {
    public:
        TogglePresenter(juce::AudioProcessorValueTreeState& apvts, juce::Button& button);

        ~TogglePresenter() override;

        void parameterChanged(const juce::String& parameterID, float newValue) override;

        void buttonStateChanged(juce::Button* button) override;

        void buttonClicked(juce::Button* button) override;

    private:
        juce::AudioProcessorValueTreeState& apvts_;
        juce::Button& button_;
    };
}
