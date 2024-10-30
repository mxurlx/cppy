#ifndef CPPY_BIN_H
#define CPPY_BIN_H

#include <string>
#include <stdexcept>

namespace cppy
{
    // Converts an integer to a binary string prefixed with "0b".
    template<typename T>
    inline std::string bin(T inp)
    {
        if constexpr (!std::is_floating_point_v<T>)
        {
            std::string res;
            bool is_neg;
            if (inp < 0)
            {
                inp *= -1;
                is_neg = true;
            } else if (inp == 0)
                return "0b0";
            while (inp > 0)
            {
                res = std::to_string(inp % 2) + res;
                inp >>= 1;
            }
            res = "0b" + res;
            if (is_neg)
                res = '-' + res;
            return res;
        }
        else
            throw std::runtime_error("Error in bin(): Input is not an integer");
    }
}

#endif