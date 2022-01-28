#include "ParameterSpecSet.h"

namespace rp::curtis
{
    const std::vector<ParameterSpec> parameterSpecSet{
            ParameterSpec{"input", "INPUT_MIX", "", ParameterSpec::Float, -100.f, 100.f, 0.f,
                          [](Curtis& curtis, float value){ curtis.setMix(value);}},
            ParameterSpec{"segment min", "SEGMENT_MIN", "ms", ParameterSpec::Float, 5.f, 100.f, 50.f,
                          [](Curtis& curtis, float value){ curtis.setSegmentMinLength(value);}},
            ParameterSpec{"repeat min", "REPEAT_MIN", "", ParameterSpec::Int, 0.f, 10.f, 0.f,
                          [](Curtis& curtis, float count){ curtis.setRepeatMin(static_cast<size_t>(count));}},
            ParameterSpec{"repeat max", "REPEAT_MAX", "", ParameterSpec::Int, 0.f, 10.f, 0.f,
                          [](Curtis& curtis, float count){ curtis.setRepeatMin(static_cast<size_t>(count));}},
            ParameterSpec{"random", "RANDOM", "", ParameterSpec::Int, 0.0f, 30.0f, 0,
                          [](Curtis& curtis, float random){ curtis.setRandomRange(static_cast<size_t>(random));}},
            ParameterSpec{"density", "DENSITY", "%", ParameterSpec::Int, 0.0f, 100.f, 100.f,
                          [](Curtis& curtis, float percentage){ curtis.setDensity(static_cast<int>(percentage));}},
            ParameterSpec{"glisson", "GLISSON", "", ParameterSpec::Bool,0.f, 1.f, 1.f,
                          [](Curtis& curtis, float value){ curtis.setGlissonEnabled(value > 0.0f);}},
            ParameterSpec{"start pitch min", "START_PITCH_MIN", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setStartMinSpeed(std::powf(2, semitone/12.0f));}},
            ParameterSpec{"start pitch max", "START_PITCH_MAX", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setStartMaxSpeed(std::powf(2, semitone/12.0f));}},
            ParameterSpec{"end pitch min", "END_PITCH_MIN", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setEndMinSpeed(std::powf(2, semitone/12.0f));}},
            ParameterSpec{"end pitch max", "END_PITCH_MAX", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](Curtis& curtis, float semitone){ curtis.setEndMaxSpeed(std::powf(2, semitone/12.0f));}},
            ParameterSpec{"start position left", "START_POSITION_LEFT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setStartLeft(position);}},
            ParameterSpec{"start position right", "START_POSITION_RIGHT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setStartRight(position);}},
            ParameterSpec{"end position left", "END_POSITION_LEFT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setEndLeft(position);}},
            ParameterSpec{"end position right", "END_POSITION_RIGHT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](Curtis& curtis, float position){ curtis.setEndRight(position);}},
            ParameterSpec{"dry", "DRY", "dB", ParameterSpec::Float, -96.f, 6.f, -96.f,
                          [](Curtis& curtis, float decibel){}},
            ParameterSpec{"wet", "WET", "dB", ParameterSpec::Float, -96.f, 6.f, 0.0f,
                          [](Curtis& curtis, float decibel){}}
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
