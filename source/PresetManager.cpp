#include "PresetManager.h"
#include "Preset.h"

namespace rp::curtis
{
    PresetManager::PresetManager(juce::AudioProcessorValueTreeState& apvts)
    : apvts_(apvts)
    {
    }

    void PresetManager::apply(int index)
    {
//        currentSelection_ = static_cast<size_t>(index);
//        const auto& selectedPreset = presets[currentSelection_];
//
//        auto skipParameter = apvts_.getParameter("SKIP");
//        skipParameter->setValueNotifyingHost(skipParameter->convertTo0to1(static_cast<float>(selectedPreset.skip)));
//
//        auto minLengthParameter = apvts_.getParameter("MIN_LENGTH");
//        minLengthParameter->setValueNotifyingHost(minLengthParameter->convertTo0to1(selectedPreset.minLength));
//
//        auto harmonic1Parameter = apvts_.getParameter("HARMONIC1");
//        harmonic1Parameter->setValueNotifyingHost(harmonic1Parameter->convertTo0to1(selectedPreset.harmonic1));
//
//        auto harmonic2Parameter = apvts_.getParameter("HARMONIC2");
//        harmonic2Parameter->setValueNotifyingHost(harmonic2Parameter->convertTo0to1(selectedPreset.harmonic2));
//
//        auto harmonic3Parameter = apvts_.getParameter("HARMONIC3");
//        harmonic3Parameter->setValueNotifyingHost(harmonic3Parameter->convertTo0to1(selectedPreset.harmonic3));
//
//        auto harmonic4Parameter = apvts_.getParameter("HARMONIC4");
//        harmonic4Parameter->setValueNotifyingHost(harmonic4Parameter->convertTo0to1(selectedPreset.harmonic4));
//
//        auto harmonic5Parameter = apvts_.getParameter("HARMONIC5");
//        harmonic5Parameter->setValueNotifyingHost(harmonic5Parameter->convertTo0to1(selectedPreset.harmonic5));
//
//        auto dutyCycleParameter = apvts_.getParameter("DUTY_CYCLE");
//        dutyCycleParameter->setValueNotifyingHost(dutyCycleParameter->convertTo0to1(selectedPreset.dutyCycle));
//
//        auto thresholdParameter = apvts_.getParameter("THRESHOLD");
//        thresholdParameter->setValueNotifyingHost(thresholdParameter->convertTo0to1(selectedPreset.threshold));
//
//        auto boostParameter = apvts_.getParameter("BOOST");
//        boostParameter->setValueNotifyingHost(boostParameter->convertTo0to1(selectedPreset.boost));
//
//        auto gateParameter = apvts_.getParameter("GATE");
//        gateParameter->setValueNotifyingHost(gateParameter->convertTo0to1(selectedPreset.gate));
//
//        auto dryParameter = apvts_.getParameter("DRY");
//        dryParameter->setValueNotifyingHost(dryParameter->convertTo0to1(selectedPreset.dry));
//
//        auto wetParameter = apvts_.getParameter("WET");
//        wetParameter->setValueNotifyingHost(wetParameter->convertTo0to1(selectedPreset.wet));
    }

    const std::string& PresetManager::getName(int index)
    {
        return presets[static_cast<size_t>(index)].name;
    }

    int PresetManager::getSelection() const
    {
        return static_cast<int>(currentSelection_);
    }

    int PresetManager::getNumberOfPresets() const
    {
        return static_cast<int>(presets.size());
    }
}
