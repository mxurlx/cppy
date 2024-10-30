#pragma once

#include "is_container.h"
#include <string>

namespace cppy
{
    namespace Capsule
    {
        // Handle containers
        template<typename T>
        inline auto container_sum(const T& container);

        template<typename T>
        inline auto container_max(const T& container);

        template<typename T>
        inline auto container_min(const T& container);

        inline int noncontainer_sum_F(const char* inp);

        template<typename T>
        inline auto noncontainer_sum(const T& inp, const bool& mult = true, const bool& mode = true)
        {
            if constexpr (is_container<T>::value)
                if (mult)
                    return container_sum(inp);
                else
                {
                    if (mode)
                        return container_max(inp);
                    else
                        return container_min(inp);
                }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                int count = 0;
                if constexpr (std::is_same_v<T, std::string>)
                    for (char c : inp)
                        count += c;
                return count;
            } else if constexpr (std::is_same_v<T, const char*>)
                return noncontainer_sum_F(inp);
            else
                return inp;
        }

        inline int noncontainer_sum_F(const char* inp)
        {
            int count = 0;
            for (size_t c = 0; inp[c] != '\0'; c++)
                count += inp[c];
            return count;
        }

        template<typename T>
        inline auto container_sum(const T& container)
        {
            auto res = noncontainer_sum(container[0],true);
            if constexpr (!std::is_same_v<T, const char*>)
                for (auto it : container)
                    res += noncontainer_sum(it,true);
            else
                return noncontainer_sum_F(container);
            return res-noncontainer_sum(container[0],true);
        }

        template<typename T>
        inline auto container_min(const T& container)
        {
            auto res = noncontainer_sum(container[0],false,false);
            for (auto it : container)
                if (noncontainer_sum(it,false,false) <= res)
                    res = noncontainer_sum(it,false,false);
            return res;
        }

        template<typename T>
        inline auto container_max(const T& container)
        {
            auto res = noncontainer_sum(container[0],false,true);
            for (auto it : container)
                if (noncontainer_sum(it,false,true) >= res)
                    res = noncontainer_sum(it,false,true);
            return res;
        }
    }
}