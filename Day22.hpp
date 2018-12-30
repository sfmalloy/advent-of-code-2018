#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "Day.hpp"

long geoIndex(int x, int y, const int& depth);

long erosionLevel(long index, const int& depth);

template<>
void Day<22>::solve1(std::ifstream& in, std::ostream& out) {
    std::string ignore, targetString;
    int depth;
    
    in >> ignore >> depth >> ignore >> targetString;

    size_t comma = targetString.find(',');
    std::pair<long, long> target = { std::stoi(targetString.substr(0, comma)), std::stoi(targetString.substr(comma + 1)) };

    std::vector<std::vector<long>> erosions(target.second + 1, std::vector<long>(target.first + 1));
    
    long riskLevel = 0;
    for (unsigned y = 0; y < erosions.size(); ++y) {
        for(unsigned x = 0; x < erosions[y].size(); ++x) {
            if (x == 0 || y == 0 || (x == target.first && y == target.second)) {
                erosions[y][x] = erosionLevel(geoIndex(x, y, depth), depth);
            } else {
                erosions[y][x] = erosionLevel(erosions[y - 1][x] * erosions[y][x - 1], depth);
            }

            riskLevel += erosions[y][x] % 3;
        }
    }

    out << riskLevel << std::endl;
}

template<>
void Day<22>::solve2(std::ifstream& in, std::ostream& out) {
    out << "not finished" << std::endl;
}

long geoIndex(int x, int y, const int& depth) {
    if (x != 0 && y == 0) {
        return x * 16807;
    } else if (x == 0 && y != 0) {
        return y * 48271;
    } else {
        return 0;
    }
}

long erosionLevel(long index, const int& depth) {
    return (index + depth) % 20183;
}