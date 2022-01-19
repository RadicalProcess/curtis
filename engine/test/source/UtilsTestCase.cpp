#include <gtest/gtest.h>

#include <cmath>

#include <engine/Utils.h>

namespace rp::trevor
{
    TEST(UnitTest_Utils, decibelToGain)
    {
        EXPECT_EQ(1.0f, utils::decibelToGain(0.0f));
        EXPECT_EQ(std::powf(10.f, -6.0f / 20.0f), utils::decibelToGain(-6.0f));
        EXPECT_EQ(std::powf(10.f, -12.0f / 20.0f), utils::decibelToGain(-12.0f));
    }
}
