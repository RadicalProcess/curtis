#pragma once

#include <gmock/gmock.h>

#include <engine/IVisualizationCache.h>

namespace rp::trevor {

    class VisualizationCacheMock : public IVisualizationCache {
    public:
        ~VisualizationCacheMock() = default;
        MOCK_METHOD(void, push, (const VisualizationData& data), (override));
        MOCK_METHOD(void, addListener, (Listener* listener), (override));
        MOCK_METHOD(void, removeListener, (Listener* listener), (override));
    };

    class VisualizationCacheListenerMock : public IVisualizationCache::Listener
    {
    public:
        ~VisualizationCacheListenerMock() = default;
        MOCK_METHOD(void, onCacheFilled, (const VisualizationData& data), (override));
    };

}  // namespace rp::trevor
