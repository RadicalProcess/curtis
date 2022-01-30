#pragma once

#include <curtis_core/IVisualizationDataProvider.h>

namespace rp::curtis::visualizer_test
{
    class DummyDataProvider : public IVisualizationDataProvider
    {
    public:
        DummyDataProvider();

        ~DummyDataProvider() override = default;

        const VisualizationData& getVisualizationData() override;

    private:
        VisualizationData data_;
    };
}
