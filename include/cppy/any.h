#ifndef CPPY_ANY_H
#define CPPY_ANY_H

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
        inline bool any_(const T& container);

        template<typename T>
        auto parse_container_(const T& inp)
        {
            if constexpr (is_container<T>::value)
                return any_(inp);
            else
                return inp;
        }

        template<typename T>
        inline bool any_(const T& container)
        {
            for (auto i : container)
                if (parse_container_(i))
                    return true;
            return false;
        }

        template<typename T>
        inline bool any_m(const T& container)
        {
            for (auto pair : container)
                if (pair.first)
                    return true;
            return false;
        }
    }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T, size_t N>
    inline bool any(T (&arr)[N])
    {
        for (T i : arr)
            if (i)
                return true;
        return false;
    }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::vector<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::deque<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::forward_list<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::list<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::set<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::multiset<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::unordered_set<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T>
    inline bool any(const std::unordered_multiset<T>& inp) { return Capsule::any_(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T, typename U>
    inline bool any(const std::map<T,U>& inp) { return Capsule::any_m(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T, typename U>
    inline bool any(const std::multimap<T,U>& inp) { return Capsule::any_m(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T, typename U>
    inline bool any(const std::unordered_map<T,U>& inp) { return Capsule::any_m(inp); }

    // Returns true if atleast one of the element of the container is true, otherwise it returns false.
    template <typename T, typename U>
    inline bool any(const std::unordered_multimap<T,U>& inp) { return Capsule::any_m(inp); }
}

#endif