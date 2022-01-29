#pragma once

#include <unordered_map>
#include <juce_audio_utils/juce_audio_utils.h>
#include <UICore/GlissonSlider/Slider.h>
#include <UICore/GlissonSlider/KnobId.h>

namespace rp::curtis
{
    class GlissonPresenter : public juce::AudioProcessorValueTreeState::Listener
                            , public uicore::glisson::Slider::Listener
    {
    public:
        GlissonPresenter(juce::AudioProcessorValueTreeState& apvts, uicore::glisson::Slider& slider);

        ~GlissonPresenter() override;

    private:

        void parameterChanged(const juce::String& parameterID, float newValue) override;

        void onSliderValueChanged(uicore::glisson::KnobId knobId, float value) override;

        juce::AudioProcessorValueTreeState& apvts_;
        rp::uicore::glisson::Slider& slider_;
        std::vector<std::pair<uicore::glisson::KnobId, juce::String>> map_;
    };
}
