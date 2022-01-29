#include "GlissonPresenter.h"
#include <algorithm>

namespace rp::curtis
{
    using namespace uicore::glisson;

    GlissonPresenter::GlissonPresenter(juce::AudioProcessorValueTreeState& apvts, uicore::glisson::Slider& slider)
    : apvts_(apvts)
    , slider_(slider)
    , map_({{TopA, "START_POSITION_A"},
            {TopB, "START_POSITION_B"},
            {BottomA, "END_POSITION_A"},
            {BottomB, "END_POSITION_B"},
            {LeftA, "START_PITCH_A"},
            {LeftB, "START_PITCH_B"},
            {RightA, "END_PITCH_A"},
            {RightB, "END_PITCH_B"}})
    {
        slider_.addListener(this);
        for(const auto& entry : map_)
            apvts_.addParameterListener(entry.second, this);
        apvts_.addParameterListener("GLISSON", this);
    }

    GlissonPresenter::~GlissonPresenter()
    {
        slider_.removeListener(this);
        for(const auto& entry : map_)
            apvts_.removeParameterListener(entry.second, this);
        apvts_.removeParameterListener("GLISSON", this);
    }

    void GlissonPresenter::parameterChanged(const juce::String& parameterID, float value)
    {
        if(parameterID == "GLISSON")
        {
            slider_.setGlissonEnabled(value > 0.0f);
            return;
        }

        const auto itr = std::find_if(map_.begin(), map_.end(), [&parameterID](const std::pair<uicore::glisson::KnobId, juce::String>& entry){
            return entry.second == parameterID;
        });
        if(itr == map_.end())
            throw std::out_of_range("GlissonPresenter: no such parameter");

        if(itr->first >= uicore::glisson::LeftA)
            slider_.set(itr->first, (value + 24.f) / 48.0f);
        else
            slider_.set(itr->first, (value + 1.0f) / 2.0f );
    }

    void GlissonPresenter::onSliderValueChanged(KnobId knobId, float value)
    {
        const auto itr = std::find_if(map_.begin(), map_.end(), [&knobId](const std::pair<uicore::glisson::KnobId, juce::String>& entry){
            return entry.first == knobId;
        });
        if(itr == map_.end())
            throw std::out_of_range("GlissonPresenter: no such knobId");

        apvts_.getParameter(itr->second)->setValueNotifyingHost(value);
    }
}
