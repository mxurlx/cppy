#ifndef CPPY_MEMORYVIEW_H
#define CPPY_MEMORYVIEW_H

namespace cppy
{
    // Returns the memory address of the input.
    template<typename T>
    inline T* memoryview(T& inp)
    {
        return &inp;    // I dont think that something can be added here
    }
}

#endif