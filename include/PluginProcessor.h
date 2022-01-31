#pragma once

#include <set>
#include <mutex>
#include <thread>

#include <juce_audio_processors/juce_audio_processors.h>
#include <curtis_core/IVisualizationDataProvider.h>

#include "EngineManager.h"
#include "StateSync.h"
#include "PresetManager.h"
namespace rp::curtis
{
    class PluginProcessor : public juce::AudioProcessor
                          , public IVisualizationDataProvider
    {
    public:
        PluginProcessor();

        ~PluginProcessor() override = default;

        void prepareToPlay(double sampleRate, int samplesPerBlock) override;
        void releaseResources() override;
        bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
        void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
        using AudioProcessor::processBlock;
        juce::AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override;
        const juce::String getName() const override;
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        bool isMidiEffect() const override;
        double getTailLengthSeconds() const override;
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram(int index) override;
        const juce::String getProgramName(int index) override;
        void changeProgramName(int index, const juce::String& newName) override;
        void getStateInformation(juce::MemoryBlock& destData) override;
        void setStateInformation(const void* data, int sizeInBytes) override;
        juce::AudioProcessorValueTreeState& getAudioProcessorValueTreeState();

        const std::vector<VisualizationDataSet>& getVisualizationDataSets() override;

    private:
        juce::AudioProcessorValueTreeState apvts_;
        PresetManager presetManager_;
        ParameterSyncPtr stateSync_;
        std::unique_ptr<EngineManager>  engineManager_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
    };
}
