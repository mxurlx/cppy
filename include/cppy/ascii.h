#ifndef CPPY_ASCII_H
#define CPPY_ASCII_H

#include <string>

namespace cppy
{
    // Returns a string with a printable representation of characters.
    inline std::string ascii(const char* inp)
    {
        std::string res = "";
        for (size_t it = 0; inp[it] != '\0'; it++)
        {
            if (inp[it] >= 32 && inp[it] <= 126)
                res += inp[it];
            else
                res += "\\x" + std::to_string(static_cast<int>(inp[it]));
        }
        return res;
    }
    // Returns a string with a printable representation of characters.
    inline std::string ascii(const std::string& inp)
    {
        std::string res = "";
        for (const char& it : inp)
            res += static_cast<int>(it);
        return res;
    }
}

#endif