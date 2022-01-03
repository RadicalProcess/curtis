#include <gtest/gtest.h>

#include <engine/FactoryMock.h>
#include <engine/EngineMock.h>
#include <engine/HoldProcessorMock.h>

#include <engine/Utils.h>
#include <engine/ParameterSpecSet.h>

#include <engine/EngineManager.h>

namespace rp::trevor
{
    using namespace testing;

    class UnitTest_EngineManager : public Test
    {
    public:
        void SetUp() override
        {
            engineMock_ = std::make_unique<NiceMock<EngineMock>>();
            engineMockPtr_ = engineMock_.get();

            holdProcessorMock_ = std::make_unique<NiceMock<HoldProcessorMock>>();
            holdProcessorMockPtr_ = holdProcessorMock_.get();

            ON_CALL(factoryMock_, createEngine(_, _, _, _))
                .WillByDefault(Return(ByMove(std::move(engineMock_))));

            ON_CALL(factoryMock_, createHoldProcessor())
                .WillByDefault(Return(ByMove(std::move(holdProcessorMock_))));

            ON_CALL(*engineMockPtr_, getHoldProcessor())
                .WillByDefault(ReturnRef(*holdProcessorMockPtr_));

        }

        void TearDown() override
        {
        }

        std::unique_ptr<EngineMock> engineMock_;
        EngineMock* engineMockPtr_;

        std::unique_ptr<HoldProcessorMock> holdProcessorMock_;
        HoldProcessorMock* holdProcessorMockPtr_;

        NiceMock<FactoryMock> factoryMock_;

        std::vector<float> channel_{256};
        float* channelPtr_{channel_.data()};
        float** buffer_ = &channelPtr_;
    };

    TEST_F(UnitTest_EngineManager, construction)
    {
        EXPECT_CALL(factoryMock_, createEngine(0, 2048, 44100.f, 256));

        EngineManager(1, 2048, 44100.f, 256, factoryMock_);
    }

    TEST_F(UnitTest_EngineManager, construction_destruction_listener)
    {
        {
            InSequence seq;
            EXPECT_CALL(*engineMockPtr_, addListener(_));
            EXPECT_CALL(*engineMockPtr_, removeListener(_));
        }
        EngineManager(1, 2048, 44100.f, 256, factoryMock_);
    }

    TEST_F(UnitTest_EngineManager, process_updateParameter)
    {
        EXPECT_CALL(*engineMockPtr_, getHoldProcessor());
        EXPECT_CALL(*holdProcessorMockPtr_, setThreshold(0.5f));

        auto&& engineManager = EngineManager(1, 2048, 44100.f, 256, factoryMock_);
        auto&& thresholdParameterSpec = getParameterSpec("THRESHOLD");

        engineManager.setParameter(thresholdParameterSpec.hash, 50.f);
        engineManager.process(buffer_, 256);
    }

    TEST_F(UnitTest_EngineManager, process)
    {
        EXPECT_CALL(*engineMockPtr_, process(_, 256));

        auto&& engineManager = EngineManager(1, 2048, 44100.f, 256, factoryMock_);
        engineManager.process(buffer_, 256);
    }

    TEST_F(UnitTest_EngineManager, getVisualizationData)
    {
        auto&& engineManager = EngineManager(1, 2048, 44100.f, 256, factoryMock_);
        auto&& visualizationData = engineManager.getVisualizationData(0);

        EXPECT_EQ(512, visualizationData.size());
    }
}

