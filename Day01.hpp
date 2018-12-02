#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

#include "Day.hpp"

template<>
void Day<1>::solve1(std::ifstream& in, std::ostream& out) {
    int frequency = 0;
    std::string change;

    while (in >> change) {
        frequency += std::stoi(change);
    }

    out << frequency << std::endl;
}

template<>
void Day<1>::solve2(std::ifstream& in, std::ostream& out) {
    int frequency = 0;
    std::string change;

    std::vector<int> values;

    while (in >> change) {
        values.push_back(std::stoi(change));
    }

    std::unordered_set<int> found;
    bool foundF = true;

    for (size_t i = 0; foundF; ++i) {
        frequency += values[i];
        foundF = found.insert(frequency).second;
        values.push_back(values[i % values.size()]);
    }

    out << frequency << std::endl;
}
