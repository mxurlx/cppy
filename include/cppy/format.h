#ifndef CPPY_FORMAT_H
#define CPPY_FORMAT_H

#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "bin.h"
#include "round.h"



namespace cppy
{
    namespace Capsule
    {
        static bool hashmodifier = false;

        static int dot = -1;

        template <typename T>
        struct is_string
        {
            static constexpr bool value = std::is_convertible_v<T, std::string> || std::is_same_v<T, const char*>;
        };

        template<typename T>
        inline void inssep(const T& inp, std::string& out, char& sep)
        {
            size_t len = out.size();
            size_t it = 3;
            int n = 0;
            if (inp < 0)
            {
                it++;
                n++;
            }
            if (hashmodifier)
            {
                it += 2;
                n += 2;
            }
            if (!std::is_same_v<T, double> && !std::is_same_v<T, float>)
                for (; it < len; it += 3)
                    out.insert(len-it+n, 1, sep);
            else
                throw std::runtime_error("Error in format(): Cannot insert separators in a floating point number");
        }

        inline int cstrlen(const char* inp)
        {
            int res = 0;
            for (size_t it = 0; inp[it] != '\0'; it++) res++;
            return res;
        }

        inline int8_t checkchar(const char& inp)           // Didn't want to include <map>
        {
            switch (inp)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    return 0;
                    break;
                case '<':
                    return 1;
                    break;
                case '>':
                    return 1;
                    break;
                case '^':
                    return 1;
                    break;
                case '=':
                    return 1;
                    break;
                case '+':
                    return 2;
                    break;
                case '-':
                    return 2;
                    break;
                case ' ':
                    return 2;
                    break;
                case '#':
                    return 3;
                    break;
                case '_':
                    return 4;
                    break;
                case ',':
                    return 4;
                    break;
                case '.':
                    return 5;
                    break;
                case 'b':
                    return 6;
                    break;
                case 'c':
                    return 6;
                    break;
                case 'd':
                    return 6;
                    break;
                case 'e':
                    return 6;
                    break;
                case 'E':
                    return 6;
                    break;
                case 'f':
                    return 6;
                    break;
                case 'F':
                    return 6;
                    break;
                case 'g':
                    return 6;
                    break;
                case 'G':
                    return 6;
                    break;
                case 'n':
                    return 6;
                    break;
                case 'o':
                    return 6;
                    break;
                case 's':
                    return 6;
                    break;
                case 'x':
                    return 6;
                    break;
                case 'X':
                    return 6;
                    break;
                case '%':
                    return 6;
                    break;
                default:
                    return -1;
                    break;
            }
        }

        inline void findhash(std::string& fmt)
        {
            int p = fmt.find('#');
            if (p != -1)
            {
                fmt.erase(p,p+1);
                hashmodifier = true;
            }
        }

        inline int extractnum(std::string& fmt)
        {
            std::string res = "";
            while (fmt.back() >= 48 && fmt.back() <= 57)
            {
                res = fmt.back() + res;
                fmt.pop_back();
            }
            return std::stoi(res);
        }

        template<typename T>
        inline void fill(const T& inp, std::string& out, std::string& fmt, std::ostringstream& oss, const int& space)
        {
            std::string strfmt = fmt.substr(0,2);
            fmt.erase(0,2);
            oss << std::setfill(strfmt[0]);
            switch (strfmt[1])
            {
                case '<':
                    oss << std::left << std::setw(space) << out;
                    break;
                case '>':
                    oss << std::right << std::setw(space) << out;
                    break;
                case '=':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Align mode \'=\' does not support strings.");
                    else
                    {
                        if (inp < 0)
                            oss << std::right << '-' << std::setw(space-1) << out.substr(1);
                        else
                            oss << std::right << std::setw(space) << out;
                        break;
                    }
                case '^':
                    int left = (space - out.size()) >> 1;       // Bit shifting is faster than division
                    int right = space - out.size() - left;
                    oss << std::setw(left) << "" << out << std::setw(right) << "";
                    break;
            }
        }

