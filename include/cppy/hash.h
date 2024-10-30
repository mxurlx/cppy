#ifndef CPPY_HASH_H
#define CPPY_HASH_H

#include <functional>
#include "contain/is_container.h"

namespace cppy
{
    namespace Capsule
    {
        template <typename T>
        inline size_t customHash(const T& value)
        {
            return std::hash<T>{}(value);
        }

        inline size_t customHash(const char* inp)
        {
            size_t length = 0;
            while (inp[length] != '\0') length++;
            
            size_t seed = length;

            for (size_t it = 0; it < length; it++) {
                seed ^= customHash(inp[it]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }

        template<typename T>
        inline size_t containerhash(const T& inp, size_t& seed)
        {
            for (size_t it = 0; it < inp.size(); it++)
            {
                if constexpr (is_container<typename T::value_type>::value)
                    containerhash(inp[it], seed);
                else
                {
                    seed ^= customHash(inp[it]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
            }
            return seed;
        }
    }

    // Returns the hash value of the input.
    template<typename T>
    inline size_t hash(const T& inp)
    {
        if constexpr (Capsule::is_container<T>::value)
        {
            size_t seed = inp.size();
            return Capsule::containerhash(inp, seed);
        }
        else
            return Capsule::customHash(inp);
    }
}

#endif