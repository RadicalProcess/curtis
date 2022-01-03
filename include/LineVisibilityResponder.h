#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <visualizer/Visualizer.h>

namespace rp::trevor
{
    class LineVisibilityResponder : public juce::MouseListener
    {
    public:
        LineVisibilityResponder(juce::Slider& thresholdSlider, juce::Slider& gateSlider, Visualizer& visualizer);

        ~LineVisibilityResponder() override;

    private:
        void mouseEnter(const juce::MouseEvent& event) override;

        void mouseExit(const juce::MouseEvent& event) override;

        juce::Slider& thresholdSlider_;
        juce::Slider& gateSlider_;
        Visualizer& visualizer_;
    };
}