        template<typename T>
        inline void sign(const T& inp, std::string& out, std::string& fmt, std::ostringstream& oss)
        {
            switch (fmt.back())
            {
                case '+':
                    if (inp >= 0)
                        out = '+' + out;
                    break;
                case ' ':
                    if (inp >= 0)
                        out = ' ' + out;
                    break;
                default:
                    break;
            }
            fmt.pop_back();
            if (fmt.empty())
                oss << out;
        }

        template<typename T>
        inline void fmtype(const T& inp, std::string& out, std::string& fmt, std::ostringstream& oss)
        {
            char type = fmt.back();
            fmt.pop_back();
            std::ostringstream oss_;
            switch (type)
            {
                case 'b':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'b\' does not support strings.");
                    else
                    {
                        if (hashmodifier)
                            out = bin(inp);
                        else
                        {
                            if (inp >= 0)
                                out = bin(inp).substr(2);
                            else
                                out = bin(inp)[0] + bin(inp).substr(3);
                        }
                    }

                    if (fmt.empty())
                        oss << out;
                    break;
                case 'c':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'c\' does not support strings.");
                    else
                        out = std::string(1, static_cast<char>(inp));

                    if (fmt.empty())
                        oss << out;
                    break;
                case 'd':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'d\' does not support strings.");
                    else
                        out = std::to_string((int)(inp));

                    if (fmt.empty())
                        oss << out;
                    break;
                case 'e':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'e\' does not support strings.");
                    else
                        oss << std::scientific;

                    if (fmt.empty())
                        oss << std::stod(out);
                    break;
                case 'E':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'E\' does not support strings.");
                    else
                        oss << std::uppercase << std::scientific;

                    if (fmt.empty())
                        oss << std::stod(out);
                    break;
                case 'f':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'f\' does not support strings.");
                    else
                        oss << std::fixed;
                    
                    oss_.copyfmt(oss);

                    oss_ << inp;
                    out = oss_.str();

                    if (fmt.empty())
                        oss << std::stod(out);
                    break;
                case 'F':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'F\' does not support strings.");
                    else
                        oss << std::uppercase << std::fixed;
                    
                    oss_.copyfmt(oss);

                    oss_ << inp;
                    out = oss_.str();

                    if (fmt.empty())
                        oss << std::stod(out);
                    break;
                case 'g':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'g\' does not support strings.");
                    else
                        if (inp >= 1000000)
                            oss << std::scientific;

                    if (fmt.empty())
                        oss << std::stod(out);
                    break;
                case 'G':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'G\' does not support strings.");
                    else
                        if (inp >= 1000000)
                            oss << std::uppercase << std::scientific;

                    if (fmt.empty())
                        oss << std::stod(out);
                    break;
                case 'n':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'n\' does not support strings.");

                    if (fmt.empty())
                        oss << inp;
                    break;
                case 'o':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'o\' does not support strings.");
                    else
                        oss << std::oct;

                    oss_.copyfmt(oss);

                    oss_ << inp;
                    out = oss_.str();

                    if (hashmodifier)
                        out = "0o" + out;

                    if (fmt.empty())
                        oss << out;
                    break;
                case 's':
                    if constexpr (!is_string<T>::value)
                        out = std::to_string(inp);
                    
                    if (fmt.empty())
                        oss << out;
                    break;
                case 'x':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'x\' does not support strings.");
                    else
                        oss << std::hex;

                    oss_.copyfmt(oss);

                    oss_ << inp;
                    out = oss_.str();

                    if (hashmodifier)
                        out = "0x" + out;

                    if (fmt.empty())
                        oss << out;
                    break;
                case 'X':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'X\' does not support strings.");
                    else
                        oss << std::uppercase << std::hex;

                    oss_.copyfmt(oss);

                    oss_ << inp;
                    out = oss_.str();
                    
                    if (hashmodifier)
                        out = "0X" + out;

                    if (fmt.empty())
                        oss << out;
                    break;
                case '%':
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Type mode \'%\' does not support strings.");
                    else
                        out = std::to_string(inp*100) + '%';

                    if (fmt.empty())
                        oss << out;
                    break;
            }
        }

