#ifndef CPPY_ISSUBCLASS_H
#define CPPY_ISSUBCLASS_H

#include <type_traits>

namespace cppy
{
    // Checks if a class is a subclass.
    template<typename SubClass, typename Class>
    inline bool issubclass()
    {
        return std::is_base_of_v<Class, SubClass>;
    }
}

#endif