#include "MainComponent.h"

namespace rp::curtis::visualizer_test
{
    MainComponent::MainComponent()
    : visualizer_(dummyDataProvider_)
    {
        setSize(800, 150);

        addAndMakeVisible(visualizer_);
    }

    void MainComponent::resized()
    {
        visualizer_.setBounds(getLocalBounds());
    }
}
