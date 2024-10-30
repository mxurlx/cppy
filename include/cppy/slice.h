#ifndef CPPY_SLICE_H
#define CPPY_SLICE_H

#include <stdexcept>

namespace cppy
{
    // Slices the container till end.
    template<typename T>
    T slice(const T& inp, const int& end)
    {
        T res;
        for (int i = 0; i < end; i++)
            res.push_back(inp[i]);
        return res;
    }

    // Slices the container from start till end.
    template<typename T>
    T slice(const T& inp, const int& start, const int& end, const int& step = 1)
    {
        if (step  == 0)
            throw std::runtime_error("Error in slice(): Step cannot be zero");
        T res;
        if (step > 0)
        {
            for (int i = start; i < end; i += step)
                res.push_back(inp[i]);
            return res;
        } else
        {
            for (int i = start; i > end; i += step)
                res.push_back(inp[i]);
            return res;
        }
    }
}

#endif