        template<typename T>
        inline void roundup(const T& inp, std::string& out, std::string& fmt, std::ostringstream& oss, const int& dig)
        {
            fmt.pop_back();
            out = std::to_string(cppy::round((double)(inp), dig));
            if (fmt.empty())
                oss << std::stod(out);
        }

        template<typename T>
        inline std::string format_(const T& inp, std::string& out, std::string& fmt, std::ostringstream& oss)
        {   
            switch (checkchar(fmt.back()))
            {
                case -1:
                    throw std::runtime_error("Error in format(): Unknown format type");
                case 0:
                {
                    if (dot != -1)
                    {
                        int dig = extractnum(fmt);
                        if constexpr (is_string<T>::value)
                        {
                            fmt.pop_back();
                            out = out.substr(0, dig);
                            if (fmt.empty())
                                oss << out;
                        }
                        else
                            roundup(inp, out, fmt, oss, dig);
                        dot = -1;
                    } else
                    {
                        int shift = extractnum(fmt);
                        if (fmt.size() == 2)
                        {
                            if (checkchar(fmt.back()) == 1)
                                fill(inp, out, fmt, oss, shift);
                        } else if (fmt.size() == 1)
                            fmt.pop_back();
                        else
                            throw std::runtime_error("Error in format(): Digit(s) in the wrong position.");
                    }
                    break;
                }
                case 1:
                    while (!fmt.empty())
                        fmt.pop_back();
                    oss << out;
                    break;
                case 2:
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Cannot sign a string.");
                    else
                    {
                        sign(inp, out, fmt, oss);
                    }
                    break;
                case 4:
                {
                    if constexpr (is_string<T>::value)
                        throw std::runtime_error("Error in format(): Cannot insert separators into a string.");
                    else
                    {
                        char sep = fmt.back();
                        inssep(inp, out, sep);
                        fmt.pop_back();
                        if (fmt.empty())
                            oss << out;
                        break;
                    }
                }
                
                case 6:
                    fmtype(inp, out, fmt, oss);
                    break;
            }

            if (!fmt.empty())
                format_(inp, out, fmt, oss);

            hashmodifier = false;
            dot = -1;
            return oss.str();
        }
    }

    // Formats the input.
    template<typename T>
    inline std::string format(const T& inp, std::string& fmt)
    {
        std::ostringstream oss;
        std::string fmt_ = fmt;
        std::string out;
        if constexpr (Capsule::is_string<T>::value)
            out = inp;
        else
            out = std::to_string(inp);
        Capsule::findhash(fmt_);

        Capsule::dot = fmt_.find('.');

        Capsule::format_(inp, out, fmt_, oss);
        return oss.str();
    }

    // Formats the input.
    template<typename T>
    inline std::string format(const T& inp, const char* fmt)
    {
        std::ostringstream oss;
        std::string fmt_ = fmt;
        std::string out;
        if constexpr (Capsule::is_string<T>::value)
            out = inp;
        else
            out = std::to_string(inp);
        Capsule::findhash(fmt_);

        Capsule::dot = fmt_.find('.');

        Capsule::format_(inp, out, fmt_, oss);
        return oss.str();
    }

    // Formats the input.
    template<typename T>
    inline std::string format(const T& inp, const char&& fmt)
    {
        std::ostringstream oss;
        std::string fmt_ = std::string(1, fmt);
        std::string out;
        if constexpr (Capsule::is_string<T>::value)
            out = inp;
        else
            out = std::to_string(inp);
        Capsule::findhash(fmt_);

        Capsule::dot = fmt_.find('.');

        Capsule::format_(inp, out, fmt_, oss);
        return oss.str();
    }
}

#endif