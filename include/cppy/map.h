#ifndef CPPY_MAP_H
#define CPPY_MAP_H

#include "contain/is_container.h"

namespace cppy
{
    // Applies the function to every element of a container.
    template<typename Func, typename T>
    inline auto map(Func func, const T& inp)
    {
        if constexpr (!Capsule::is_container<T>::value)
            throw std::runtime_error("Error in map(): Non-container type is parsed");
        
        T res = inp;
        for (size_t i = 0; i < inp.size(); i++)
            res[i] = func(res[i]);
        return res;
    }
}

#endif