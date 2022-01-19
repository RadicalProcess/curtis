#pragma once

#include "PluginProcessor.h"

namespace rp::trevor
{
    class PluginEditor : public juce::AudioProcessorEditor
    {
    public:
        explicit PluginEditor(PluginProcessor&);

        ~PluginEditor() override;

        void resized() override;

    private:

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
    };
}
