#include <gtest/gtest.h>

#include <engine/Validator.h>

namespace rp::trevor
{
    using namespace testing;

    class UnitTest_Validator : public TestWithParam<std::tuple<float, size_t, bool>>
    {
    };

    TEST_P(UnitTest_Validator, isValid) {
        const auto [sr, blockSize, expected] = GetParam();

        auto validator = Validator(sr, blockSize);

        EXPECT_EQ(expected, validator.isValid());
    }

    INSTANTIATE_TEST_CASE_P(
        UnitTest_Validator,
        UnitTest_Validator,
        Values(
                std::make_tuple(22049.0f, 512, false),
                std::make_tuple(22050.0f, 512, true),
                std::make_tuple(192000.0f, 512, true),
                std::make_tuple(192001.0f, 512, false),
                std::make_tuple(44100.0f, 2048, true),
                std::make_tuple(44100.0f, 2049, false))
    );
}
