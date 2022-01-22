#include "ParameterSpecSet.h"

namespace rp::curtis
{
    const std::vector<ParameterSpec> parameterSpecSet{
            ParameterSpec{"segment min", "SEGMENT_MIN", "ms", ParameterSpec::Float, 5.f, 100.f, 50.f,
                          [](IEngine& engine, float value){
                          }},
            ParameterSpec{"repeat min", "REPEAT_MIN", "", ParameterSpec::Int, 0, 10, 0,
                          [](IEngine& engine, float us){

                          }},
            ParameterSpec{"repeat max", "REPEAT_MAX", "", ParameterSpec::Int, 0, 10, 0,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"random", "RANDOM", "", ParameterSpec::Int, 0.0f, 30.0f, 0,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"density", "DENSITY", "%", ParameterSpec::Float, 0.0f, 100.f, 100.f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"glisson", "GLISSON", "", ParameterSpec::Bool,0.f, 1.f, 1.f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"start pitch min", "START_PITCH_MIN", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"start pitch max", "START_PITCH_MAX", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"end pitch min", "END_PITCH_MIN", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"end pitch max", "END_PITCH_MAX", "semitone", ParameterSpec::Float, -24.0f, 24.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"start position left", "START_POSITION_LEFT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"start position right", "START_POSITION_RIGHT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"end position left", "END_POSITION_LEFT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"end position right", "END_POSITION_RIGHT", "", ParameterSpec::Float, -1.0f, 1.0f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"dry", "DRY", "dB", ParameterSpec::Float, -96.f, 6.f, -96.f,
                          [](IEngine& engine, float decibel){
                          }},
            ParameterSpec{"wet", "WET", "dB", ParameterSpec::Float, -96.f, 6.f, 0.0f,
                          [](IEngine& engine, float decibel){
                          }}
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
