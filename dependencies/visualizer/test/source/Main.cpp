#include <juce_gui_basics/juce_gui_basics.h>
#include "DummyDataProvider.h"
#include "MainComponent.h"

namespace rp::curtis::visualizer_test
{
    class MainWindow : public juce::DocumentWindow
    {
    public:
        explicit MainWindow(juce::String name)
        : DocumentWindow(name,
                         juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),                          DocumentWindow::allButtons)
        {
            setSize(800, 500);

            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);

            centreWithSize(getWidth(), getHeight());

            setVisible(true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        DummyDataProvider dummyDataProvider_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };




    class GuiAppApplication : public juce::JUCEApplication
    {
    public:
        GuiAppApplication()
        {}

        const juce::String getApplicationName() override
        { return JUCE_APPLICATION_NAME_STRING; }

        const juce::String getApplicationVersion() override
        { return JUCE_APPLICATION_VERSION_STRING; }

        bool moreThanOneInstanceAllowed() override
        { return true; }

        void initialise(const juce::String& commandLine) override
        {
            juce::ignoreUnused(commandLine);

            mainWindow.reset(new MainWindow(getApplicationName()));
        }

        void shutdown() override
        {

            mainWindow = nullptr;
        }

        void systemRequestedQuit() override
        {

            quit();
        }

        void anotherInstanceStarted(const juce::String& commandLine) override
        {

            juce::ignoreUnused(commandLine);
        }


    private:
        std::unique_ptr<MainWindow> mainWindow;
    };
}

START_JUCE_APPLICATION (rp::curtis::visualizer_test::GuiAppApplication)
