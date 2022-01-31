#include "Waveform.h"

namespace rp::curtis
{
    namespace
    {
        std::vector<Position> createWaveform(size_t size)
        {
            auto waveform = std::vector<Position>();
            waveform.reserve(size);
            const auto halfSize = static_cast<int>(size) / 2;
            for(auto i = 0; i < static_cast<int>(size); i++)
                waveform.emplace_back(Position{static_cast<float>(i - halfSize) / static_cast<float>(halfSize), 0.0f, 0.f});
            return waveform;
        }
    }

    Waveform::Waveform(size_t size)
    : positions_(createWaveform(size))
    , vbo_(positions_)
    {
    }

    void Waveform::update()
    {
        vbo_.update(positions_);
    }

    void Waveform::bind()
    {
        vbo_.bind();
    }

    GLsizei Waveform::getNumVertices() const
    {
        return static_cast<GLsizei>(positions_.size());
    }

    std::vector<Position>& Waveform::getPosition()
    {
        return positions_;
    }
}
