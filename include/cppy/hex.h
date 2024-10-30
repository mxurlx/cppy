#ifndef CPPY_HEX_H
#define CPPY_HEX_H

#include <string>
#include <map>
#include <stdexcept>

namespace cppy
{

    // Converts an integer to a lowercase hexadecimal string prefixed with "0x"
    template<typename T>
    inline std::string hex(T inp)
    {
        std::map<int, std::string> m{
            {10,"a"},
            {11,"b"},
            {12,"c"},
            {13,"d"},
            {14,"e"},
            {15,"f"}
            };
        if constexpr (!std::is_floating_point_v<T>)
        {
            std::string res;
            bool is_neg;
            if (inp < 0)
            {
                inp *= -1;
                is_neg = true;
            } else if (inp == 0)
                return "0x0";
            while (inp > 0)
            {
                auto n = inp % 16;
                if (n > 9)
                    res = m[n] + res;
                else
                    res = std::to_string(n) + res;
                inp /= 16;
            }
            res = "0x" + res;
            if (is_neg)
                res = '-' + res;
            return res;
        }
        else
            throw std::runtime_error("Error in hex(): Input is not an integer");
    }
}

#endif