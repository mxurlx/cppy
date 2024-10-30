#include "cppy.h"

int main()
{
    std::string inp;
    inp = cppy::input(">>> ");
    cppy::exec(inp, "cppy.h");
}