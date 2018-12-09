#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>

#include "Day.hpp"

long getDataSum(std::ifstream& in, const size_t& childCount, const size_t& metaSize);

template<>
void Day<8>::solve1(std::ifstream& in, std::ostream& out) {
    size_t childCount, metaSize;
    in >> childCount >> metaSize;

    out << getDataSum(in, childCount, metaSize) << std::endl;
}

template<>
void Day<8>::solve2(std::ifstream& in, std::ostream& out) {
    
}

long getDataSum(std::ifstream& in, const size_t& childCount, const size_t& metaSize) {
    int sum = 0;
    for (size_t i = 0; i < childCount; ++i) {
        size_t currChildCount, currMetaSize;
        in >> currChildCount >> currMetaSize;
        sum += getDataSum(in, currChildCount, currMetaSize);
    }

    for (size_t k = 0; k < metaSize; ++k) {
        int curr;
        in >> curr;
        sum += curr;
    }

    return sum;
}