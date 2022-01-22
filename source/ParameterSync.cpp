#include "ParameterSync.h"

namespace rp::curtis
{
    ParameterSync::ParameterSync(IParameterSource& parameterSource, size_t parameterHash, IParameterSetter& parameterSetter)
    : parameterSource_(parameterSource)
    , parameterHash_(parameterHash)
    , parameterSetter_(parameterSetter)
    {
        parameterSource_.addListener(this);
    }

    ParameterSync::~ParameterSync()
    {
        parameterSource_.removeListener(this);
    }

    void ParameterSync::onParameterChanged(float value)
    {
        parameterSetter_.setParameter(parameterHash_, value);
    }
}
