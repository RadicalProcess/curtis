#include "visualizer/Uniforms.h"

#include <stdexcept>

namespace rp::curtis
{
    using namespace juce;

    namespace
    {
        std::unique_ptr<OpenGLShaderProgram::Uniform> createUniform(OpenGLContext& openGLContext,
            OpenGLShaderProgram& shader, const std::string& uniformName)
        {
            if (openGLContext.extensions.glGetUniformLocation(shader.getProgramID(), uniformName.c_str()) < 0)
                throw std::invalid_argument("no such uniform");

            return std::make_unique<OpenGLShaderProgram::Uniform>(shader, uniformName.c_str());
        }
    }

    Uniforms::Uniforms(OpenGLContext& openGLContext, OpenGLShaderProgram& shader, const std::vector<std::string>& uniformNames)
    {
        for(auto&& name : uniformNames)
            map.emplace(std::make_pair(name, createUniform(openGLContext, shader, name)));
    }

    juce::OpenGLShaderProgram::Uniform& Uniforms::get(const std::string& uniformName)
    {
        return *map[uniformName];
    }
}
