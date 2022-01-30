#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <visualizer/Visualizer.h>
#include "DummyDataProvider.h"

namespace rp::curtis::visualizer_test
{
    class MainComponent : public juce::Component
    {
    public:
        MainComponent();

        void resized() override;

    private:
        DummyDataProvider dummyDataProvider_;
        Visualizer visualizer_;
    };
}
