#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/FactoryMock.h>
#include <engine/AdditiveProcessorMock.h>
#include <engine/ZeroXProcessorMock.h>
#include <engine/PhasorProcessorMock.h>
#include <engine/HoldProcessorMock.h>
#include <engine/DelayProcessorMock.h>
#include <engine/VisualizationCacheMock.h>
#include <engine/EngineMock.h>

#include <engine/Engine.h>

namespace rp::trevor
{
    using namespace testing;

    class UnitTest_Engine : public Test
    {
    public:
        void SetUp() override
        {
            additiveProcessorMock_ = std::make_unique<NiceMock<AdditiveProcessorMock>>();
            additiveProcessorMockPtr_ = additiveProcessorMock_.get();

            zeroXProcessorMock_= std::make_unique<NiceMock<ZeroXProcessorMock>>();
            zeroXProcessorMockPtr_ = zeroXProcessorMock_.get();

            phasorProcessorMock_ = std::make_unique<NiceMock<PhasorProcessorMock>>();
            phasorProcessorMockPtr_ = phasorProcessorMock_.get();

            holdProcessorMock_ = std::make_unique<NiceMock<HoldProcessorMock>>();
            holdProcessorMockPtr_ = holdProcessorMock_.get();

            inputDelayProcessorMock_ = std::make_unique<NiceMock<DelayProcessorMock>>();
            inputDelayProcessorMockPtr_ = inputDelayProcessorMock_.get();

            dryDelayProcessorMock_ = std::make_unique<NiceMock<DelayProcessorMock>>();
            dryDelayProcessorMockPtr_ = dryDelayProcessorMock_.get();

            zeroXDelayProcessorMock_ = std::make_unique<NiceMock<DelayProcessorMock>>();
            zeroXDelayProcessorMockPtr_ = zeroXDelayProcessorMock_.get();

            visualizationCacheMock_ = std::make_unique<NiceMock<VisualizationCacheMock>>();
            visualizationCacheMockPtr_ = visualizationCacheMock_.get();

            ON_CALL(factoryMock_, createAdditiveProcessor()).WillByDefault(Return(ByMove(std::move(additiveProcessorMock_))));
            ON_CALL(factoryMock_, createZeroXProcessor(_)).WillByDefault(Return(ByMove(std::move(zeroXProcessorMock_))));
            ON_CALL(factoryMock_, createPhasorProcessor()).WillByDefault(Return(ByMove(std::move(phasorProcessorMock_))));
            ON_CALL(factoryMock_, createHoldProcessor()).WillByDefault(Return(ByMove(std::move(holdProcessorMock_))));
            ON_CALL(factoryMock_, createVisualizationCache(_,_)).WillByDefault(Return(ByMove(std::move(visualizationCacheMock_))));
            ON_CALL(factoryMock_, createDelayProcessor(_)).WillByDefault(Invoke([this]() -> std::unique_ptr<DelayProcessorMock>{
                callCount_++;
                switch(callCount_)
                {
                    case 1:
                        return std::move(inputDelayProcessorMock_);
                    case 2:
                        return std::move(dryDelayProcessorMock_);
                    default:
                        return std::move(zeroXDelayProcessorMock_);
                }
            }));
        }

        void TearDown() override
        {
            additiveProcessorMock_ = nullptr;
            zeroXProcessorMock_ = nullptr;
            phasorProcessorMock_ = nullptr;
            holdProcessorMock_ = nullptr;
            inputDelayProcessorMock_ = nullptr;
            dryDelayProcessorMock_ = nullptr;
            zeroXDelayProcessorMock_= nullptr;
            visualizationCacheMock_ = nullptr;
        }

        NiceMock<FactoryMock> factoryMock_;

        std::unique_ptr<AdditiveProcessorMock> additiveProcessorMock_;
        AdditiveProcessorMock* additiveProcessorMockPtr_;

        std::unique_ptr<ZeroXProcessorMock> zeroXProcessorMock_;
        ZeroXProcessorMock* zeroXProcessorMockPtr_;

        std::unique_ptr<PhasorProcessorMock> phasorProcessorMock_;
        PhasorProcessorMock* phasorProcessorMockPtr_;

        std::unique_ptr<HoldProcessorMock> holdProcessorMock_;
        HoldProcessorMock* holdProcessorMockPtr_;

