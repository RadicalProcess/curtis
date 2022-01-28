#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include <UICore/RotarySlider.h>
#include <UICore/StraightSlider.h>
#include <UICore/StepSlider.h>
#include <UICore/Label.h>
#include <UICore/TextField.h>
#include <UICore/ToggleButton.h>
#include <UICore/GlissonSlider/Slider.h>

#include "PluginProcessor.h"
#include "IParameterSetter.h"

namespace rp::curtis
{
    class PluginEditor : public juce::AudioProcessorEditor
    {
    public:
        explicit PluginEditor(PluginProcessor&);

    private:
        void paint(juce::Graphics& g) override;

        juce::AudioProcessorValueTreeState& apvts_;

        uicore::Label inputMixLabel_;
        uicore::CenterDefaultRotarySlider inputMixSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment inputMixSliderAttachment_;

        uicore::Label segmentMinLabel_;
        uicore::StandardRotarySlider segmentMinSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment segmentMinSliderAttachment_;

        uicore::Label randomLabel_;
        uicore::StandardRotarySlider randomSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment randomSliderAttachment_;

        uicore::ToggleButton glissonToggle_;
        uicore::Label glissonLabel_;
        uicore::glisson::Slider glissonSlider_;

        uicore::Label repeatLabel_;
        uicore::StandardRotarySlider repeatSlider_;

        uicore::Label dryLabel_;
        uicore::DecibelRotarySlider drySlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment drySliderAttachment_;

        uicore::Label wetLabel_;
        uicore::DecibelRotarySlider wetSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment wetSliderAttachment_;


        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
    };
}
