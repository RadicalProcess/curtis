#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include <UICore/RotarySlider.h>
#include <UICore/StraightSlider.h>
#include <UICore/StepSlider.h>
#include <UICore/Label.h>
#include <UICore/TextField.h>
#include <UICore/ToggleButton.h>
#include <UICore/GlissonSlider/Slider.h>
#include <visualizer/Visualizer.h>
#include "PluginProcessor.h"
#include "IParameterSetter.h"
#include "GlissonPresenter.h"
#include "TogglePresenter.h"

namespace rp::curtis
{
    class PluginEditor : public juce::AudioProcessorEditor
    {
    public:
        explicit PluginEditor(PluginProcessor&);

    private:
        void paint(juce::Graphics& g) override;

        juce::AudioProcessorValueTreeState& apvts_;

        Visualizer visualizer_;

        uicore::Label inputMixLabel_;
        uicore::CenterDefaultRotarySlider inputMixSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment inputMixSliderAttachment_;

        uicore::Label segmentMinLabel_;
        uicore::StandardRotarySlider segmentMinSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment segmentMinSliderAttachment_;

        uicore::Label randomLabel_;
        uicore::StepSlider randomSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment randomSliderAttachment_;

        uicore::ToggleButton glissonToggle_;
        const TogglePresenter togglePresenter_;

        uicore::Label glissonLabel_;
        uicore::glisson::Slider glissonSlider_;
        const GlissonPresenter glissonPresenter_;

        uicore::Label repeatLabel_;
        uicore::StepSlider repeatSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment repeatSliderAttachment_;

        uicore::Label densityLabel_;
        uicore::StandardRotarySlider densitySlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment densitySliderAttachment_;

        uicore::Label dryLabel_;
        uicore::DecibelRotarySlider drySlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment drySliderAttachment_;

        uicore::Label wetLabel_;
        uicore::DecibelRotarySlider wetSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment wetSliderAttachment_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
    };
}
