#ifndef __UTIL__
#define __UTIL__

#include <iostream>
#include <vector>

template<class T>
static inline void OutputVec(const std::vector<T> &vec) {
    for (const auto &v : vec) {
        std::cout << v  << " ";
    }
    std::cout << std::endl;
}

#endif
