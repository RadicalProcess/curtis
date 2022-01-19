#pragma once

#include <memory>
#include <vector>
#include <string_view>

#include "IParameterSync.h"
#include "IParameterSource.h"
#include "IParameterSetter.h"
#include "IFactory.h"

namespace rp::trevor
{
    class ParameterSyncSet : public IParameterSync
    {
    public:
        ~ParameterSyncSet() = default;

        ParameterSyncSet(IParameterSource& parameterStateSource,
                         IParameterSetter& parameterSetter,
                         const IFactory& factory);

    private:
        std::vector<ParameterSyncPtr> parameterSyncs_;
    };
}
