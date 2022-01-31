#include "DummyDataProvider.h"
#include <cmath>

namespace rp::curtis::visualizer_test
{
    DummyDataProvider::DummyDataProvider()
    : visualizationDataSets_(512)
    {
        for(auto i = 0; i < 512; ++i)
        {
            const auto fi = static_cast<float>(i);
            visualizationDataSets_[i].pitch = static_cast<float>(i) / 256.0f - 1.0f;
            visualizationDataSets_[i].pan = 1.0f - static_cast<float>(i) / 256.0f;
            visualizationDataSets_[i].sampleL = sin(fi / 13.f);
            visualizationDataSets_[i].sampleR = sin(fi / 20.f);
            visualizationDataSets_[i].segment = i % 64 == 0 ? 1.0f : 0.0f;
        }
    }

    const std::vector<VisualizationDataSet>& DummyDataProvider::getVisualizationDataSets()
    {
        return visualizationDataSets_;
    }
}
