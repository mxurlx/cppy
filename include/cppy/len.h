#ifndef CPPY_LEN_H
#define CPPY_LEN_H

#include <type_traits>
#include <stdexcept>

namespace cppy
{
    // Returns the length of the input.
    template<typename T>
    inline size_t len(const T& inp)
    {
        if constexpr (std::is_class_v<T>)
            return inp.size();
        else
            throw std::runtime_error("Error in len(): Unsupported type");
    }

    // Returns the length of the input.
    template<typename T, size_t N>
    inline size_t len(const T (&)[N])
    {
        return N;
    }

    // Return the length of the input
    inline size_t len(const char* inp)
    {
        size_t res = 0;
        while (inp[res] != '\0') res++;
        return res;
    }
}

#endif