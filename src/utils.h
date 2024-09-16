#ifndef UTILS_H
#define UTILS_H

#include <iostream>

inline std::pair<int, int> indexToRowCol(int index)
{
    int row = index / 8;
    int col = index % 8;
    return {row, col};
}

#endif // UTILS_H
