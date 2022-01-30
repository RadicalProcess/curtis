#include "visualizer/Vbo.h"

namespace rp::curtis
{
    using namespace juce;
    using namespace juce::gl;

    Vbo::Vbo(const std::vector<Position>& positions, GLenum mode)
    {
        juce::OpenGLExtensionFunctions::glGenBuffers(1, &vertexBuffer_);
        juce::OpenGLExtensionFunctions::glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
        juce::OpenGLExtensionFunctions::glBufferData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr> (static_cast<size_t> (positions.size()) * sizeof(Position)),
                positions.data(), mode);
    }

    Vbo::~Vbo()
    {
        juce::OpenGLExtensionFunctions::glDeleteBuffers(1, &vertexBuffer_);
    }

    void Vbo::update(const std::vector<Position>& positions)
    {
        juce::OpenGLExtensionFunctions::glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
        juce::OpenGLExtensionFunctions::glBufferData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(positions.size() * sizeof(float) * 3),
                positions.data(), GL_DYNAMIC_DRAW);
    }

    void Vbo::bind() const
    {
        juce::OpenGLExtensionFunctions::glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    }
}
