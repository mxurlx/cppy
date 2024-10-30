#ifndef CPPY_ALL_H
#define CPPY_ALL_H

#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <iostream>
#include "contain/is_container.h"

namespace cppy
{
    namespace Capsule
    {
        template<typename T>
        inline bool all_(const T& container);

        template<typename T>
        auto parse_container(const T& inp)
        {
            if constexpr (is_container<T>::value)
                return all_(inp);
            else
                return inp;
        }

        template<typename T>
        inline bool all_(const T& container)
        {
            for (auto i : container)
                if (!parse_container(i))
                    return false;
            return true;
        }

        template<typename T>
        inline bool all_m(const T& container)
        {
            for (auto pair : container)
                if (!pair.first)
                    return false;
            return true;
        }
    }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T, size_t N>
    inline bool all(T (&arr)[N])
    {
        for (T i : arr)
            if (!i)
                return false;
        return true;
    }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::vector<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::deque<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::forward_list<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::list<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::set<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::multiset<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::unordered_set<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T>
    inline bool all(const std::unordered_multiset<T>& inp) { return Capsule::all_(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T, typename U>
    inline bool all(const std::map<T,U>& inp) { return Capsule::all_m(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T, typename U>
    inline bool all(const std::multimap<T,U>& inp) { return Capsule::all_m(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T, typename U>
    inline bool all(const std::unordered_map<T,U>& inp) { return Capsule::all_m(inp); }

    // Returns true all elements of the container are true, otherwise it returns false.
    template <typename T, typename U>
    inline bool all(const std::unordered_multimap<T,U>& inp) { return Capsule::all_m(inp); }
}

#endif