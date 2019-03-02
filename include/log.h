#pragma once

#include <iostream>
#include <utility>

void log() {}

template <typename First, typename ...Rest>
void log(First &&first, Rest && ...rest)
{
    std::cout << std::forward<First>(first);
    log(std::forward<Rest>(rest)...);
}

};
