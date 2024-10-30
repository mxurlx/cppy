#ifndef CPPY_FLOATP_H
#define CPPY_FLOATP_H

#include <type_traits>
#include <string>
#include <stdexcept>

namespace cppy
{
    // Converts the input to a double
    template<typename T>
    inline double floatp(const T& inp)
    {
        if constexpr (std::is_same_v<T, std::string>)
            return std::stod(inp);
        else if constexpr (std::is_same_v<T, char>)
            return inp-'0';
        else if constexpr (std::is_same_v<T, int> ||
            std::is_same_v<T, float> ||
            std::is_same_v<T, double> ||
            std::is_same_v<T, long> ||
            std::is_same_v<T, long long>)
            return inp;
        else
            throw std::runtime_error("Error in floatp(): Unsupported type is parsed");
    }

    inline double floatp(const char* inp)
    {
        return atof(inp);
    }
}

#endif