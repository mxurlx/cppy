#ifndef CPPY_ROUND_H
#define CPPY_ROUND_H

#include <cmath>
#include <stdexcept>

namespace cppy
{
    // Rounds up the input to digit
    inline double round(double num, int digit = 0)
    {
        if (digit < 0)
            throw std::runtime_error("Error in round(): digit cannot be less than zero");
        double scale = std::pow(10, digit);
        return std::round(num * scale) / scale; 
    }

    inline float round(float num, int digit = 0)
    {
        if (digit < 0)
            throw std::runtime_error("Error in round(): digit cannot be less than zero");
        float scale = std::pow(10, digit);
        return std::round(num * scale) / scale; 
    }
}

#endif