#include <gtest/gtest.h>

#include <engine/VisualizationCacheMock.h>

#include <engine/VisualizationCache.h>

namespace rp::trevor
{
    using namespace testing;

    class UnitTest_VisualizationCache : public Test
    {
    protected:
        void SetUp() override
        {
            Test::SetUp();
        }

        void TearDown() override
        {
            Test::TearDown();
        }

        VisualizationCacheListenerMock visualizationCacheListenerMock_;
    };

    TEST_F(UnitTest_VisualizationCache, construction_add_listener)
    {
        EXPECT_CALL(visualizationCacheListenerMock_, onCacheFilled(_)).WillOnce(Invoke([](const VisualizationData& visualizationData){
            EXPECT_EQ(32, visualizationData.size());
        }));

        auto visualizationDataCache = VisualizationCache(64, 32);
        visualizationDataCache.addListener(&visualizationCacheListenerMock_);
        visualizationDataCache.push(VisualizationData(64));
    }

    TEST_F(UnitTest_VisualizationCache, construction_add_listener_listener_notified_only_cache_is_filled)
    {
        EXPECT_CALL(visualizationCacheListenerMock_, onCacheFilled(_)).Times(0);

        auto visualizationDataCache = VisualizationCache(64, 32);
        visualizationDataCache.addListener(&visualizationCacheListenerMock_);
        visualizationDataCache.push(VisualizationData(32));
    }

    TEST_F(UnitTest_VisualizationCache, construction_remove_listener)
    {
        EXPECT_CALL(visualizationCacheListenerMock_, onCacheFilled(_)).Times(0);

        auto visualizationDataCache = VisualizationCache(64, 32);
        visualizationDataCache.addListener(&visualizationCacheListenerMock_);
        visualizationDataCache.removeListener(&visualizationCacheListenerMock_);
        visualizationDataCache.push(VisualizationData(64));
    }
}
