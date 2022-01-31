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
        void updateData(const std::vector<VisualizationDataSet>& visualizationDataSets);

        void renderLine(Waveform& waveform, float yTranslate, float yScale, const std::array<float, 4>& color);

        void renderSegment();

        void resized() override;

        IVisualizationDataProvider& visualizationDataProvider_;
        juce::OpenGLContext openGLContext_;

        std::unique_ptr<juce::OpenGLShaderProgram> shader_;
        std::unique_ptr<Waveform> pitch_;
        std::unique_ptr<Waveform> pan_;
        std::unique_ptr<Waveform> waveLeft_;
        std::unique_ptr<Waveform> waveRight_;

        std::unique_ptr<Attributes> attributes_;
        std::unique_ptr<Uniforms> uniforms_;

        const std::array<float, 4> whiteColor_;
        const std::array<float, 4> foreGroundColor_;
        const std::array<float, 4> backGroundColor_;
        const std::array<float, 4> highlightColor_;
        std::vector<bool> segments_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
    };
}
