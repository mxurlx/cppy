#ifndef CPPY_ZIP_H
#define CPPY_ZIP_H

#include <vector>
#include <tuple>

namespace cppy
{
    // Returns a vector of tuples, where the first element in each passed container is paired together, same goes for the second element and so on.
    template<typename... Args>
    inline auto zip(const Args&... args)
    {
        std::size_t minsize = std::min({args.size()...});
        std::vector<std::tuple<typename Args::value_type...>> res;
        
        for (size_t it = 0; it < minsize; it++)
            res.emplace_back(std::make_tuple(args[it]...));
        
        return res;
    }
}

#endif