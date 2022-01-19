#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace rp::trevor
{
    PluginEditor::PluginEditor(PluginProcessor& pluginProcessor)
    : AudioProcessorEditor(&pluginProcessor)
    {
        setSize(835, 315);
        addAndMakeVisible(mainComponent_);
    }

    PluginEditor::~PluginEditor()
    {
    }

    void PluginEditor::resized()
    {
    }
}
