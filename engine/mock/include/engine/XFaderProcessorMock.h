#pragma once

#include <gmock/gmock.h>

#include <engine/IXFaderProcessor.h>

namespace rp::trevor
{
    class XFaderProcessorMock : public IXFaderProcessor {
    public:
        ~XFaderProcessorMock() override = default;
        MOCK_METHOD(void, process, (Buffer& buffer, const Buffer& reference), (override));
        MOCK_METHOD(void, setDryWet, (float dryWet), (override));
    };
 }  // namespace rp::trevor

