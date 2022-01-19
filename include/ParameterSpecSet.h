#pragma once

#include <array>
#include <stdexcept>
#include "ParameterSpec.h"

namespace rp::curtis
{
    extern const std::vector<ParameterSpec> parameterSpecSet;

    const ParameterSpec& getParameterSpec(std::string_view id);
}
