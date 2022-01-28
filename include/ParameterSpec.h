#pragma once

#include <string_view>
#include <boost/functional/hash.hpp>
#include <utility>
#include <curtis_core/Curtis.h>

namespace rp::curtis
{
    inline
    size_t getHash(const std::string_view& str)
    {
        const auto stringHash = boost::hash<std::string_view>();
        return stringHash(str);
    }

    struct ParameterSpec
    {
    public:
        enum Type
        {
            Float,
            Int,
            Bool
        };

        explicit ParameterSpec(std::string_view _name, std::string_view _id, std::string_view _unit, Type _type, float _min, float _max, float _init, std::function<void(
                Curtis&, float value)> _setter)
        : name(_name)
        , id(_id)
        , unit(_unit)
        , hash(getHash(name))
        , type(_type)
        , min(_min)
        , max(_max)
        , init(_init)
        , setter(std::move(_setter))
        {}

        const std::string_view name;
        const std::string_view id;
        const std::string_view unit;
        const size_t hash;
        const Type type;
        const float min;
        const float max;
        const float init;
        const std::function<void(Curtis&, float value)> setter;
    };
}
