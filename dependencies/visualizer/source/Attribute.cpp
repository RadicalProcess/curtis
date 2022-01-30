#include "visualizer/Attributes.h"
#include "visualizer/Position.h"

namespace rp::curtis
{
    using namespace juce;
    using namespace juce::gl;

    Attributes::Attributes(OpenGLShaderProgram& shaderProgram)
    {
        position = createAttribute(shaderProgram, "position");
    }

    void Attributes::enable() const
    {
        OpenGLExtensionFunctions::glVertexAttribPointer(position->attributeID, 3, GL_FLOAT, GL_FALSE, sizeof(Position), nullptr);
        OpenGLExtensionFunctions::glEnableVertexAttribArray(position->attributeID);
    }

    void Attributes::disable() const
    {
        OpenGLExtensionFunctions::glDisableVertexAttribArray(position->attributeID);
    }

    std::unique_ptr<OpenGLShaderProgram::Attribute> Attributes::createAttribute(OpenGLShaderProgram &shader, const char *attributeName)
    {
        if (OpenGLExtensionFunctions::glGetAttribLocation(shader.getProgramID(), attributeName) < 0)
            return nullptr;

        return std::make_unique<OpenGLShaderProgram::Attribute>(shader, attributeName);
    }
}
