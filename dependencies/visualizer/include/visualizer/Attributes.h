#pragma once
#include <juce_opengl/juce_opengl.h>

namespace rp::curtis
{
    class Attributes
    {
    public:
        Attributes(juce::OpenGLShaderProgram& shaderProgram);
        void enable() const;
        void disable() const;

        std::unique_ptr<juce::OpenGLShaderProgram::Attribute> position;

    private:
        static std::unique_ptr<juce::OpenGLShaderProgram::Attribute> createAttribute(juce::OpenGLShaderProgram &shader, const char *attributeName);
    };
}
