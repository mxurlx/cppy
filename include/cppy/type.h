#ifndef CPPY_TYPE_H
#define CPPY_TYPE_H

#include <string>
#include <typeinfo>

namespace cppy
{
    // Returns typename of the input.
    template<typename T>
    inline std::string type(const T& inp)
    {
        return typeid(inp).name();
    }
}

#endif