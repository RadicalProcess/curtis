#pragma once

#include <unordered_map>

#include <juce_opengl/juce_opengl.h>

namespace rp::curtis
{
    class Uniforms
    {
    public:
        Uniforms(juce::OpenGLContext& openGLContext,
                juce::OpenGLShaderProgram& shader,
                const std::vector<std::string>& uniformNames);

        juce::OpenGLShaderProgram::Uniform& get(const std::string& uniformName);

    private:
        std::unordered_map<std::string, std::unique_ptr <juce::OpenGLShaderProgram::Uniform>> map;
    };
}
