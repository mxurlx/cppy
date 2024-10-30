#ifndef CPPY_INTEGER_H
#define CPPY_INTEGER_H

#include <type_traits>
#include <string>
#include <stdexcept>

namespace cppy
{
    // Converts the input to an integer.
    template<typename T>
    inline int integer(const T& inp)
    {
        if constexpr (std::is_same_v<T, std::string>)
            return std::stoi(inp);
        else if constexpr (std::is_same_v<T, char>)
            return inp-'0';
        else if constexpr (std::is_same_v<T, int> ||
            std::is_same_v<T, float> ||
            std::is_same_v<T, double> ||
            std::is_same_v<T, long> ||
            std::is_same_v<T, long long>)
            return inp;
        else
            throw std::runtime_error("Error in integer(): Unsupported type is parsed");
    }

    // Converts the input to an integer.
    inline int integer(const char* inp)
    {
        int res = 0;
        while (*inp)
            res = res*10 + (*inp++ - '0');
        return res;
    }
}

#endif