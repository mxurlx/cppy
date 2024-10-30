#ifndef CPPY_FILTER_H
#define CPPY_FILTER_H

#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>

namespace cppy
{
    // Constructs a container from those elements of the input for which function is true.
    template<typename Func, typename T>
    inline std::vector<T> filter(Func func, const std::vector<T>& inp)
    {
        std::vector<T> res;
        for (const auto& it : inp)
            if (func(it))
                res.push_back(it);
        return res;
    }

    // Constructs a container from those elements of the input for which function is true.
    template<typename Func, typename T>
    inline std::deque<T> filter(Func func, const std::deque<T>& inp)
    {
        std::deque<T> res;
        for (const auto& it : inp)
            if (func(it))
                res.push_back(it);
        return res;
    }

    template<typename Func, typename T>
    inline std::list<T> filter(Func func, const std::list<T>& inp)
    {
        std::list<T> res;
        for (const auto& it : inp)
            if (func(it))
                res.push_back(it);
        return res;
    }

    // Constructs a container from those elements of the input for which function is true.
    template<typename Func, typename T>
    inline std::set<T> filter(Func func, const std::set<T>& inp)
    {
        std::set<T> res;
        for (const auto& it : inp)
            if (func(it))
                res.insert(it);
        return res;
    }

    // Constructs a container from those elements of the input for which function is true.
    template<typename Func, typename T>
    inline std::multiset<T> filter(Func func, const std::multiset<T>& inp)
    {
        std::multiset<T> res;
        for (const auto& it : inp)
            if (func(it))
                res.insert(it);
        return res;
    }

    // Constructs a container from those elements of the input for which function is true.
    template<typename Func, typename T>
    inline std::unordered_set<T> filter(Func func, const std::unordered_set<T>& inp)
    {
        std::unordered_set<T> res;
        for (const auto& it : inp)
            if (func(it))
                res.insert(it);
        return res;
    }

    // Constructs a container from those elements of the input for which function is true.
    template<typename Func, typename T>
    inline std::forward_list<T> filter(Func func, const std::forward_list<T>& inp)
    {
        std::forward_list<T> res;
        for (const auto& it : inp)
            if (func(it))
                res.push_front(it);
        return res;
    }

    // Had to do it through overloads due to container types having different element insertion methods.
}

#endif