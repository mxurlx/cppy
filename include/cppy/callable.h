#ifndef CPPY_CALLABLE_H
#define CPPY_CALLABLE_H

#include <type_traits>

namespace cppy
{
    namespace Capsule
    {
        template <typename T>
        struct is_callable
        {
            private:
                template <typename U>
                static auto test(U* p) -> decltype((*p)(), void(), std::true_type{});

                template <typename U>
                static auto test(...) -> std::false_type;

            public:
                static constexpr bool value = decltype(test<T>(nullptr))::value;
        };
    }

    // Checks if the input is callable.
    template<typename T>
    inline bool callable(const T&)
    {
        if constexpr (Capsule::is_callable<T>::value)
            return true;
        else
            return false;
    }
}

#endif