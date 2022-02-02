#include "PluginEditor.h"

#include "PluginProcessor.h"
#include "ParameterSpecSet.h"

namespace rp::curtis
{

    using namespace juce;

    PluginEditor::PluginEditor(PluginProcessor& pluginProcessor)
    : juce::AudioProcessorEditor(pluginProcessor)
    , apvts_(pluginProcessor.getAudioProcessorValueTreeState())
    , visualizer_(pluginProcessor)
    , inputMixLabel_("INPUT_MIN", getParameterSpec("INPUT_MIX").name.data())
    , inputMixSlider_("INPUT_MIX", 0, "")
    , inputMixSliderAttachment_(apvts_, getParameterSpec("INPUT_MIX").id.data(), inputMixSlider_)
    , segmentMinLabel_("SEGMENT_MIN", getParameterSpec("SEGMENT_MIN").name.data())
    , segmentMinSlider_("SEGMENT_MIN", 0, "ms")
    , segmentMinSliderAttachment_(apvts_, getParameterSpec("SEGMENT_MIN").id.data(), segmentMinSlider_)
    , randomLabel_("RANDOM", getParameterSpec("RANDOM").name.data())
    , randomSlider_("RANDOM", 0, 30)
    , randomSliderAttachment_(apvts_, getParameterSpec("RANDOM").id.data(), randomSlider_)
    , glissonToggle_("GLISSON_TOGGLE")
    , togglePresenter_(apvts_, glissonToggle_)
    , glissonLabel_("GLISSON", "glisson")
    , glissonSlider_()
    , glissonPresenter_(apvts_, glissonSlider_)
    , repeatLabel_("REPEAT", getParameterSpec("REPEAT").name.data())
    , repeatSlider_("REPEAT", 0, 10)
    , repeatSliderAttachment_(apvts_, getParameterSpec("REPEAT").id.data(), repeatSlider_)
    , densityLabel_("DENSITY", getParameterSpec("DENSITY").name.data())
    , densitySlider_("DENSITY", 0)
    , densitySliderAttachment_(apvts_, getParameterSpec("DENSITY").id.data(), densitySlider_)
    , dryLabel_("DRY_LABEL", getParameterSpec("DRY").name.data())
    , drySlider_("DRY_SLIDER", 0, getParameterSpec("DRY").unit.data())
    , drySliderAttachment_(apvts_, getParameterSpec("DRY").id.data(), drySlider_)
    , wetLabel_("WET_LABEL", getParameterSpec("WET").name.data())
    , wetSlider_("WET_SLIDER", 0, getParameterSpec("WET").unit.data())
    , wetSliderAttachment_(apvts_, getParameterSpec("WET").id.data(), wetSlider_)
    {
        setSize(733, 215);
        {
            visualizer_.setBounds(0, 0, 733, 100);
            addAndMakeVisible(visualizer_);
        }

        {
            inputMixLabel_.setBounds(15, 102, 75, 20);
            addAndMakeVisible(inputMixLabel_);
            inputMixSlider_.setBounds(15, 125, 75, 80);
            addAndMakeVisible(inputMixSlider_);
        }

        {
            segmentMinLabel_.setBounds(100, 102, 75, 20);
            addAndMakeVisible(segmentMinLabel_);
            segmentMinSlider_.setSkewFactor(0.5f);
            segmentMinSlider_.setBounds(100, 125, 75, 80);
            segmentMinSlider_.setRange(getParameterSpec("SEGMENT_MIN").min, getParameterSpec("SEGMENT_MIN").max);
            addAndMakeVisible(segmentMinSlider_);
        }

        {
            randomLabel_.setBounds(185, 102, 75, 20);
            addAndMakeVisible(randomLabel_);
            randomSlider_.setBounds(185, 125, 75, 80);
            addAndMakeVisible(randomSlider_);
        }

        {
            glissonLabel_.setBounds(270, 102, 110, 20);
            addAndMakeVisible(glissonLabel_);

            glissonToggle_.setBounds(293, 108, 10, 10);
            addAndMakeVisible(glissonToggle_);
            glissonSlider_.setBounds(270, 125, 110, 80);
            addAndMakeVisible(glissonSlider_);
        }

        {
            repeatLabel_.setBounds(390, 102, 75, 20);
            addAndMakeVisible(repeatLabel_);
            repeatSlider_.setBounds(390, 125, 75, 80);
            addAndMakeVisible(repeatSlider_);
        }

        {
            densityLabel_.setBounds(475, 102, 75, 20);
            addAndMakeVisible(densityLabel_);
            densitySlider_.setBounds(475, 125, 75, 80);
            addAndMakeVisible(densitySlider_);
        }

        {
            dryLabel_.setBounds(560, 102, 75, 20);
            addAndMakeVisible(dryLabel_);
            drySlider_.setSkewFactor(3.0f);
            drySlider_.setBounds(560, 125, 75, 80);
            drySlider_.setRange(getParameterSpec("DRY").min, getParameterSpec("DRY").max);
            addAndMakeVisible(drySlider_);
        }

        {
            wetLabel_.setBounds(645, 102, 75, 20);
            addAndMakeVisible(wetLabel_);
            wetSlider_.setBounds(645, 125, 75, 80);
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
