#pragma once

#include <type_traits>
#include <stdexcept>

namespace cppy
{
    namespace Capsule
    {
        template <typename T>
        struct is_container
        {
            private:
                template <typename C>
                static std::true_type test(typename C::iterator*);
                
                template <typename C>
                static std::false_type test(...);

            public:
                static constexpr bool value = decltype(test<T>(nullptr))::value;
        };
    }
}