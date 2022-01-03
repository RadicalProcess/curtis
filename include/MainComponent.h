#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include <UICore/RotarySlider.h>
#include <UICore/StraightSlider.h>
#include <UICore/StepSlider.h>
#include <UICore/Label.h>
#include <UICore/TextField.h>

#include <engine/IParameterSetter.h>
#include <engine/IVisualizationDataProvider.h>

#include "LineVisibilityResponder.h"
#include "LinePresenter.h"

namespace rp::trevor
{
    class MainComponent : public juce::Component
    {
    public:
        explicit MainComponent(juce::AudioProcessorValueTreeState& apvts, IVisualizationDataProvider& visualizationDataProvider);

        void paint(juce::Graphics &) override;

        void resized() override;

    private:
        juce::AudioProcessorValueTreeState& apvts_;

        Visualizer visualizerL_;
        Visualizer visualizerR_;

        uicore::Label skipLabel_;
        uicore::StepSlider skipSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment skipSliderAttachment_;

        uicore::Label minLengthLabel_;
        uicore::StandardRotarySlider minLengthSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment minLengthSliderAttachment_;

        uicore::Label harmonicsLabel_;
        std::vector<std::unique_ptr<uicore::VerticalSlider>> harmonicsSliders_;
        std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> harmonicsSliderAttachments_;

        uicore::Label dutyCycleLabel_;
        uicore::StandardRotarySlider dutyCycleSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment dutyCycleSliderAttachment_;

        uicore::Label thresholdLabel_;
        uicore::DecibelRotarySlider thresholdSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment thresholdSliderAttachment_;

        uicore::Label boostLabel_;
        uicore::StandardRotarySlider boostSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment boostSliderAttachment_;

        uicore::Label gateLabel_;
        uicore::DecibelRotarySlider gateSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment gateSliderAttachment_;

        uicore::Label dryLabel_;
        uicore::DecibelRotarySlider drySlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment drySliderAttachment_;

        uicore::Label wetLabel_;
        uicore::DecibelRotarySlider wetSlider_;
        const juce::AudioProcessorValueTreeState::SliderAttachment wetSliderAttachment_;

        juce::Image logoImage_;

        LineVisibilityResponder lineVisibilityResponderL_, lineVisibilityResponderR_;
        LinePresenter linePresenterL_, linePresenterR_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
    };
}
