#pragma once
#include <type_traits>

namespace lte
{
namespace util
{
    struct EnumClassHash
    {
        template<typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };
    
    template<typename Key>
    using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;
}
}