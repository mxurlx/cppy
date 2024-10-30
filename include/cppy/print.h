#ifndef CPPY_PRINT_H
#define CPPY_PRINT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <tuple>

struct Sep
{
    std::string_view val = " ";
};

struct End
{
    std::string_view val = "\n";
};

struct Flush
{
    bool val = false;
};

struct File
{
    std::ofstream* ofs = new std::ofstream("");
};


namespace cppy
{
    namespace Capsule
    {
        struct opt
        {
            Sep sep;
            End end;
            Flush flush;
            File file;
        };

        template <typename T>
        inline std::ostream& out_non_container(std::ostream& os, const T& value);

        template <typename T, size_t N>
        inline std::ostream& operator<<(std::ostream& os, T (&arr)[N])
        {
            if constexpr (!std::is_same_v<T, const char>)
            {
                os << '{' << arr[0];
                for (size_t i = 1; i < *(&arr+1)-arr; i++)
                    os << ',' << ' ' << arr[i];
                os << '}';
                return os;
            }
            else
                return out_non_container(os, arr);
        }

        template<typename T>
        struct is_tuple : std::false_type {};

        template<typename... Args>
        struct is_tuple<std::tuple<Args...>> : std::true_type {};

        inline std::ostream& out_tuple_empty(std::ostream& os, const std::tuple<>&)
        {
            os << '(' << ')';
            return os;
        }

        template <size_t I = 0, typename... Args>
        inline std::ostream& out_tuple(std::ostream& os, const std::tuple<Args...>& t)
        {
            if constexpr (I == 0)
                os << '(';
            if constexpr (I < sizeof...(Args))
            {
                if (I > 0)
                    os << ',' << ' ';
                os << std::get<I>(t);
                out_tuple<I+1>(os, t);
            }
            if constexpr (I == sizeof...(Args))
                os << ')';
            return os;
        }

        template <typename T>
        inline std::ostream& out_container(std::ostream& os, const T& container)
        {
            os << '{';
            auto it = container.begin();
            if constexpr (is_tuple<typename T::value_type>::value)
            {
                for (; it != container.end(); it++)
                {
                    out_tuple(os, *it);
                    if (std::next(it) != container.end())
                        os << ',' << ' ';
                }
            } else
            {
                if (it != container.end())
                {
                    out_non_container(os, *it);
                    for (it++; it != container.end(); it++)
                    {
                        os << ',' << ' ';
                        out_non_container(os, *it);
                    }
                }
            }
            os << '}';
            return os;
        }

        


        template <typename T>
        inline std::ostream& out_map(std::ostream& os, const T& map)
        {
            os << '{';
            auto it = map.begin();
            if (it != map.end())
            {
                os << '{' << it->first << ':' << ' ' << it->second << '}';
                for (it++; it != map.end(); it++)
                    os << ',' << ' ' << '{' << it->first << ':' << ' ' << it->second << '}';
            }
            os << '}';
            return os;
        }

        template <typename T>
        inline std::ostream& out_non_container(std::ostream& os, const T& value)
        {
            if constexpr (std::is_class_v<T> && !(std::is_same_v<T, std::string>))
                out_container(os, value);
            else
                os << value;
            return os;
        }

        inline std::ostream& operator<<(std::ostream& os, const char* str)
        {
            return out_non_container(os, str);
        }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& inp) { return out_container(os, inp); }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::deque<T>& inp) { return out_container(os, inp); }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::forward_list<T>& inp) { return out_container(os, inp); }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::list<T>& inp) { return out_container(os, inp); }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::set<T>& inp) { return out_container(os, inp); }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::multiset<T>& inp) { return out_container(os, inp); }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& inp) { return out_container(os, inp); }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& os, const std::unordered_multiset<T>& inp) { return out_container(os, inp); }

        template <typename T, typename U>
        inline std::ostream& operator<<(std::ostream& os, const std::map<T, U>& inp) { return out_map(os, inp); }

        template <typename T, typename U>
        inline std::ostream& operator<<(std::ostream& os, const std::multimap<T, U>& inp) { return out_map(os, inp); }

        template <typename T, typename U>
        inline std::ostream& operator<<(std::ostream& os, const std::unordered_map<T, U>& inp) { return out_map(os, inp); }

        template <typename T, typename U>
        inline std::ostream& operator<<(std::ostream& os, const std::unordered_multimap<T, U>& inp) { return out_map(os, inp); }

        template <typename... Args>
        inline std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& inp) { return out_tuple(os, inp); }

        inline std::ostream& operator<<(std::ostream& os, const std::tuple<>& inp) { return out_tuple_empty(os, inp); }

        template<typename First, typename... Args>
        inline void print_(opt& op, const First& first, Args&... args)
        {
            auto& stream = op.file.ofs->is_open() ? *op.file.ofs : std::cout;
            stream << first;
            ((stream << op.sep.val << args), ...);
            stream << op.end.val;
            if (op.flush.val)
                stream << std::flush;
        }

        template<typename...Args>
        inline void print_(opt& op, Sep& Sep, Args&... args)
        {
            op.sep = Sep;
            print_(op, args...);
        }

        template<typename...Args>
        inline void print_(opt& op, End& End, Args&... args)
        {
            op.end = End;
            print_(op, args...);
        }

        template<typename...Args>
        inline void print_(opt& op, Flush& Flush, Args&... args)
        {
            op.flush = Flush;
            print_(op, args...);
        }

        template<typename...Args>
        inline void print_(opt& op, File& File, Args&... args)
        {
            op.file = File;
            print_(op, args...);
        }

        inline void print_(opt& op)
        {
            auto& stream = op.file.ofs->is_open() ? *op.file.ofs : std::cout;
            stream << op.end.val;
            if (op.flush.val)
                stream << std::flush;
        }
    }

    // Prints objects. Sep, End, File, Flush, if present, must be parsed like structs before objects in any order.
    template<typename... Args>
    inline void print(Args&&... args)
    {
        Capsule::opt op;
        print_(op, args...);
    }
}

#endif