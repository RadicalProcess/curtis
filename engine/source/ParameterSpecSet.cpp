#include "ParameterSpecSet.h"
#include "Utils.h"

namespace rp::trevor
{
    const std::vector<ParameterSpec> parameterSpecSet{
        ParameterSpec{"skip", "SKIP", "", ParameterSpec::Int, 0.f, 5.f, 1.f,
                      [](IEngine& engine, float value){
                            engine.getZeroXProcessor().setSkip(static_cast<size_t>(value));
                      }},
        ParameterSpec{"min length", "MIN_LENGTH", "us", ParameterSpec::Float, 0.f, 5000.f, 0.f,
                      [](IEngine& engine, float us){
                            const auto sampleRate = engine.getSampleRate();
                            engine.getZeroXProcessor().setMinLength(static_cast<size_t>(us * 0.000001 * sampleRate));
                      }},
        ParameterSpec{"harmonic1", "HARMONIC1", "%", ParameterSpec::Float, 0.0f, 100.f, 100.f,
                      [](IEngine& engine, float percentage){
                            engine.getAdditiveProcessor().setAdditiveHarmonic(0, percentage / 100.0f);
                      }},
        ParameterSpec{"harmonic2", "HARMONIC2", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                      [](IEngine& engine, float percentage){
                            engine.getAdditiveProcessor().setAdditiveHarmonic(1, percentage / 100.0f);
                      }},
        ParameterSpec{"harmonic3", "HARMONIC3", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                      [](IEngine& engine, float percentage){
                            engine.getAdditiveProcessor().setAdditiveHarmonic(2, percentage / 100.0f);
                       }},
        ParameterSpec{"harmonic4", "HARMONIC4", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                      [](IEngine& engine, float percentage){
                            engine.getAdditiveProcessor().setAdditiveHarmonic(3, percentage / 100.0f);
                      }},
        ParameterSpec{"harmonic5", "HARMONIC5", "%", ParameterSpec::Float, 0.0f, 100.f, 0.0f,
                      [](IEngine& engine, float percentage){
                            engine.getAdditiveProcessor().setAdditiveHarmonic(4, percentage / 100.0f);
                      }},
        ParameterSpec{"duty cycle", "DUTY_CYCLE", "%", ParameterSpec::Float, 5.f, 100.f, 100.f,
                      [](IEngine& engine, float percentage){
                            engine.getPhasorProcessor().setDutyCycle(percentage / 100.0f);
                      }},
        ParameterSpec{"threshold", "THRESHOLD", "%", ParameterSpec::Float, 0.f, 100.f, 0.f,
                      [](IEngine& engine, float percentage){
                            engine.getHoldProcessor().setThreshold(percentage / 100.0f);
                      }},
        ParameterSpec{"boost", "BOOST", "%", ParameterSpec::Float, 0.f, 100.f, 0.f,
                      [](IEngine& engine, float percentage){
                            engine.getHoldProcessor().setBoost(percentage / 100.0f);
                      }},
        ParameterSpec{"gate", "GATE", "%", ParameterSpec::Float, 0.f, 100.f, 0.f,
                      [](IEngine& engine, float percentage){
                             engine.getHoldProcessor().setGate(percentage / 100.0f);
                      }},
        ParameterSpec{"dry", "DRY", "dB", ParameterSpec::Float, -96.f, 6.f, -96.f,
                      [](IEngine& engine, float decibel){
                            engine.setDryGain(utils::decibelToGain(decibel));
                      }},
        ParameterSpec{"wet", "WET", "dB", ParameterSpec::Float, -96.f, 6.f, 0.0f,
                      [](IEngine& engine, float decibel){
                            engine.setWetGain(utils::decibelToGain(decibel));
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
