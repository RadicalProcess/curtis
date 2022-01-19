#pragma once

#include <string_view>

#include "IParameterSync.h"
#include "IParameterSource.h"
#include "IParameterSetter.h"
#include "ParameterSpec.h"

namespace rp::curtis
{
    class ParameterSync : public IParameterSync
                        , public IParameterSource::Listener
    {
    public:
        ParameterSync(IParameterSource& parameterSource, size_t parameterHash, IParameterSetter& parameterSetter);

        ~ParameterSync() override;

    private:

        void onParameterChanged(float value) override;

        IParameterSource& parameterSource_;
        const size_t parameterHash_;
        IParameterSetter& parameterSetter_;
    };
}
