#pragma once

#include <juce_opengl/juce_opengl.h>

#include "Attributes.h"
#include "Uniforms.h"
#include "Vbo.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace dearvr::monitor::SceneViewer
{
    class Shape
    {
    public:
        Shape(juce::OpenGLContext& glContext, const juce::String& objString);
        
        void draw(Attributes& attribute);

    private:
    
        std::vector<std::unique_ptr<Vbo>> vertexBuffers_;
    };
}
