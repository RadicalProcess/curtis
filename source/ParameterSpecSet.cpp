#include "ParameterSpecSet.h"

namespace rp::curtis
{
    const std::vector<ParameterSpec> parameterSpecSet{
            ParameterSpec{"skip", "SKIP", "", ParameterSpec::Int, 0.f, 5.f, 1.f,
                          [](IEngine& engine, float value){
                          }},
            ParameterSpec{"min length", "MIN_LENGTH", "us", ParameterSpec::Float, 0.f, 5000.f, 0.f,
                          [](IEngine& engine, float us){

                          }},
            ParameterSpec{"harmonic1", "HARMONIC1", "%", ParameterSpec::Float, 0.0f, 100.f, 100.f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"harmonic2", "HARMONIC2", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"harmonic3", "HARMONIC3", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"harmonic4", "HARMONIC4", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"harmonic5", "HARMONIC5", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"duty cycle", "DUTY_CYCLE", "%", ParameterSpec::Float, 5.f, 100.f, 100.f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"threshold", "THRESHOLD", "%", ParameterSpec::Float, 0.f, 100.f, 0.f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"boost", "BOOST", "%", ParameterSpec::Float, 0.f, 100.f, 0.f,
                          [](IEngine& engine, float percentage){
                          }},
            ParameterSpec{"gate", "GATE", "%", ParameterSpec::Float, 0.f, 100.f, 0.f,
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