        std::unique_ptr<DelayProcessorMock> inputDelayProcessorMock_;
        DelayProcessorMock* inputDelayProcessorMockPtr_;

        std::unique_ptr<DelayProcessorMock> dryDelayProcessorMock_;
        DelayProcessorMock* dryDelayProcessorMockPtr_;

        std::unique_ptr<DelayProcessorMock> zeroXDelayProcessorMock_;
        DelayProcessorMock* zeroXDelayProcessorMockPtr_;

        std::unique_ptr<VisualizationCacheMock> visualizationCacheMock_;
        VisualizationCacheMock* visualizationCacheMockPtr_;

        size_t callCount_ {0};
    };

    TEST_F(UnitTest_Engine, construction)
    {
        EXPECT_CALL(factoryMock_, createZeroXProcessor(2048));
        EXPECT_CALL(factoryMock_, createPhasorProcessor());
        EXPECT_CALL(factoryMock_, createAdditiveProcessor());
        EXPECT_CALL(factoryMock_, createHoldProcessor());
        EXPECT_CALL(factoryMock_, createDelayProcessor(2048)).Times(3);
        EXPECT_CALL(factoryMock_, createVisualizationCache(2048, _));

        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);
    }

    TEST_F(UnitTest_Engine, construction_destruction_add_remove_listener)
    {
        EXPECT_CALL(*visualizationCacheMockPtr_, addListener(_));
        EXPECT_CALL(*visualizationCacheMockPtr_, removeListener(_));

        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);
    }

    TEST_F(UnitTest_Engine, process)
    {
        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);
        auto dummyBlock = std::vector<float>(256);

        {
            InSequence seq;
            EXPECT_CALL(*inputDelayProcessorMockPtr_, process(_));
            EXPECT_CALL(*zeroXProcessorMockPtr_, process(_));
            EXPECT_CALL(*zeroXDelayProcessorMockPtr_, process(_));
            EXPECT_CALL(*phasorProcessorMockPtr_, process(_));
            EXPECT_CALL(*additiveProcessorMockPtr_, process(_));
            EXPECT_CALL(*holdProcessorMockPtr_, process(_));
            EXPECT_CALL(*dryDelayProcessorMockPtr_, process(_));
            EXPECT_CALL(*visualizationCacheMockPtr_, push(_));
        }
        engine.process(dummyBlock.data(), dummyBlock.size());
    }

    TEST_F(UnitTest_Engine, getSampleRate)
    {
        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);

        EXPECT_EQ(44100.f, engine.getSampleRate());
    }

    TEST_F(UnitTest_Engine, getZeroXProcessor)
    {
        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);

        EXPECT_EQ(zeroXProcessorMockPtr_, &engine.getZeroXProcessor());
    }

    TEST_F(UnitTest_Engine, getAdditiveProcessor)
    {
        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);

        EXPECT_EQ(additiveProcessorMockPtr_, &engine.getAdditiveProcessor());
    }

    TEST_F(UnitTest_Engine, getPhasorProcessor)
    {
        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);

        EXPECT_EQ(phasorProcessorMockPtr_, &engine.getPhasorProcessor());
    }

    TEST_F(UnitTest_Engine, getHoldProcessor)
    {
        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);

        EXPECT_EQ(holdProcessorMockPtr_, &engine.getHoldProcessor());
    }


    TEST_F(UnitTest_Engine, addListener)
    {
        auto&& engineListenerMock = EngineListenerMock();

        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);
        engine.addListener(&engineListenerMock);

        EXPECT_CALL(engineListenerMock, onVisualizationDataFilled(0, _));

        static_cast<IVisualizationCache::Listener&>(engine).onCacheFilled(VisualizationData(64));
    }

    TEST_F(UnitTest_Engine, removeListener)
    {
        auto&& engineListenerMock = EngineListenerMock();

        auto&& engine = Engine(0, 2048, 44100.f, 256, factoryMock_);
        engine.addListener(&engineListenerMock);
        engine.removeListener(&engineListenerMock);

        EXPECT_CALL(engineListenerMock, onVisualizationDataFilled(0, _)).Times(0);

        static_cast<IVisualizationCache::Listener&>(engine).onCacheFilled(VisualizationData(64));
    }
}
