#include <iostream>
#include <fstream>
#include <array>
#include <tuple>

#include "Day.hpp"

int getPowerLevel(const int& x, const int& y, const int& serial);

std::array<std::array<int, 300>, 300> powerGrid(const int& serial);

template<>
void Day<11>::solve1(std::ifstream& in, std::ostream& out) {
    int serial;
    in >> serial;

    std::array<std::array<int, 300>, 300> grid = powerGrid(serial);

    int maxArea = 0;
    std::pair<int, int> coord;
    for (int y = 0; y < 298; ++y) {
        for (int x = 0; x < 298; ++x) {
            int area = 0;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    area += grid[y + i][x + j];
                }
            }

            if (maxArea < area) {
                maxArea = area;
                coord = { x + 1, y + 1 };
            }
        }
    }

    out << coord.first << "," << coord.second << std::endl;
}

template<>
void Day<11>::solve2(std::ifstream& in, std::ostream& out) {
    int serial;
    in >> serial;

    std::array<std::array<int, 300>, 300> grid = powerGrid(serial);

    int maxArea = 0, maxSize = 0;
    std::pair<int, int> coord;

    for (int s = 1; s <= 300; ++s) {
        for (int y = 0; y < 300 - s; ++y) {
            for (int x = 0; x < 300 - s; ++x) {
                int area = 0;
                for (int i = 0; i < s; ++i) {
                    for (int j = 0; j < s; ++j) {
                        area += grid[y + i][x + j];
                    }
                }

                if (maxArea < area) {
                    maxArea = area;
                    coord = { x + 1, y + 1 };
                    maxSize = s;
                }
            }
        }
    }

    out << coord.first << "," << coord.second << "," << maxSize << std::endl;
}

int getPowerLevel(const int& x, const int& y, const int& serial) {
    int rackID = x + 10;
    int power = rackID * y + serial;
    power = power * rackID;
    power /= 100;
    power = power % 10;
    power -= 5;

    return power;
}

std::array<std::array<int, 300>, 300> powerGrid(const int& serial) {
    std::array<std::array<int, 300>, 300> grid;

    for (int y = 1; y <= 300; ++y) {
        for (int x = 1; x <= 300; ++x) {
            grid[y - 1][x - 1] = getPowerLevel(x, y, serial);
        }
    }

    return grid;
}