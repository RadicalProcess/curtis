#include "StateSync.h"

#include "ParameterSpecSet.h"
#include "ParameterSync.h"
#include "ParameterSource.h"

namespace rp::curtis
{
    StateSync::StateSync(juce::AudioProcessorValueTreeState& apvts, IParameterSetter& parameterSetter)
    {
        for(auto& parameterSpec: parameterSpecSet)
        {
            auto&& parameterSource = std::make_unique<ParameterSource>(apvts, parameterSpec.id.data());
            auto&& parameterSync = std::make_unique<ParameterSync>(*parameterSource, parameterSpec.hash, parameterSetter);

            sourceSyncs_.emplace_back(SourceSync{std::move(parameterSource), std::move(parameterSync)});
        }
    }
}
