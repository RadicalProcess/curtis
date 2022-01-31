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
        currentSelection_ = static_cast<size_t>(index);
        const auto& selectedPreset = presets[currentSelection_];

        auto inputMixParameter = apvts_.getParameter("INPUT_MIX");
        inputMixParameter->setValueNotifyingHost(inputMixParameter->convertTo0to1(static_cast<float>(selectedPreset.inputMix)));

        auto segmentMinParameter = apvts_.getParameter("SEGMENT_MIN");
        segmentMinParameter->setValueNotifyingHost(segmentMinParameter->convertTo0to1(selectedPreset.segmentMin));

        auto repeatParameter = apvts_.getParameter("REPEAT");
        repeatParameter->setValueNotifyingHost(repeatParameter->convertTo0to1(static_cast<float>(selectedPreset.repeat)));

        auto randomParameter = apvts_.getParameter("RANDOM");
        randomParameter->setValueNotifyingHost(randomParameter->convertTo0to1(static_cast<float>(selectedPreset.random)));

        auto densityParameter = apvts_.getParameter("DENSITY");
        densityParameter->setValueNotifyingHost(densityParameter->convertTo0to1(static_cast<float>(selectedPreset.density)));

        auto glissonParameter = apvts_.getParameter("GLISSON");
        glissonParameter->setValueNotifyingHost(glissonParameter->convertTo0to1(selectedPreset.glisson));

        auto startPitchAParameter = apvts_.getParameter("START_PITCH_A");
        startPitchAParameter->setValueNotifyingHost(startPitchAParameter->convertTo0to1(selectedPreset.startPitchA));

        auto startPitchBarameter = apvts_.getParameter("START_PITCH_B");
        startPitchBarameter->setValueNotifyingHost(startPitchBarameter->convertTo0to1(selectedPreset.startPitchB));

        auto endPitchAParameter = apvts_.getParameter("END_PITCH_A");
        endPitchAParameter->setValueNotifyingHost(endPitchAParameter->convertTo0to1(selectedPreset.endPitchA));

        auto endPitchBParameter = apvts_.getParameter("END_PITCH_B");
        endPitchBParameter->setValueNotifyingHost(endPitchBParameter->convertTo0to1(selectedPreset.endPitchB));

        auto startPositionAParameter = apvts_.getParameter("START_POSITION_A");
        startPositionAParameter->setValueNotifyingHost(startPositionAParameter->convertTo0to1(selectedPreset.startPositionA));

        auto startPositionBParameter = apvts_.getParameter("START_POSITION_B");
        startPositionBParameter->setValueNotifyingHost(startPositionBParameter->convertTo0to1(selectedPreset.startPositionB));

        auto endPositionAParameter = apvts_.getParameter("END_POSITION_A");
        endPositionAParameter->setValueNotifyingHost(endPositionAParameter->convertTo0to1(selectedPreset.endPositionA));

        auto endPositionBParameter = apvts_.getParameter("END_POSITION_B");
        endPositionBParameter->setValueNotifyingHost(endPositionBParameter->convertTo0to1(selectedPreset.endPositionB));

        auto dryParameter = apvts_.getParameter("DRY");
        dryParameter->setValueNotifyingHost(dryParameter->convertTo0to1(selectedPreset.dry));

        auto wetParameter = apvts_.getParameter("WET");
        wetParameter->setValueNotifyingHost(wetParameter->convertTo0to1(selectedPreset.wet));
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
