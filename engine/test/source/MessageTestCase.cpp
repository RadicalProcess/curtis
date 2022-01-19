#include <gtest/gtest.h>

#include <engine/Message.h>

namespace rp::trevor
{
    TEST(UnitTest_Message, instantiation)
    {
        auto&& message = Message{12345, 0.5f};

        EXPECT_EQ(12345, message.hash);
        EXPECT_EQ(0.5f, message.value);
    }
}
