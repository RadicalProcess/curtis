#include "PluginProcessor.h"

#include "ParameterSpecSet.h"

#include "PluginEditor.h"
#include "StateSync.h"

namespace rp::curtis
{
    namespace
    {
        using namespace juce;
        AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
        {
            auto layout = AudioProcessorValueTreeState::ParameterLayout();
            for(auto& parameterSpec : parameterSpecSet)
            {
                switch(parameterSpec.type)
                {
                    case ParameterSpec::Float:
                    {
                        layout.add(std::make_unique<AudioParameterFloat>(parameterSpec.id.data(),
                                                                         parameterSpec.name.data(),
                                                                         parameterSpec.min,
                                                                         parameterSpec.max,
                                                                         parameterSpec.init));
                        break;
                    }
                    case ParameterSpec::Int:
                    {
                        layout.add(std::make_unique<AudioParameterInt>(parameterSpec.id.data(),
                                                                         parameterSpec.name.data(),
                                                                         static_cast<int>(parameterSpec.min),
                                                                         static_cast<int>(parameterSpec.max),
                                                                         static_cast<int>(parameterSpec.init)));
                        break;
                    }
                    default:
                        throw std::out_of_range("no such type");
                }
            }
            return layout;
        }
    }

    PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , apvts_(*this, nullptr, "PARAMETERS", createParameterLayout())
    , presetManager_(apvts_)
    {
    }

    void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
    {
        const auto channelCount = std::max(getTotalNumInputChannels(), getTotalNumOutputChannels());
        const auto factor = static_cast<int>(sampleRate / 22050.0);
        const auto timeout = factor * 1024;
        setLatencySamples(samplesPerBlock + timeout * 2);

        {
            const auto lock = std::lock_guard(mutex_);

        }
        stateSync_ = std::make_unique<StateSync>(apvts_,*engine_);
    }

    bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
    {
        if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()
            && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
            return false;

        return true;
    }

    void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& )
    {
        engine_->process(buffer.getArrayOfWritePointers(), static_cast<size_t>(buffer.getNumSamples()));
    }

    bool PluginProcessor::hasEditor() const
    {
        return true; // (change this to false if you choose to not supply an editor)
    }

    juce::AudioProcessorEditor* PluginProcessor::createEditor()
    {
        return new PluginEditor(*this);
    }

    void PluginProcessor::getStateInformation(juce::MemoryBlock& destData)
    {
        const auto state = apvts_.copyState();
        const auto xml = std::unique_ptr<juce::XmlElement>(state.createXml());
        copyXmlToBinary (*xml, destData);
    }

    void PluginProcessor::setStateInformation(const void* data, int sizeInBytes)
    {
        const auto xmlState = std::unique_ptr<juce::XmlElement>(getXmlFromBinary(data, sizeInBytes));

        if(xmlState != nullptr)
            if (xmlState->hasTagName(apvts_.state.getType()))
                apvts_.replaceState(juce::ValueTree::fromXml(*xmlState));
    }

    juce::AudioProcessorValueTreeState& PluginProcessor::getAudioProcessorValueTreeState()
    {
        return apvts_;
    }

    const juce::String PluginProcessor::getName() const {return JucePlugin_Name;}
    bool PluginProcessor::acceptsMidi() const { return false; }
    bool PluginProcessor::producesMidi() const { return false; }
    bool PluginProcessor::isMidiEffect() const { return false; }
    double PluginProcessor::getTailLengthSeconds() const { return 0.0; }
    int PluginProcessor::getNumPrograms(){ return presetManager_.getNumberOfPresets(); }
    int PluginProcessor::getCurrentProgram(){ return presetManager_.getSelection(); }
    void PluginProcessor::setCurrentProgram(int index){ presetManager_.apply(index); }
    const juce::String PluginProcessor::getProgramName(int index ){ return presetManager_.getName(index);}
    void PluginProcessor::changeProgramName(int , const juce::String&){}
    void PluginProcessor::releaseResources(){}

}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new rp::curtis::PluginProcessor();
}
