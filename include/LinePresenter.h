#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <visualizer/Visualizer.h>

namespace rp::trevor
{
    class LinePresenter: public juce::AudioProcessorValueTreeState::Listener
    {
    public:
        LinePresenter(Visualizer& visualizer, juce::AudioProcessorValueTreeState& apvts);

        ~LinePresenter() override;

        void parameterChanged(const juce::String& parameterID, float percentage) override;

    private:
        Visualizer& visualizer_;
        juce::AudioProcessorValueTreeState& apvts_;
        const std::function<void(Visualizer&, float value)> func_;
    };
}
