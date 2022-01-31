#include "VisualizationDataCompressor.h"

namespace rp::curtis
{
    VisualizationDataCompressor::VisualizationDataCompressor(size_t targetSize)
    : compressedData_(targetSize, {0.f, 0.f, 0.f, 0.f, false})
    {
    }

    const std::vector<VisualizationDataSet>& VisualizationDataCompressor::getCompressed() const
    {
        return compressedData_;
    }

    void VisualizationDataCompressor::compress(const std::vector<VisualizationDataSet>& uncompressedData)
    {
        const auto originalSize = uncompressedData.size();
        const auto compressionRatio = originalSize / compressedData_.size();
        for(auto i = static_cast<size_t>(0); i < compressedData_.size(); ++i)
        {
            auto compressedSample = VisualizationDataSet{0.f, 0.f, 0.f, 0.f, false};
            const auto offset = i * compressionRatio;
            for(auto j = static_cast<size_t>(0); j < compressionRatio; ++j)
            {
                compressedSample.pitch += uncompressedData[offset+j].pitch;
                compressedSample.pan += uncompressedData[offset+j].pan;
                compressedSample.sampleL += uncompressedData[offset+j].sampleL;
                compressedSample.sampleR += uncompressedData[offset+j].sampleR;
                if(uncompressedData[offset+j].segment)
                    compressedSample.segment = true;
            }

            compressedSample.scale(1.0f / static_cast<float>(compressionRatio));
            compressedData_[i] = compressedSample;
        }
    }
}
