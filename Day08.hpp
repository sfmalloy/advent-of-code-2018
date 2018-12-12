#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Day.hpp"

int getDataSum(std::ifstream& in, const size_t& childCount, const size_t& metaSize);

int getRootValue(std::ifstream& in, const size_t& childCount, const size_t& metaSize);

template<>
void Day<8>::solve1(std::ifstream& in, std::ostream& out) {
    size_t childCount, metaSize;
    in >> childCount >> metaSize;

    out << getDataSum(in, childCount, metaSize) << std::endl;
}

template<>
void Day<8>::solve2(std::ifstream& in, std::ostream& out) {
    size_t childCount, metaSize;
    in >> childCount >> metaSize;

    out << getRootValue(in, childCount, metaSize) << std::endl;
}

int getDataSum(std::ifstream& in, const size_t& childCount, const size_t& metaSize) {
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

int getRootValue(std::ifstream& in, const size_t& childCount, const size_t& metaSize) {
    std::vector<int> sums;
    for (size_t i = 0; i < childCount; ++i) {
        size_t currChildCount, currMetaSize;
        in >> currChildCount >> currMetaSize;
        sums.push_back(getRootValue(in, currChildCount, currMetaSize));
    }

    int sum = 0;
    std::vector<int> meta(metaSize);
    
    for (size_t k = 0; k < metaSize; ++k) {
        int curr;
        in >> curr;
        meta.push_back(curr);
    }

    if (childCount == 0) {
        sum = std::accumulate(meta.begin(), meta.end(), 0);
    } else {
        for (const int& m : meta) {
            size_t comp = m - 1;
            if (comp < sums.size()) {
                sum += sums[comp];
            }
        }
    }

    return sum;
}