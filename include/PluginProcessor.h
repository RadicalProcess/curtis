#pragma once

#include <set>
#include <mutex>
#include <thread>

#include <juce_audio_processors/juce_audio_processors.h>


#include "PresetManager.h"

namespace rp::trevor
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

    private:

        juce::AudioProcessorValueTreeState apvts_;
        EngineManagerPtr engineManager_;
        ParameterSyncPtr stateSync_;
        PresetManager presetManager_;
        std::unique_ptr<Validator> validator_;

        std::mutex mutex_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
    };
}
