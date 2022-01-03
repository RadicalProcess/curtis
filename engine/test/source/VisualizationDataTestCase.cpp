#include <gtest/gtest.h>

#include <engine/VisualizationData.h>

namespace rp::trevor
{
    TEST(VisualizationData, construction)
    {
        auto visualizationData = VisualizationData(35);

        EXPECT_EQ(35, visualizationData.original.size());
        EXPECT_EQ(35, visualizationData.generated.size());
        EXPECT_EQ(35, visualizationData.mixed.size());
        EXPECT_EQ(35, visualizationData.zeroCrosses.size());
    }

    TEST(VisualizationData, copy_assignment)
    {
        auto visualizationDataA = VisualizationData(1);
        auto visualizationDataB = VisualizationData(1);

        visualizationDataA.original[0] = 1.0f;
        visualizationDataA.generated[0] = 2.0f;
        visualizationDataA.mixed[0] = 3.0f;
        visualizationDataA.zeroCrosses[0] = 4.0f;

        visualizationDataB = visualizationDataA;

        EXPECT_EQ(1.0f, visualizationDataB.original[0]);
        EXPECT_EQ(2.0f, visualizationDataB.generated[0]);
        EXPECT_EQ(3.0f, visualizationDataB.mixed[0]);
        EXPECT_EQ(4.0f, visualizationDataB.zeroCrosses[0]);
    }

    TEST(VisualizationData, copy_assignment_different_size)
    {
        auto visualizationDataA = VisualizationData(1);
        auto visualizationDataB = VisualizationData(2);

        EXPECT_THROW(visualizationDataA = visualizationDataB, std::out_of_range);
    }
}
