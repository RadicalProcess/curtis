#include <gtest/gtest.h>

#include <engine/RingBuffer.h>

namespace rp::trevor
{
    using namespace testing;

    TEST(UnitTest_RingBuffer, construction)
    {
        EXPECT_NO_THROW(RingBuffer(4));
    }

    TEST(UnitTest_RingBuffer, push_pop)
    {
        auto dummyData = std::vector<float>{ 1.1f, 2.2f, 3.3f, 4.4f };
        auto dummyBuffer = Buffer(dummyData.data(), dummyData.size());
        auto consumedBuffer = Buffer(4);
        auto ringBuffer = RingBuffer(4);

        ASSERT_TRUE(ringBuffer.push(dummyBuffer));

        EXPECT_TRUE(ringBuffer.tryConsume(consumedBuffer));
        EXPECT_EQ(consumedBuffer[0], 1.1f);
        EXPECT_EQ(consumedBuffer[1], 2.2f);
        EXPECT_EQ(consumedBuffer[2], 3.3f);
        EXPECT_EQ(consumedBuffer[3], 4.4f);
    }

    TEST(UnitTest_RingBuffer, push_too_much)
    {
        auto dummyData = std::vector<float>{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
        auto dummyBuffer = Buffer(dummyData.data(), dummyData.size());
        auto ringBuffer = RingBuffer(4);

        EXPECT_FALSE(ringBuffer.push(dummyBuffer));
    }

    TEST(UnitTest_RingBuffer, push_pop_push)
    {
        auto dummyData = std::vector<float>{ 1.1f, 2.2f, 3.3f, 4.4f};
        auto dummyBuffer = Buffer(dummyData.data(), dummyData.size());
        auto consumedBuffer = Buffer(2);
        auto ringBuffer = RingBuffer(4);

        ASSERT_TRUE(ringBuffer.push(dummyBuffer));
        ASSERT_TRUE(ringBuffer.tryConsume(consumedBuffer));
        ASSERT_TRUE(ringBuffer.tryConsume(consumedBuffer));

        EXPECT_TRUE(ringBuffer.push(dummyBuffer));
    }

    TEST(UnitTest_RingBuffer, pop_twice)
    {
        auto dummyData = std::vector<float>{ 1.1f, 2.2f, 3.3f, 4.4f };
        auto dummyBuffer = Buffer(dummyData.data(), dummyData.size());
        auto consumedBuffer = Buffer(2);
        auto ringBuffer = RingBuffer(4);

        ASSERT_TRUE(ringBuffer.push(dummyBuffer));

        EXPECT_TRUE(ringBuffer.tryConsume(consumedBuffer));
        EXPECT_EQ(consumedBuffer[0], 1.1f);
        EXPECT_EQ(consumedBuffer[1], 2.2f);

        EXPECT_TRUE(ringBuffer.tryConsume(consumedBuffer));
        EXPECT_EQ(consumedBuffer[0], 3.3f);
        EXPECT_EQ(consumedBuffer[1], 4.4f);
    }

    TEST(UnitTest_RingBuffer, push_pop_inssuficient_sample)
    {
        auto dummyData = std::vector<float>{ 1.1f, 2.2f, 3.3f, 4.4f };
        auto dummyBuffer = Buffer(dummyData.data(), dummyData.size());
        auto consumeBuffer = Buffer(4);
        auto ringBuffer = RingBuffer(4);
        ASSERT_TRUE(ringBuffer.push(dummyBuffer));

        EXPECT_TRUE(ringBuffer.tryConsume(consumeBuffer));
        EXPECT_FALSE(ringBuffer.tryConsume(consumeBuffer));
    }
}
