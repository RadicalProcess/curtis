#include "visualizer/ZeroX.h"

#include <juce_opengl/juce_opengl.h>
#include <UICore/Style.h>

namespace rp::curtis
{
    using namespace juce::gl;

    ZeroX::ZeroX(size_t samples)
    : tick_(2.0f / static_cast<float>(samples))
    {
    }

    void ZeroX::render(const std::vector<size_t>& indices)
    {
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        for(auto index : indices)
        {
            const auto x = tick_ * static_cast<float>(index) - 1.0f;
            glVertex2f(x, -1.0f);
            glVertex2f(x, 1.0f);
        }
        glEnd();
    }
}
