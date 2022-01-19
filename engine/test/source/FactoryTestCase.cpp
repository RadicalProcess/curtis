#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/Factory.h>
#include <engine/VisualizationCache.h>
#include <engine/Engine.h>
#include <engine/AdditiveProcessor.h>
#include <engine/DelayProcessor.h>
#include <engine/HoldProcessor.h>
#include <engine/PhasorProcessor.h>
#include <engine/XFaderProcessor.h>
#include <engine/ZeroXProcessor.h>

namespace rp::trevor
{
    using namespace testing;

    TEST(UnitTest_Factory, createVisualizationCache)
    {
        auto&& visualizationCache = Factory().createVisualizationCache(2048, 256);

        ASSERT_THAT(visualizationCache.get(), NotNull());
        EXPECT_THAT(visualizationCache.get(), WhenDynamicCastTo<VisualizationCache*>(NotNull()));
    }

    TEST(UnitTest_Factory, createEngine)
    {
        auto&& engine = Factory().createEngine(0, 2048, 44100.f, 256);

        ASSERT_THAT(engine.get(), NotNull());
        EXPECT_THAT(engine.get(), WhenDynamicCastTo<Engine*>(NotNull()));
    }

    TEST(UnitTest_Factory, createAdditiveProcessor)
    {
        auto&& processor = Factory().createAdditiveProcessor();

        ASSERT_THAT(processor.get(), NotNull());
        EXPECT_THAT(processor.get(), WhenDynamicCastTo<AdditiveProcessor*>(NotNull()));
    }

    TEST(UnitTest_Factory, createDelayProcessor)
    {
        auto&& processor = Factory().createDelayProcessor(2048);

        ASSERT_THAT(processor.get(), NotNull());
        EXPECT_THAT(processor.get(), WhenDynamicCastTo<DelayProcessor*>(NotNull()));
    }

    TEST(UnitTest_Factory, createHoldProcessor)
    {
        auto&& processor = Factory().createHoldProcessor();

        ASSERT_THAT(processor.get(), NotNull());
        EXPECT_THAT(processor.get(), WhenDynamicCastTo<HoldProcessor*>(NotNull()));
    }

    TEST(UnitTest_Factory, createPhasorProcessor)
    {
        auto&& processor = Factory().createPhasorProcessor();

        ASSERT_THAT(processor.get(), NotNull());
        EXPECT_THAT(processor.get(), WhenDynamicCastTo<PhasorProcessor*>(NotNull()));
    }

    TEST(UnitTest_Factory, createXFaderProcessor)
    {
        auto&& processor = Factory().createXFaderProcessor(0.5f);

        ASSERT_THAT(processor.get(), NotNull());
        EXPECT_THAT(processor.get(), WhenDynamicCastTo<XFaderProcessor*>(NotNull()));
    }

    TEST(UnitTest_Factory, createZeroXProcessor)
    {
        auto&& processor = Factory().createZeroXProcessor(2048);

        ASSERT_THAT(processor.get(), NotNull());
        EXPECT_THAT(processor.get(), WhenDynamicCastTo<ZeroXProcessor*>(NotNull()));
    }
}
