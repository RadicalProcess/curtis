#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/ParameterStateSourceMock.h>
#include <engine/ParameterSetterMock.h>

#include <engine/ParameterSpec.h>
#include <engine/ParameterSync.h>

namespace rp::trevor
{
    using namespace testing;

    class UnitTest_ParameterSync : public Test
    {
    protected:
        NiceMock<ParameterStateSourceMock> parameterStateSourceMock_;
        NiceMock<ParameterSetterMock> parameterSetterMock_;

    };

    TEST_F(UnitTest_ParameterSync, construction)
    {
        EXPECT_CALL(parameterStateSourceMock_, addListener(_));

        ParameterSync(parameterStateSourceMock_, 30, parameterSetterMock_);
    }

    TEST_F(UnitTest_ParameterSync, destruction)
    {
        EXPECT_CALL(parameterStateSourceMock_, removeListener(_));
        ParameterSync(parameterStateSourceMock_, 30, parameterSetterMock_);
    }

    TEST_F(UnitTest_ParameterSync, onParameterChanged)
    {
        EXPECT_CALL(parameterSetterMock_, setParameter(30, 0.5f));

        auto&& parameterSync = ParameterSync(parameterStateSourceMock_, 30, parameterSetterMock_);
        static_cast<IParameterSource::Listener&>(parameterSync).onParameterChanged(0.5f);
    }
}
