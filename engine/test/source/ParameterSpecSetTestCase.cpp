#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/Utils.h>
#include <engine/ParameterSpecSet.h>

#include <engine/EngineMock.h>
#include <engine/ZeroXProcessorMock.h>
#include <engine/AdditiveProcessorMock.h>
#include <engine/PhasorProcessorMock.h>
#include <engine/HoldProcessorMock.h>
#include <engine/XFaderProcessorMock.h>

namespace rp::trevor
{
    using namespace testing;

    class UnitTest_ParameterSpecSet : public Test
    {
    protected:
        void SetUp() override
        {
            ON_CALL(engineMock_, getSampleRate()).WillByDefault(Return(44100.0f));
            ON_CALL(engineMock_, getZeroXProcessor()).WillByDefault(ReturnRef(zeroXProcessorMock_));
            ON_CALL(engineMock_, getAdditiveProcessor()).WillByDefault(ReturnRef(additiveProcessorMock_));
            ON_CALL(engineMock_, getPhasorProcessor()).WillByDefault(ReturnRef(phasorProcessorMock_));
            ON_CALL(engineMock_, getHoldProcessor()).WillByDefault(ReturnRef(holdProcessorMock_));
        }

        void TearDown() override
        {
        }

        NiceMock<EngineMock> engineMock_;
        NiceMock<ZeroXProcessorMock> zeroXProcessorMock_;
        NiceMock<AdditiveProcessorMock> additiveProcessorMock_;
        NiceMock<PhasorProcessorMock> phasorProcessorMock_;
        NiceMock<HoldProcessorMock> holdProcessorMock_;
        NiceMock<XFaderProcessorMock> xFaderProcessorMock_;
    };

    TEST_F(UnitTest_ParameterSpecSet, skip)
    {
        EXPECT_CALL(engineMock_, getZeroXProcessor());
        EXPECT_CALL(zeroXProcessorMock_, setSkip(3));

        getParameterSpec("SKIP").setter(engineMock_, 3.0f);
    }

    TEST_F(UnitTest_ParameterSpecSet, min_length)
    {
        EXPECT_CALL(engineMock_, getZeroXProcessor());
        EXPECT_CALL(engineMock_, getSampleRate());
        EXPECT_CALL(zeroXProcessorMock_, setMinLength(2500.0f * 44100.0f * 0.000001));

        getParameterSpec("MIN_LENGTH").setter(engineMock_, 2500.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, harmonic1)
    {
        EXPECT_CALL(engineMock_, getAdditiveProcessor());
        EXPECT_CALL(additiveProcessorMock_, setAdditiveHarmonic(0, 0.5f));

        getParameterSpec("HARMONIC1").setter(engineMock_, 50.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, harmonic2)
    {
        EXPECT_CALL(engineMock_, getAdditiveProcessor());
        EXPECT_CALL(additiveProcessorMock_, setAdditiveHarmonic(1, 0.5f));

        getParameterSpec("HARMONIC2").setter(engineMock_, 50.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, harmonic3)
    {
        EXPECT_CALL(engineMock_, getAdditiveProcessor());
        EXPECT_CALL(additiveProcessorMock_, setAdditiveHarmonic(2, 0.5f));

        getParameterSpec("HARMONIC3").setter(engineMock_, 50.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, harmonic4)
    {
        EXPECT_CALL(engineMock_, getAdditiveProcessor());
        EXPECT_CALL(additiveProcessorMock_, setAdditiveHarmonic(3, 0.5f));

        getParameterSpec("HARMONIC4").setter(engineMock_, 50.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, harmonic5)
    {
        EXPECT_CALL(engineMock_, getAdditiveProcessor());
        EXPECT_CALL(additiveProcessorMock_, setAdditiveHarmonic(4, 0.5f));

        getParameterSpec("HARMONIC5").setter(engineMock_, 50.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, duty_cycle)
    {
        EXPECT_CALL(engineMock_, getPhasorProcessor());
        EXPECT_CALL(phasorProcessorMock_, setDutyCycle(0.5f));

        getParameterSpec("DUTY_CYCLE").setter(engineMock_, 50.0f);
    }

    TEST_F(UnitTest_ParameterSpecSet, threshold)
    {
        EXPECT_CALL(engineMock_, getHoldProcessor());
        EXPECT_CALL(holdProcessorMock_, setThreshold(0.5));

        getParameterSpec("THRESHOLD").setter(engineMock_, 50.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, boost)
    {
        EXPECT_CALL(engineMock_, getHoldProcessor());
        EXPECT_CALL(holdProcessorMock_, setBoost(0.5f));

        getParameterSpec("BOOST").setter(engineMock_, 50.f);
    }

    TEST_F(UnitTest_ParameterSpecSet, gate)
    {
        EXPECT_CALL(engineMock_, getHoldProcessor());
        EXPECT_CALL(holdProcessorMock_, setGate(0.5f));

        getParameterSpec("GATE").setter(engineMock_, 50.f);
    }


    TEST_F(UnitTest_ParameterSpecSet, getParameterSpec)
    {
        const auto& parameterSpec = getParameterSpec("THRESHOLD");

        EXPECT_EQ("threshold", parameterSpec.name);
        EXPECT_EQ(0.0f, parameterSpec.min);
    }

    TEST_F(UnitTest_ParameterSpecSet, getParameterSpec_non_existent)
    {
        EXPECT_THROW( getParameterSpec("DUMMY"), std::out_of_range);
    }
}
