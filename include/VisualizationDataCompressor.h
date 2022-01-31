#pragma once

#include <vector>
#include <curtis_core/VisualizationDataSet.h>

namespace rp::curtis
{
    class VisualizationDataCompressor
    {
    public:
        VisualizationDataCompressor(size_t targetSize);

        const std::vector<VisualizationDataSet>& getCompressed() const;

        void compress(const std::vector<VisualizationDataSet>& uncompressedData);

    private:
        std::vector<VisualizationDataSet> compressedData_;
    };
}
