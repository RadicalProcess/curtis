#pragma once

#include "PluginProcessor.h"
#include "MainComponent.h"

namespace rp::curtis
{
    class PluginEditor : public juce::AudioProcessorEditor
    {
    public:
        explicit PluginEditor(PluginProcessor&);

        ~PluginEditor() override;

        void resized() override;

    private:

        MainComponent mainComponent_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
    };
}
