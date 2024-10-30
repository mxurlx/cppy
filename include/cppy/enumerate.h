#ifndef CPPY_ENUMERATE_H
#define CPPY_ENUMERATE_H

#include <map>

namespace cppy
{
    // Adds a counter as the key to the container.
    template<typename T>
    inline std::map<int, typename T::value_type> enumerate(const T& inp, const int& start = 0)
    {
        int i = start;
        std::map<int, typename T::value_type> res;
        for (const auto& it : inp)
        {
            res.insert(std::make_pair(i,it));
            i++;
        }
        return res;
    }

    // Adds a counter as the key to the container.
    template<typename T, size_t N>
    inline std::map<int, T> enumerate(T (&inp)[N], const int& start = 0)
    {
        int i = start;
        std::map<int, T> res;
        for (size_t it = 0; it < N; it++)
        {
            res.insert(std::make_pair(i,inp[it]));
            i++;
        }
        return res;
    }
}

#endif