#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

namespace rp::trevor
{
    class PresetManager
    {
    public:
        PresetManager(juce::AudioProcessorValueTreeState& apvts);

        void apply(int index);

        const std::string& getName(int index);

        int getSelection() const;

        int getNumberOfPresents() const;

    private:
        juce::AudioProcessorValueTreeState& apvts_;
        size_t currentSelection_;
    };
}