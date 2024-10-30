#ifndef CPPY_DIVMOD_H
#define CPPY_DIVMOD_H

#include <vector>

namespace cppy
{
    // Returns the vector of the inputs' quotient and remainder.
    inline std::vector<int> divmod(const int& x, const int& y)
    {
        std::vector res = {x/y, x%y};
        return res;
    }
}

#endif