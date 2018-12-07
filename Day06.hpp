#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <map>

#include "Day.hpp"

std::vector<std::pair<int, int>> getCoords(std::ifstream& in);

template<>
void Day<6>::solve1(std::ifstream& in, std::ostream& out) {
    std::vector<std::pair<int, int>> coords = getCoords(in);
    
    int xMax = std::max_element(coords.begin(), coords.end())->first;
    int yMax = std::max_element(coords.begin(), coords.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b)
                                                                { return a.second < b.second; })->second;

    std::vector<std::pair<int, int>> exclusions;

    for (int y = 0; y <= yMax; ++y) {
        for (int x = 0; x <= xMax; ++x) {
            if (y == 0 || y == yMax || x == 0 || x == xMax) {
                int distance = yMax * xMax;
                std::pair<int, int> point;

                for (const auto& c : coords) {
                    int currDistance = std::abs(y - c.second) + std::abs(y - c.first);
                    if (currDistance < distance) {
                        point = c;
                        distance = currDistance;
                    }
                }

                if (std::find(exclusions.begin(), exclusions.end(), point) == exclusions.end()) {
                    bool isUnique = true;
                    for (const auto& c : coords) {
                        int currDistance = std::abs(y - c.second) + std::abs(y - c.first);
                        if (c != point && distance == currDistance) {
                            isUnique = false;
                            break;
                        }
                    }

                    if (isUnique)
                        exclusions.push_back(point);
                }
            }
        }
    }

    out << std::endl;
    for (const auto& c : exclusions) {
        out << c.first << ", " << c.second << std::endl;
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