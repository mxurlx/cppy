#ifndef CPPY_EXEC_H
#define CPPY_EXEC_H

#include <string>
#include <fstream>
#include <type_traits>
#include <filesystem>

namespace cppy
{
    namespace Capsule
    {
        template<typename T>
        inline void handle_libs(std::ofstream& source, const T& inp) 
        {
            if constexpr (std::is_same_v<T, std::string> ||
                (std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, char>))
                source << "\n#include \"" << inp << '\"';
            else
                throw std::runtime_error("Error in exec(): Bad input. String only.");
        }
    }

    // Executes the input by creating the temp file, parsing the input into it and finally compiling it.
    template<typename... Libraries>
    inline void exec(const std::string& inp, const Libraries&... libs)
    {
        std::ofstream source("temp.cpp");
        source << "#include <iostream>";

        Capsule::handle_libs(source, libs...);

        std::string code = "\nint main() { " + inp + " }";
        source << code;
        source.close();
        if (std::filesystem::path("/").preferred_separator == '/')
            std::system("g++ temp.cpp -o temp && ./temp");
        else
            std::system("g++ temp.cpp -o temp && temp");
    }

    // Executes the input by creating the temp file, parsing the input into it and finally compiling it.
    inline void exec(const std::string& inp)
    {
        std::ofstream source("temp.cpp");
        source << "#include <iostream>";
        std::string code = "\nint main() { " + inp + " }";
        source << code;
        source.close();
        std::system("g++ temp.cpp -o temp && temp");
    }
}

#endif