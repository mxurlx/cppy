#ifndef CPPY_STR_H
#define CPPY_STR_H

#include <string>

namespace cppy
{
    // Converts the input into a string.
    template<typename T>
    inline std::string str(const T& inp)
    {
        return std::to_string(inp);
    }

    // Converts the input into a string.
    inline std::string str(const char* inp)
    {
        return inp;
    }

    // Converts the input into a string.
    inline std::string str(std::string inp)
    {
        return inp;
    }
}

#endif