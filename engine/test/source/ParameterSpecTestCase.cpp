#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/EngineMock.h>
#include <engine/HoldProcessorMock.h>

#include <engine/ParameterSpec.h>

namespace rp::trevor
{
    using namespace testing;

    TEST(UnitTest_ParameterSpec, construction)
    {
        auto&& parameterSpec = ParameterSpec("threshold", "THRESHOLD", "dB", ParameterSpec::Float ,-96.0f, 0.0f, 0.0f, [](IEngine& engine, float value){
            engine.getHoldProcessor();
        });

        EXPECT_EQ("threshold", parameterSpec.name);
        EXPECT_EQ("THRESHOLD", parameterSpec.id);
        EXPECT_EQ("dB", parameterSpec.unit);
        EXPECT_EQ(-96.0f, parameterSpec.min);
        EXPECT_EQ(0.0f, parameterSpec.max);
        EXPECT_EQ(0.0f, parameterSpec.init);

        auto&& engineMock = NiceMock<EngineMock>();
        auto&& holdProcessorMock = NiceMock<HoldProcessorMock>();
        EXPECT_CALL(engineMock, getHoldProcessor()).WillOnce(ReturnRef(holdProcessorMock));
        parameterSpec.setter(engineMock, 0.5f);
    }
}
