#include <set>

#include <engine/IParameterSourceSet.h>

#include <juce_audio_utils/juce_audio_utils.h>

namespace rp::trevor
{
    class ParameterSourceSet : public IParameterSourceSet
    {
    public:
        explicit ParameterSourceSet(juce::AudioProcessorValueTreeState& apvts);

        ~ParameterSourceSet() override = default;

        void addListener(const std::string& parameterId, IParameterSourceSet::Listener* listener) override;

        void removeListener(const std::string& parameterId, IParameterSourceSet::Listener* listener) override;

    private:
        juce::AudioProcessorValueTreeState& apvts_;
        std::set<IParameterSourceSet::Listener*> listeners_;
    };
}
