#include "Visualizer.h"

#include <vector>
#include <UICore/Style.h>
#include <VisualizerResource.h>
#include "Constants.h"

using namespace juce;

namespace rp::curtis
{
    namespace
    {
        using namespace juce::gl;

        void drawVerticalLine(float x)
        {
            glBegin(GL_LINES);
            glVertex2f(x, -1.f);
            glVertex2f(x, 1.f);
            glEnd();
        }
    }

    using namespace uicore::styles;

    Visualizer::Visualizer(IVisualizationDataProvider& visualizationDataProvider)
    : visualizationDataProvider_(visualizationDataProvider)
    , whiteColor_({1.0f, 1.0f, 1.0f, 1.0f})
    , foreGroundColor_({foreground.getFloatRed(), foreground.getFloatGreen(), foreground.getFloatBlue(), 1.0f})
    , backGroundColor_({background.getFloatRed(), background.getFloatGreen(), background.getFloatBlue(), 1.0f})
    , highlightColor_({highlight.getFloatRed(), highlight.getFloatGreen(), highlight.getFloatBlue(), 1.0f})
    , segments_(Constants::visualDataSize, false)
    {
    }

    Visualizer::~Visualizer()
    {
        shutdownOpenGL();
    }

    void Visualizer::initialise()
    {
        shader_ = std::make_unique<OpenGLShaderProgram>(openGLContext);
        const auto vertexResult = shader_->addVertexShader(resource::vertex_glsl);
        const auto fragResult = shader_->addFragmentShader(resource::frag_glsl);
        const auto linkResult = shader_->link();

        if(!(vertexResult && fragResult && linkResult))
            throw std::runtime_error("GL setup error");

        attributes_ = std::make_unique<Attributes>(*shader_);
        uniforms_ = std::make_unique<Uniforms>(openGLContext_, *shader_, std::vector<std::string>{"yTranslate", "yScale", "lineColor"});
        pitch_ = std::make_unique<Waveform>(Constants::visualDataSize);
        pan_ = std::make_unique<Waveform>(Constants::visualDataSize);
        waveLeft_ = std::make_unique<Waveform>(Constants::visualDataSize);
        waveRight_ = std::make_unique<Waveform>(Constants::visualDataSize);
    }

    void Visualizer::shutdown(){}

    void Visualizer::resized(){}

    void Visualizer::render()
    {
        using namespace ::juce::gl;
        jassert (OpenGLHelpers::isContextActive());

        auto desktopScale = (float) openGLContext.getRenderingScale();
        OpenGLHelpers::clear(juce::Colours::black);

        glViewport(0, 0, roundToInt (desktopScale * (float) getWidth()), roundToInt (desktopScale * (float) getHeight()));
        glLineWidth(3.0f);
        shader_->use();

        updateData(visualizationDataProvider_.getVisualizationDataSets());

        glLineWidth(1.0f);
        renderLine(*waveLeft_, 0.5f, 0.5f, whiteColor_);
        renderLine(*waveRight_, -0.5f, 0.5f, whiteColor_);
        glLineWidth(2.0f);
        renderLine(*pitch_, 0.0f, 1.0f, foreGroundColor_);
        glLineWidth(3.0f);
        renderLine(*pan_, 0.0f, 1.0f, backGroundColor_);

        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        renderSegment();
        attributes_->disable();
    }

    void Visualizer::updateData(const std::vector<VisualizationDataSet>& visualizationDataSets)
    {
        auto& pitchPosition = pitch_->getPosition();
        auto& panPosition = pan_->getPosition();
        auto& waveLeftPosition = waveLeft_->getPosition();
        auto& waveRightPosition = waveRight_->getPosition();

        for(auto i = static_cast<size_t>(0); i < visualizationDataSets.size(); ++i)
        {
            pitchPosition[i][1] = visualizationDataSets[i].pitch;
            panPosition[i][1] = visualizationDataSets[i].pan;
            waveLeftPosition[i][1] = visualizationDataSets[i].sampleL;
            waveRightPosition[i][1] = visualizationDataSets[i].sampleR;
            segments_[i] = visualizationDataSets[i].segment;
        }
    }

    void Visualizer::renderLine(Waveform& waveform, float yTranslate, float yScale, const std::array<float, 4>& color)
    {
        waveform.bind();
        waveform.update();
        attributes_->enable();
        uniforms_->get("yTranslate").set(yTranslate);
        uniforms_->get("yScale").set(yScale);
        uniforms_->get("lineColor").set(color[0], color[1], color[2], color[3]);
        glDrawArrays(GL_LINE_STRIP, 0, waveform.getNumVertices());
        attributes_->disable();
    }

    void Visualizer::renderSegment()
    {
        glLineWidth(1.0f);
        glColor4f(highlightColor_[0], highlightColor_[1], highlightColor_[2], 1.0f);
        const auto halfSize = Constants::visualDataSize / 2;
        for(auto i = 0; i < segments_.size(); i++)
        {
            if(segments_[i])
                drawVerticalLine(static_cast<float>(i) / static_cast<float>(halfSize) - 1.0f);
        }
    }

    void Visualizer::paint(Graphics&)
    {
    }
}
