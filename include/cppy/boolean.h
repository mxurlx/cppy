#ifndef CPPY_BOOLEAN_H
#define CPPY_BOOLEAN_H

#include "contain/is_container.h"

namespace cppy
{
    // Returns the bool value of the input. If the input is a container, the function returns false if it's empty, otherwise it return true.
    template<typename T>
    inline bool boolean(const T& inp)
    {
        if constexpr (Capsule::is_container<T>::value)
        {
            if (inp.empty())
                return false;
            else
                return true;
        }
        else
        {
            if (!inp)
                return false;
            else
                return true;
        }
    }
}

#endif