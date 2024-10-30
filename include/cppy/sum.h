#ifndef CPPY_SUM_H
#define CPPY_SUM_H

#include "contain/containersum.h"

namespace cppy
{
    // Sums start and the elements of a container and returns the total. The container's elements are normally numbers.
    template<typename T>
    inline auto sum(const T& inp, double start = 0)
    {
        return Capsule::container_sum(inp) + start;
    }
}

#endif