#ifndef CPPY_RANGE_H
#define CPPY_RANGE_H

#include <vector>
#include <stdexcept>

namespace cppy
{
    // Returns the vector of integers, going from start till stop.
    inline std::vector<int> range(int start, int stop, int step = 1)
    {
        std::vector<int> res;
        
        if (step == 0)
            throw std::runtime_error("Error in range(): Range step must not be zero");

        if (step > 0)
            for (int i = start; i < stop; i += step)
                res.push_back(i);
        else
            for (int i = start; i > stop; i += step)
                res.push_back(i);
        return res;
    }

    // Returns the vector of integers, going till stop.
    inline std::vector<int> range(int stop)
    {
        std::vector<int> res;
        for (int i = 0; i < stop; i += 1)
            res.push_back(i);
        return res;
    }
}

#endif