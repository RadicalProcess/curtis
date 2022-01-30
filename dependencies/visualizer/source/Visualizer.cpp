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
    , visualizationData_(Constants::visualDataSize)
    , foreGroundColor_({foreground.getFloatRed(), foreground.getFloatGreen(), foreground.getFloatBlue(), 1.0f})
    , backGroundColor_({background.getFloatRed(), background.getFloatGreen(), background.getFloatBlue(), 1.0f})
    , highlightColor_({highlight.getFloatRed(), highlight.getFloatGreen(), highlight.getFloatBlue(), 1.0f})
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

        visualizationData_ = visualizationDataProvider_.getVisualizationData();

        auto desktopScale = (float) openGLContext.getRenderingScale();
        OpenGLHelpers::clear(juce::Colours::black);

        glViewport(0, 0, roundToInt (desktopScale * (float) getWidth()), roundToInt (desktopScale * (float) getHeight()));

        glLineWidth(3.0f);
        shader_->use();

        pitch_->bind();
        pitch_->update(visualizationData_.pitch);
        attributes_->enable();
        uniforms_->get("yTranslate").set(0.0f);
        uniforms_->get("yScale").set(1.0f);
        uniforms_->get("lineColor").set(1.0f , 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, pitch_->getNumVertices());
        attributes_->disable();

        glLineWidth(2.0f);
        pan_->bind();
        pan_->update(visualizationData_.pan);
        attributes_->enable();
        uniforms_->get("yTranslate").set(0.0f);
        uniforms_->get("yScale").set(1.0f);
        uniforms_->get("lineColor").set(foreGroundColor_[0], foreGroundColor_[1], foreGroundColor_[2], 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, pan_->getNumVertices());
        attributes_->disable();

        glLineWidth(2.0f);
        waveLeft_->bind();
        waveLeft_->update(visualizationData_.waveLeft);
        attributes_->enable();
        uniforms_->get("yTranslate").set(0.5f);
        uniforms_->get("yScale").set(0.5f);
        uniforms_->get("lineColor").set(backGroundColor_[0], backGroundColor_[1], backGroundColor_[2], 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, waveLeft_->getNumVertices());
        attributes_->disable();

        glLineWidth(2.0f);
        waveRight_->bind();
        waveRight_->update(visualizationData_.waveRight);
        attributes_->enable();
        uniforms_->get("yTranslate").set(-0.5f);
        uniforms_->get("yScale").set(0.5f);
        uniforms_->get("lineColor").set(backGroundColor_[0], backGroundColor_[1], backGroundColor_[2], 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, waveRight_->getNumVertices());
        attributes_->disable();

        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        glLineWidth(1.0f);
        glColor4f(highlightColor_[0], highlightColor_[1], highlightColor_[2], 1.0f);
        const auto halfSize = Constants::visualDataSize / 2;
        auto* ptr = visualizationData_.segment.getReadPtr();
        for(auto i = 0; i < visualizationData_.segment.size(); i++)
        {
            if(ptr[i] == 0.0f)
                continue;
            drawVerticalLine(static_cast<float>(i) / static_cast<float>(halfSize) - 1.0f);
        }
        attributes_->disable();
    }


    void Visualizer::paint(Graphics&)
    {
    }


}
