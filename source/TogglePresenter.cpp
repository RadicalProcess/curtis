#include "TogglePresenter.h"

namespace rp::curtis
{
    TogglePresenter::TogglePresenter(juce::AudioProcessorValueTreeState& apvts, juce::Button& button)
    : apvts_(apvts)
    , button_(button)
    {
        apvts_.addParameterListener("GLISSON", this);
        button_.addListener(this);

        button_.setToggleState(apvts_.getParameter("GLISSON")->getValue() > 0.0f, juce::NotificationType::dontSendNotification);

    }

    TogglePresenter::~TogglePresenter()
    {
        apvts_.removeParameterListener("GLISSON", this);
        button_.removeListener(this);
    }

    void TogglePresenter::parameterChanged(const juce::String&, float newValue)
    {
        button_.setToggleState(newValue > 0.0f, juce::NotificationType::dontSendNotification);
    }

    void TogglePresenter::buttonStateChanged(juce::Button* button)
    {
        apvts_.getParameter("GLISSON")->setValueNotifyingHost(button->getToggleState() ? 1.0f : 0.0f);
    }

    void TogglePresenter::buttonClicked(juce::Button* )
    {
    }
}
