#ifndef CPPY_SORTED_H
#define CPPY_SORTED_H

#include "contain/containersum.h"
#include <functional>
#include <vector>


struct Reverse
{
    bool val = false;
};

struct Key
{
    std::function<int(int)> val;
};

namespace cppy
{
    namespace Capsule
    {
        static const int RUN = 32;

        template<typename T, typename Key>
        inline void insertionSort(T& inp, int left, int right, const bool& reverse, Key& key)
        {
            for (int i = left+1; i <= right; i++)
            {
                typename T::value_type temp = inp[i];
                int j = i - 1;
                if (reverse)
                {
                    while (j >= left && key(inp[j]) < key(temp))
                    {
                        inp[j+1] = inp[j];
                        j--;
                    }
                }
                else
                {
                    while (j >= left && key(inp[j]) > key(temp))
                    {
                        inp[j+1] = inp[j];
                        j--;
                    }
                }
                inp[j+1] = temp;
            }
        }

        template<typename T>
        inline void insertionSort(T& inp, int left, int right, const bool& reverse)
        {
            for (int i = left+1; i <= right; i++)
            {
                typename T::value_type temp = inp[i];
                int j = i - 1;
                if (reverse)
                    while (j >= left && noncontainer_sum(inp[j]) < noncontainer_sum(temp))
                    {
                        inp[j+1] = inp[j];
                        j--;
                    }
                else
                    while (j >= left && noncontainer_sum(inp[j]) > noncontainer_sum(temp))
                    {
                        inp[j+1] = inp[j];
                        j--;
                    }
                inp[j+1] = temp;
            }
        }

        template<typename T, typename Key>
        inline void merge(T& inp, int l, int m, int r, const bool& reverse, Key& key)
        {
            int len1 = m - l + 1, len2 = r - m;

            std::vector<typename T::value_type> left(len1);
            std::vector<typename T::value_type> right(len2);

            for (int i = 0; i < len1; i++)
                left[i] = inp[l + i];
            for (int i = 0; i < len2; i++)
                right[i] = inp[m + 1 + i];

            int i = 0, j = 0, k = l;

            if (reverse)
                while (i < len1 && j < len2) {
                    if (key(left[i]) >= key(right[j]))
                    {
                        inp[k] = left[i];
                        i++;
                    } else
                    {
                        inp[k] = right[j];
                        j++;
                    }
                    k++;
                }
            else
                while (i < len1 && j < len2)
                {
                    if (key(left[i]) <= key(right[j]))
                    {
                        inp[k] = left[i];
                        i++;
                    } else
                    {
                        inp[k] = right[j];
                        j++;
                    }
                    k++;
                }

            while (i < len1)
            {
                inp[k] = left[i];
                k++;
                i++;
            }

            while (j < len2)
            {
                inp[k] = right[j];
                k++;
                j++;
            }
        }

        template <typename T>
        inline void merge(T& inp, int l, int m, int r, const bool& reverse)
        {
            int len1 = m - l + 1, len2 = r - m;

            std::vector<typename T::value_type> left(len1);
            std::vector<typename T::value_type> right(len2);

            for (int i = 0; i < len1; i++)
                left[i] = inp[l + i];
            for (int i = 0; i < len2; i++)
                right[i] = inp[m + 1 + i];

            int i = 0, j = 0, k = l;

            if (reverse)
                while (i < len1 && j < len2) {
                    if (noncontainer_sum(left[i]) >= noncontainer_sum(right[j]))
                    {
                        inp[k] = left[i];
                        i++;
                    } else
                    {
                        inp[k] = right[j];
                        j++;
                    }
                    k++;
                }
            else
                while (i < len1 && j < len2)
                {
                    if (noncontainer_sum(left[i]) <= noncontainer_sum(right[j]))
                    {
                        inp[k] = left[i];
                        i++;
                    } else
                    {
                        inp[k] = right[j];
                        j++;
                    }
                    k++;
                }

            while (i < len1)
            {
                inp[k] = left[i];
                k++;
                i++;
            }

            while (j < len2)
            {
                inp[k] = right[j];
                k++;
                j++;
            }
        }

        template<typename T, typename Key>
        inline void timSort(T& inp, int n, const bool& reverse, Key& key)
        {
            for (int i = 0; i < n; i += RUN)
                insertionSort(inp, i, std::min((i+RUN-1), (n-1)), reverse, key);
            
            for (int size = RUN; size < n; size = 2 * size)
                for (int left = 0; left < n; left += 2 * size)
                {
                    int mid = left + size - 1;
                    int right = std::min((left + 2*size - 1), (n-1));
                    if (mid < right)
                        merge(inp, left, mid, right, reverse, key);
                }
        }

        template<typename T>
        inline void timSort(T& inp, int n, const bool& reverse)
        {
            for (int i = 0; i < n; i += RUN)
                insertionSort(inp, i, std::min(i+RUN-1, n-1), reverse);
            
            for (int size = RUN; size < n; size = 2 * size)
                for (int left = 0; left < n; left += 2 * size)
                {
                    int mid = left + size - 1;
                    int right = std::min(left + 2*size - 1, n-1);
                    if (mid < right)
                        merge(inp, left, mid, right, reverse);
                }
        }
    }

    // Sorts the container. Key and Reverse, if present, must be parsed like structs after the container in any order.
    template<typename T>
    inline T sorted(T inp)
    {
        if constexpr (Capsule::is_container<T>::value)
        {
            Capsule::timSort(inp, inp.size(), false);
            return inp;
        } else
            throw std::runtime_error("Error in sorted(): Non-container type is parsed");
    }

    // Sorts the container. Key and Reverse, if present, must be parsed like structs after the container in any order.
    template<typename T>
    inline T sorted(T inp, Reverse&& reverse)
    {
        if constexpr (Capsule::is_container<T>::value)
        {
            Capsule::timSort(inp, inp.size(), reverse.val);
            return inp;
        } else
            throw std::runtime_error("Error in sorted(): Non-container type is parsed");
    }

    // Sorts the container. Key and Reverse, if present, must be parsed like structs after the container in any order.
    template<typename T>
    inline T sorted(T inp, Key&& key)
    {
        if constexpr (Capsule::is_container<T>::value)
        {
            Capsule::timSort(inp, inp.size(), false, key.val);
            return inp;
        } else
            throw std::runtime_error("Error in sorted(): Non-container type is parsed");
    }

    // Sorts the container. Key and Reverse, if present, must be parsed like structs after the container in any order.
    template<typename T>
    inline T sorted(T inp, Key&& key, Reverse&& reverse)
    {
        if constexpr (Capsule::is_container<T>::value)
        {
            Capsule::timSort(inp, inp.size(), reverse.val, key.val);
            return inp;
        } else
            throw std::runtime_error("Error in sorted(): Non-container type is parsed");
    }

    // Sorts the container. Key and Reverse, if present, must be parsed like structs after the container in any order.
    template<typename T>
    inline T sorted(T inp, Reverse&& reverse, Key&& key)
    {
        if constexpr (Capsule::is_container<T>::value)
        {
            Capsule::timSort(inp, inp.size(), reverse.val, key.val);
            return inp;
        } else
            throw std::runtime_error("Error in sorted(): Non-container type is parsed");
    }
}

#endif