#pragma once

#include <atomic>
#include <vector>
#include <array>

#include <juce_opengl/juce_opengl.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <curtis_core/IVisualizationDataProvider.h>

#include "Attributes.h"
#include "Uniforms.h"
#include "Waveform.h"

namespace rp::curtis
{
    class Visualizer : public juce::OpenGLAppComponent
    {
    public:
        explicit Visualizer(IVisualizationDataProvider& visualizationDataProvider);

        ~Visualizer() override;

        void initialise() override;

        void shutdown() override;

        void render() override;

        void paint(juce::Graphics& g) override;

    private:
        void resized() override;

        IVisualizationDataProvider& visualizationDataProvider_;
        VisualizationData visualizationData_;
        juce::OpenGLContext openGLContext_;

        std::unique_ptr<juce::OpenGLShaderProgram> shader_;
        std::unique_ptr<Waveform> pitch_;
        std::unique_ptr<Waveform> pan_;
        std::unique_ptr<Waveform> waveLeft_;
        std::unique_ptr<Waveform> waveRight_;

        std::unique_ptr<Attributes> attributes_;
        std::unique_ptr<Uniforms> uniforms_;

        const std::array<float, 4> foreGroundColor_;
        const std::array<float, 4> backGroundColor_;
        const std::array<float, 4> highlightColor_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
    };
}
