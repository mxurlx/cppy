#ifndef CPPY_REVERSED_H
#define CPPY_REVERSED_H

#include <cstddef>

namespace cppy
{
    // Reverses the container.
    template<typename T>
    inline T reversed(T inp)
    {
        for (size_t i = 0, j = inp.size()-1; i < j; i++, j--)
        {
            auto c = inp[i];
            inp[i] = inp[j];
            inp[j] = c;
        }
        return inp;
    }
}

#endif