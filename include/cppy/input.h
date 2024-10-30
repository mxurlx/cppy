#ifndef CPPY_INPUT_H
#define CPPY_INPUT_H

#include <string>
#include <iostream>
#include "contain/is_container.h"

namespace cppy
{
    // Reads the input and converts it into a string.
    inline std::string input(const char* prompt = "")
    {
        std::string inp;
        std::cout << prompt;
        std::getline(std::cin, inp);
        return inp;
    }
}

#endif