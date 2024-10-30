#ifndef CPPY_MIN_H
#define CPPY_MIN_H

#include "contain/containersum.h"

namespace cppy
{
    // Returns the smallest object among all the parsed ones.
    template<typename First, typename... Args>
    inline auto min(First first, Args... args)
    {
        auto res = first;
        if constexpr (Capsule::is_container<First>::value &&
        (Capsule::is_container<decltype(args)>::value && ...))
        {
                (..., [&]
                {
                    if (Capsule::container_sum(args,true) <= Capsule::container_sum(res,true))
                        res = args;
                }());
                return res;
        } else if constexpr (!Capsule::is_container<First>::value &&
        (!Capsule::is_container<decltype(args)>::value && ...))
        {
            (..., [&]
            {
                if (args <= res)
                    res = args;
            }());
            return res;
        } else
            throw std::runtime_error("Error in min(): Cannot work with containers and non-containers at the same time");
    }

    // Returns the smallest object in the container.
    template<typename Iterable>
    inline auto min(Iterable container)
    {
        if constexpr (!Capsule::is_container<Iterable>::value)
            return container;
        else
            return Capsule::container_min(container);
    }
}

#endif