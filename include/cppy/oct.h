#ifndef CPPY_OCT_H
#define CPPY_OCT_H

#include <string>
#include <stdexcept>

namespace cppy
{
    // Converts an integer to an octal string prefixed with "0o"
    template<typename T>
    std::string oct(T inp)
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
                return "0o0";
            while (inp > 0)
            {
                res = std::to_string(inp % 8) + res;
                inp /= 8;
            }
            res = "0o" + res;
            if (is_neg)
                res = '-' + res;
            return res;
        }
        else
            throw std::runtime_error("Error in oct(): Input is not an integer");
    }
}

#endif