#include <gtest/gtest.h>

#include <engine/Buffer.h>

namespace rp::trevor
{
    TEST(Buffer, owned)
    {
        auto&& buffer = Buffer(4);

        EXPECT_TRUE(buffer.owned());

        for(auto i = 0; i < 4; ++i)
            EXPECT_NO_THROW(buffer[i]);
    }


    TEST(Buffer, non_owned)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        EXPECT_EQ(0.0f, buffer[0]);
        EXPECT_EQ(0.1f, buffer[1]);
        EXPECT_EQ(0.2f, buffer[2]);
        EXPECT_EQ(0.3f, buffer[3]);

        EXPECT_FALSE(buffer.owned());
    }

    TEST(Buffer, copy_construction)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());
        auto copied = buffer;

        for(auto i = 0; i < 4; ++i)
            EXPECT_EQ(data[i], copied[i]);

        EXPECT_TRUE(copied.owned());
        EXPECT_EQ(4, copied.size());
    }

    TEST(Buffer, subscript_operator)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        for(auto i = 0; i < 4; ++i)
            EXPECT_EQ(data[i], buffer[i]);
    }

    TEST(Buffer, subscript_operator_write)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());
        buffer[1] = 1.12345f;

        EXPECT_EQ(buffer[1], 1.12345f);
        EXPECT_EQ(data[1], 1.12345f);
    }

    TEST(Buffer, out_of_range)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        EXPECT_THROW( auto&& value = buffer[4], std::out_of_range);
    }

    TEST(Buffer, copyTo)
    {
        auto&& dataA = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& bufferA = Buffer(dataA.data(), dataA.size());

        auto&& dataB = std::vector<float>{20.0f, 30.0f};
        auto&& bufferB = Buffer(dataB.data(), dataB.size());

        bufferA.copyTo(2, bufferB);

        EXPECT_EQ(0.0f, bufferA[0]);
        EXPECT_EQ(0.1f, bufferA[1]);
        EXPECT_EQ(20.0f, bufferA[2]);
        EXPECT_EQ(30.0f, bufferA[3]);
    }

    TEST(Buffer, copyTo_out_of_range)
    {
        auto&& dataA = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& bufferA = Buffer(dataA.data(), dataA.size());

        auto&& dataB = std::vector<float>{20.0f, 30.0f};
        auto&& bufferB = Buffer(dataB.data(), dataB.size());

        EXPECT_THROW(bufferA.copyTo(3, bufferB), std::out_of_range);
    }

    TEST(Buffer, multiply)
    {
        auto&& bufferA = Buffer(2);
        auto&& bufferB = Buffer(2);
        bufferA[0] = 0.5;
        bufferA[1] = 0.25;
        bufferB[0] = 20.0f;
        bufferB[1] = 40.0f;

        bufferA.multiply(bufferB);

        EXPECT_FLOAT_EQ(10.0f, bufferA[0]);
        EXPECT_FLOAT_EQ(10.0f, bufferA[1]);
    }


    TEST(Buffer, copy_construction_is_deep_copied)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());
        auto copied = buffer;

        copied[0] = 1.0f;

        EXPECT_EQ(0.0f, data[0]);
        EXPECT_EQ(1.0f, copied[0]);
    }

    TEST(Buffer, size)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        EXPECT_EQ(4, buffer.size());
    }

    TEST(Buffer, data)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        EXPECT_EQ(&data[0], buffer.data());
    }

    TEST(Buffer, downSample_size_too_big)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        EXPECT_THROW(buffer.downSample(4, DownSampleMethod::Binarize), std::out_of_range);
    }

    TEST(Buffer, downSample_size_zero)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        EXPECT_THROW(buffer.downSample(0, DownSampleMethod::Binarize), std::out_of_range);
    }

    TEST(Buffer, downSample_skip)
    {
        auto&& data = std::vector<float>{0.0f, 0.1f, 0.2f, 0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        auto&& newBuffer = buffer.downSample(2, DownSampleMethod::Skip);

        ASSERT_EQ(2, newBuffer.size());
        ASSERT_TRUE(newBuffer.owned());

        EXPECT_EQ(0.0f, newBuffer[0]);
        EXPECT_EQ(0.2f, newBuffer[1]);
    }

    TEST(Buffer, downSample_binarize)
    {
        auto&& data = std::vector<float>{0.0f, 0.0f, 0.0f, 0.1f};
        auto&& buffer = Buffer(data.data(), data.size());

        auto&& newBuffer = buffer.downSample(2, DownSampleMethod::Binarize);

        ASSERT_EQ(2, newBuffer.size());
        ASSERT_TRUE(newBuffer.owned());
        EXPECT_EQ(0.0f, newBuffer[0]);
        EXPECT_EQ(1.0f, newBuffer[1]);
    }

    TEST(Buffer, downSample_binarize_negative)
    {
        auto&& data = std::vector<float>{0.0f, 0.0f, 0.0f, -0.1f};
        auto&& buffer = Buffer(data.data(), data.size());

        auto&& newBuffer = buffer.downSample(2, DownSampleMethod::Binarize);

        ASSERT_EQ(2, newBuffer.size());
        ASSERT_TRUE(newBuffer.owned());
        EXPECT_EQ(0.0f, newBuffer[0]);
        EXPECT_EQ(0.0f, newBuffer[1]);
    }

    TEST(Buffer, downSample_indivisible)
    {
        auto&& data = std::vector<float>{0.0f, -0.1f, 0.2f, -0.3f};
        auto&& buffer = Buffer(data.data(), data.size());

        EXPECT_THROW(buffer.downSample(3, DownSampleMethod::Skip), std::logic_error);
    }
}
