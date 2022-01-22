#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterSpecSet.h"

namespace rp::curtis
{

    using namespace juce;

    PluginEditor::PluginEditor(PluginProcessor& pluginProcessor)
    : juce::AudioProcessorEditor(pluginProcessor)
    , apvts_(pluginProcessor.getAudioProcessorValueTreeState())
    , segmentMinLabel_("SEGMENT_MIN", getParameterSpec("SEGMENT_MIN").name.data())
    , segmentMinSlider_("SEGMENT_MIN", 0, "ms")
    , segmentMinSliderAttachment_(apvts_, getParameterSpec("SEGMENT_MIN").id.data(), segmentMinSlider_)
    , randomLabel_("RANDOM", getParameterSpec("RANDOM").name.data())
    , randomSlider_("RANDOM", 0)
    , randomSliderAttachment_(apvts_, getParameterSpec("RANDOM").id.data(), randomSlider_)
    , repeatLabel_("REPEAT", "Repeat")
    , repeatSlider_("REPEAT")
    , dryLabel_("DRY_LABEL", getParameterSpec("DRY").name.data())
    , drySlider_("DRY_SLIDER", 0, getParameterSpec("DRY").unit.data())
    , drySliderAttachment_(apvts_, getParameterSpec("DRY").id.data(), drySlider_)
    , wetLabel_("WET_LABEL", getParameterSpec("WET").name.data())
    , wetSlider_("WET_SLIDER", 0, getParameterSpec("WET").unit.data())
    , wetSliderAttachment_(apvts_, getParameterSpec("WET").id.data(), wetSlider_)
    {
        setSize(835, 315);

        {
            segmentMinLabel_.setBounds(15, 205, 75, 20);
            addAndMakeVisible(segmentMinLabel_);
            segmentMinSlider_.setBounds(15, 225, 75, 80);
            addAndMakeVisible(segmentMinSlider_);
        }

        {
            randomLabel_.setBounds(105, 205, 75, 20);
            addAndMakeVisible(randomLabel_);
            randomSlider_.setBounds(105, 225, 75, 80);
            addAndMakeVisible(randomSlider_);
        }

        {
            repeatLabel_.setBounds(195, 205, 75, 20);
            addAndMakeVisible(repeatLabel_);
            repeatSlider_.setBounds(195, 225, 75, 80);
            addAndMakeVisible(repeatSlider_);
        }

        {
            dryLabel_.setBounds(660, 205, 75, 20);
            addAndMakeVisible(dryLabel_);
            drySlider_.setSkewFactor(3.0f);
            drySlider_.setBounds(660, 225, 75, 80);
            drySlider_.setRange(getParameterSpec("DRY").min, getParameterSpec("DRY").max);
            addAndMakeVisible(drySlider_);
        }

        {
            wetLabel_.setBounds(745, 205, 75, 20);
            addAndMakeVisible(wetLabel_);
            wetSlider_.setBounds(745, 225, 75, 80);
            wetSlider_.setSkewFactor(3.0f);
            wetSlider_.setRange(getParameterSpec("WET").min, getParameterSpec("WET").max);
            addAndMakeVisible(wetSlider_);
        }
    }

    void PluginEditor::paint(juce::Graphics &g)
    {
        g.fillAll(juce::Colours::black);
    }
}
