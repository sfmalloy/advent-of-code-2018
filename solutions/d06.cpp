#include <iostream>
#include <vector>
#include <map>
#include <tuple>

#include "solution.hpp"

std::vector<std::pair<int, int>> getCoords(std::ifstream& in);

template<>
void
solution<6>::solve(std::ifstream& input)
{
    std::vector<std::pair<int, int>> coords;
    std::string x, y;

    while (input >> x >> y) {
        std::pair<int, int> p = {std::stoi(x.substr(0, x.size() - 1)), std::stoi(y)};
        coords.push_back(p);
    }

    int xMax = std::max_element(coords.begin(), coords.end())->first;
    int yMax = std::max_element(coords.begin(), coords.end(), [](const auto& p1, const auto& p2) { return p1.second < p2.second; })->second;
    std::vector<std::pair<int, int>> exclusions;

    for (int y = 0; y <= yMax; ++y) {
        for (int x = 0; x <= xMax + 1; ++x) {
            if (x == 0 || x == xMax || y == 0 || y == yMax) {
                int distance = yMax * xMax;
                std::pair<int, int> currPair;
                for (const auto& c : coords) {
                    int currDistance = std::abs(c.second - y) + std::abs(c.first - x);

                    if (currDistance < distance) {
                        distance = currDistance;
                        currPair = c;
                    }
                }

                if (std::find(exclusions.begin(), exclusions.end(), currPair) == exclusions.end()) {
                    exclusions.push_back(currPair);
                }
            }
        }
    }

    std::map<std::pair<int, int>, int> areas;

    for (int y = 0; y <= yMax; ++y) {
        for (int x = 0; x <= xMax; ++x) {
            int distance = yMax * xMax;
            std::pair<int, int> currPair;
            std::map<int, int> distCount;

            for (const auto& c : coords) {
                int currDistance = std::abs(c.second - y) + std::abs(c.first - x);

                ++distCount[currDistance];
                if (currDistance < distance) {
                    distance = currDistance;
                    currPair = c;
                }
            }

            if (distCount[distance] == 1) {
                if (std::find(exclusions.begin(), exclusions.end(), currPair) == exclusions.end()) {
                    ++areas[currPair];
                }
            }
        }
    }

    int maxArea = 0;
    for (const auto& p : areas) {
        if (maxArea < p.second) {
            maxArea = p.second;
        }
    }

    std::cout << maxArea << std::endl;


    int upper = 10000, area = 0;

    for (int y = 0; y <= yMax; ++y) {
        for (int x = 0; x <= xMax; ++x) {
            int distance = 0;
            for (const auto& c : coords) {
                distance += std::abs(c.second - y) + std::abs(c.first - x);
            }

            if (distance < upper)
                ++area;
        }
    }

    std::cout << area << '\n';
}
