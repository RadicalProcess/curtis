#include "DummyDataProvider.h"
#include <cmath>

namespace rp::curtis::visualizer_test
{
    DummyDataProvider::DummyDataProvider()
    : data_(512)
    {
        auto* pitchPtr = data_.pitch.getWritePtr();
        auto* panPtr = data_.pan.getWritePtr();
        auto* waveLeftPtr = data_.waveLeft.getWritePtr();
        auto* waveRightPtr = data_.waveRight.getWritePtr();
        auto* segmentPtr = data_.segment.getWritePtr();

        for(auto i = 0; i < 512; ++i)
        {
            const auto fi = static_cast<float>(i);
            pitchPtr[i] = static_cast<float>(i) / 256.0f - 1.0f;
            panPtr[i] = 1.0f - static_cast<float>(i) / 256.0f;
            waveLeftPtr[i] = sin(fi / 13.f);
            waveRightPtr[i] = sin(fi / 20.f);
            segmentPtr[i] = i % 64 == 0 ? 1.0f : 0.0f;
        }
    }

    const VisualizationData& DummyDataProvider::getVisualizationData()
    {
        return data_;
    }
}
