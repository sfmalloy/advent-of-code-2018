#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <unordered_map>

#include "Day.hpp"

std::vector<std::pair<int, int>> getCoords(std::ifstream& in);

template<>
void Day<6>::solve1(std::ifstream& in, std::ostream& out) {
    std::vector<std::pair<int, int>> coords = getCoords(in);
    std::sort(coords.begin(), coords.end());
    int xMax = coords[coords.size() - 1].first;
    int yMax = std::max_element(coords.begin(), coords.end(), [](const std::pair<int,int>& a, const std::pair<int,int>& b) 
                                                                { return a.second < b.second; })->second;


    std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>> coordMap;

    for (size_t i = 0; i < yMax + 1; ++i) {
        for (size_t j = 0; j < xMax; ++j) {
            std::pair<int, int> currCord;

            for (auto p : coords) {

            }
        }
    }
}

template<>
void Day<6>::solve2(std::ifstream& in, std::ostream& out) {
    
}

std::vector<std::pair<int, int>> getCoords(std::ifstream& in) {
    std::vector<std::pair<int, int>> coords;
    std::string x, y;

    while (in >> x >> y) {
        std::pair<int, int> p = {std::stoi(x.substr(0, x.size() - 1)), std::stoi(y)};
        coords.push_back(p);
    }

    return coords;
}