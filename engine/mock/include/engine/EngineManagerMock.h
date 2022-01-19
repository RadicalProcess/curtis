#pragma once

#include <gmock/gmock.h>

namespace rp::trevor {

    class EngineManagerMock : public IEngineManager {
    public:
        MOCK_METHOD(void, process, (float** buffer, size_t size), (override));
        MOCK_METHOD(std::vector<VisualizationData>, getVisualizationData, (), (override));
    };

}  // namespace rp::trevor
