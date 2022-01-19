#include <gtest/gtest.h>

#include <engine/SampleCapacitor.h>

namespace rp::trevor
{
    using namespace testing;

    TEST(UnitTest_SampleCapacitor, process)
    {
        auto dummyBuffer = Buffer(2);
        dummyBuffer[0] = 1.1f;
        dummyBuffer[1] = 2.2f;

        auto sampleCapacitor = SampleCapacitor(2, [](Buffer&){});
        sampleCapacitor.process(dummyBuffer);

        EXPECT_EQ(0.0f, dummyBuffer[0]);
        EXPECT_EQ(0.0f, dummyBuffer[1]);
    }

    TEST(UnitTest_SampleCapacitor, process_consume_pushed_samples)
    {
        auto dummyBuffer = Buffer(2);
        dummyBuffer[0] = 1.1f;
        dummyBuffer[1] = 2.2f;

        auto sampleCapacitor = SampleCapacitor(2, [](Buffer&){});
        sampleCapacitor.process(dummyBuffer);
        sampleCapacitor.process(dummyBuffer);

        EXPECT_EQ(1.1f, dummyBuffer[0]);
        EXPECT_EQ(2.2f, dummyBuffer[1]);
    }

}
