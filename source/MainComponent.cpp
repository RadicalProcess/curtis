#include "MainComponent.h"

#include <juce_audio_utils/juce_audio_utils.h>
#include "ParameterSpecSet.h"

namespace rp::trevor
{
    using namespace juce;

    namespace
    {
        using SA = AudioProcessorValueTreeState::SliderAttachment;

        std::vector<std::unique_ptr<SA>>
        createAttachments(AudioProcessorValueTreeState& apvts, std::vector<std::unique_ptr<uicore::VerticalSlider>>& sliders)
        {
            auto attachments = std::vector<std::unique_ptr<SA>>();
            attachments.emplace_back(std::make_unique<SA>(apvts, getParameterSpec("HARMONIC1").id.data(), *sliders[0]));
            attachments.emplace_back(std::make_unique<SA>(apvts, getParameterSpec("HARMONIC2").id.data(), *sliders[1]));
            attachments.emplace_back(std::make_unique<SA>(apvts, getParameterSpec("HARMONIC3").id.data(), *sliders[2]));
            attachments.emplace_back(std::make_unique<SA>(apvts, getParameterSpec("HARMONIC4").id.data(), *sliders[3]));
            attachments.emplace_back(std::make_unique<SA>(apvts, getParameterSpec("HARMONIC5").id.data(), *sliders[4]));
            return attachments;
        }

        std::vector<std::unique_ptr<uicore::VerticalSlider>> createSliders()
        {
            auto&& sliders = std::vector<std::unique_ptr<uicore::VerticalSlider>>();
            for( auto i = 0; i < 5; ++i)
                sliders.emplace_back(std::make_unique<uicore::VerticalSlider>("HARMONIC_SLIDER_" + std::to_string(i)));
            return std::move(sliders);
        }
    }

    MainComponent::MainComponent(juce::AudioProcessorValueTreeState& apvts)
    : apvts_(apvts)
    , skipLabel_("SKIP_LABEL", getParameterSpec("SKIP").name.data())
    , skipSlider_("SKIP_SLIDER", 0, 5)
    , skipSliderAttachment_(apvts_, getParameterSpec("SKIP").id.data(), skipSlider_)
    , minLengthLabel_("MIN_LABEL", getParameterSpec("MIN_LENGTH").name.data())
    , minLengthSlider_("MIN_LENGTH_SLIDER", 0, getParameterSpec("MIN_LENGTH").unit.data())
    , minLengthSliderAttachment_(apvts_, getParameterSpec("MIN_LENGTH").id.data(), minLengthSlider_)
    , harmonicsLabel_("HARMONICS_LABEL", "harmonics")
    , harmonicsSliders_(createSliders())
    , harmonicsSliderAttachments_(createAttachments(apvts_, harmonicsSliders_))
    , dutyCycleLabel_("DUTY_CYCLE_LABEL", getParameterSpec("DUTY_CYCLE").name.data())
    , dutyCycleSlider_("DUTY_CYCLE_SLIDER", 0, getParameterSpec("DUTY_CYCLE").unit.data())
    , dutyCycleSliderAttachment_(apvts_, getParameterSpec("DUTY_CYCLE").id.data(), dutyCycleSlider_)
    , thresholdLabel_("THRESHOLD_LABEL", getParameterSpec("THRESHOLD").name.data())
    , thresholdSlider_("THRESHOLD_SLIDER", 0, getParameterSpec("THRESHOLD").unit.data())
    , thresholdSliderAttachment_(apvts_, getParameterSpec("THRESHOLD").id.data(), thresholdSlider_)
    , boostLabel_("BOOST_LABEL", getParameterSpec("BOOST").name.data())
    , boostSlider_("BOOST_SLIDER", 0, getParameterSpec("BOOST").unit.data())
    , boostSliderAttachment_(apvts_, getParameterSpec("BOOST").id.data(), boostSlider_)
    , gateLabel_("GATE_LABEL", getParameterSpec("GATE").name.data())
    , gateSlider_("GATE_SLIDER", 0, getParameterSpec("GATE").unit.data())
    , gateSliderAttachment_(apvts_, getParameterSpec("GATE").id.data(), gateSlider_)
    , dryLabel_("DRY_LABEL", getParameterSpec("DRY").name.data())
    , drySlider_("DRY_SLIDER", 0, getParameterSpec("DRY").unit.data())
    , drySliderAttachment_(apvts, getParameterSpec("DRY").id.data(), drySlider_)
    , wetLabel_("WET_LABEL", getParameterSpec("WET").name.data())
    , wetSlider_("WET_SLIDER", 0, getParameterSpec("WET").unit.data())
    , wetSliderAttachment_(apvts, getParameterSpec("WET").id.data(), wetSlider_)
    {

        {
            skipLabel_.setBounds(15, 205, 75, 20);
            addAndMakeVisible(skipLabel_);
            skipSlider_.setBounds(15, 225, 75, 80);
            addAndMakeVisible(skipSlider_);
        }

        {
            minLengthLabel_.setBounds(100, 205, 75, 20);
            addAndMakeVisible(minLengthLabel_);
            minLengthSlider_.setBounds(100, 225, 75, 80);
            minLengthSlider_.setRange(getParameterSpec("MIN_LENGTH").min, getParameterSpec("MIN_LENGTH").max);
            addAndMakeVisible(minLengthSlider_);
        }

        {
            harmonicsLabel_.setBounds(200, 205, 75, 20);
            addAndMakeVisible(harmonicsLabel_);

            for( auto i = static_cast<size_t>(0); i < harmonicsSliders_.size(); ++i)
            {
                harmonicsSliders_[i]->setBounds(200 + 16 * static_cast<int>(i), 225, 13, 73);
                harmonicsSliders_[i]->setRange(getParameterSpec("HARMONIC1").min, getParameterSpec("HARMONIC1").max);
                addAndMakeVisible(harmonicsSliders_[i].get());
            }
        }

        {
            dutyCycleLabel_.setBounds(290, 205, 75, 20);
            addAndMakeVisible(dutyCycleLabel_);
            dutyCycleSlider_.setBounds(290, 225, 75, 80);
            dutyCycleSlider_.setRange(getParameterSpec("DUTY_CYCLE").min, getParameterSpec("DUTY_CYCLE").max);
            addAndMakeVisible(dutyCycleSlider_);
        }

        {
            thresholdLabel_.setBounds(390, 205, 75, 20);
            addAndMakeVisible(thresholdLabel_);
            thresholdSlider_.setBounds(390, 225, 75, 80);
            thresholdSlider_.setRange(getParameterSpec("THRESHOLD").min, getParameterSpec("THRESHOLD").max);
            addAndMakeVisible(thresholdSlider_);
        }

        {
            boostLabel_.setBounds(475, 205, 75, 20);
            addAndMakeVisible(boostLabel_);
            boostSlider_.setBounds(475, 225, 75, 80);
            boostSlider_.setRange(getParameterSpec("BOOST").min, getParameterSpec("BOOST").max);
            addAndMakeVisible(boostSlider_);
        }

        {
            gateLabel_.setBounds(560, 205, 75, 20);
            addAndMakeVisible(gateLabel_);
            gateSlider_.setBounds(560, 225, 75, 80);
            gateSlider_.setRange(getParameterSpec("GATE").min, getParameterSpec("GATE").max);
            addAndMakeVisible(gateSlider_);
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

    void MainComponent::paint(juce::Graphics &g)
    {
        g.fillAll(juce::Colours::black);
    }

    void MainComponent::resized()
    {
    }
}
