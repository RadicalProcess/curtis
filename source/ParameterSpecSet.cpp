#include "ParameterSpecSet.h"
#include <juce_audio_basics/juce_audio_basics.h>

namespace rp::curtis
{
    const std::vector<ParameterSpec> parameterSpecSet{
            ParameterSpec{"input", "INPUT_MIX", "", ParameterSpec::Float, -100.f, 100.f, -100.f,
                          [](Curtis& curtis, float value){ curtis.setMix(value / 100.0f);}},
            ParameterSpec{"segment min", "SEGMENT_MIN", "ms", ParameterSpec::Float, 5.f, 1000.f, 50.f,
                          [](Curtis& curtis, float value){ curtis.setSegmentMinLength(value);}},
            ParameterSpec{"repeat", "REPEAT", "", ParameterSpec::Int, 0.f, 10.f, 0.f,
                          [](Curtis& curtis, float count){ curtis.setRepeat(static_cast<size_t>(count));}},
            ParameterSpec{"random", "RANDOM", "", ParameterSpec::Int, 0.0f, 30.0f, 0,
                          [](Curtis& curtis, float random){ curtis.setRandomRange(static_cast<size_t>(random));}},
            ParameterSpec{"density", "DENSITY", "%", ParameterSpec::Int, 0.0f, 100.f, 100.f,
                          [](Curtis& curtis, float percentage){ curtis.setDensity(static_cast<int>(percentage));}},
            ParameterSpec{"glisson", "GLISSON", "", ParameterSpec::Bool,0.f, 1.f, 1.f,
                          [](Curtis& curtis, float value){ curtis.setGlissonEnabled(value > 0.0f);}},
            ParameterSpec{"start pitch A", "START_PITCH_A", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setStartSpeedA(std::powf(2, semitone / 12.0f));}},
            ParameterSpec{"start pitch B", "START_PITCH_B", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setStartSpeedB(std::powf(2, semitone / 12.0f));}},
            ParameterSpec{"end pitch A", "END_PITCH_A", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setEndSpeedA(std::powf(2, semitone / 12.0f));}},
            ParameterSpec{"end pitch B", "END_PITCH_B", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setEndSpeedB(std::powf(2, semitone / 12.0f));}},
            ParameterSpec{"start position A", "START_POSITION_A", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setStartPositionA(position);}},
            ParameterSpec{"start position B", "START_POSITION_B", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setStartPositionB(position);}},
            ParameterSpec{"end position A", "END_POSITION_A", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setEndPositionA(position);}},
            ParameterSpec{"end position B", "END_POSITION_B", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setEndPositionB(position);}},
            ParameterSpec{"dry", "DRY", "dB", ParameterSpec::Float, -96.f, 6.f, -96.f,
                          [](Curtis& curtis, float decibel){ curtis.setDry(juce::Decibels::decibelsToGain(decibel));}},
            ParameterSpec{"wet", "WET", "dB", ParameterSpec::Float, -96.f, 6.f, 0.0f,
                          [](Curtis& curtis, float decibel){ curtis.setWet(juce::Decibels::decibelsToGain(decibel));}}
    };

    const ParameterSpec& getParameterSpec(std::string_view id)
    {
        auto itr = std::find_if(parameterSpecSet.begin(), parameterSpecSet.end(), [id](const ParameterSpec& parameterSpec){
            return parameterSpec.id == id;
        });

        if (itr == parameterSpecSet.end())
            throw std::out_of_range("no such parameter spec");

        return *itr;
    }
}
