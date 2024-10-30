#ifndef CPPY_MAX_H
#define CPPY_MAX_H

#include "contain/containersum.h"

namespace cppy
{

    // Returns the biggest object among all the parsed ones.
    template<typename First, typename... Args>
    inline auto max(First first, Args... args)
    {
        auto res = first;
        if constexpr (Capsule::is_container<First>::value &&
        (Capsule::is_container<decltype(args)>::value && ...))
        {
                (..., [&]
                {
                    if (Capsule::container_sum(args,true) >= Capsule::container_sum(res,true)) // tema nomer 4
                        res = args;
                }());
                return res;
        } else if constexpr (!Capsule::is_container<First>::value &&
        (!Capsule::is_container<decltype(args)>::value && ...))
        {
            (..., [&]
            {
                if (args >= res)
                    res = args;
            }());
            return res;
        } else
            throw std::runtime_error("Error in max(): Cannot work with containers and non-containers at the same time");
    }

    // Returns the biggest object in the container.
    template<typename Iterable>
    inline auto max(Iterable container)
    {
        if constexpr (!Capsule::is_container<Iterable>::value)
            return container;
        else
            return Capsule::container_max(container);
    }
}

#endif