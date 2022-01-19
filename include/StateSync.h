#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <engine/IParameterSync.h>
#include <engine/IParameterSetter.h>
#include <engine/IParameterSource.h>

namespace rp::trevor
{
    class StateSync : public IParameterSync
    {
    public:
        StateSync(juce::AudioProcessorValueTreeState& apvts, IParameterSetter& parameterSetter);

    private:
        struct SourceSync
        {
            ParameterSourcePtr parameterSource_;
            ParameterSyncPtr parameterSync_;
        };

        std::vector<SourceSync> sourceSyncs_;
    };
}
