#include <iostream>
#include <string>

#include "solution.hpp"
#include <unordered_map>

bool open_to_tree(i32 r, i32 c, char* landscape);
bool tree_to_lumberyard(i32 r, i32 c, char* landscape);
bool lumberyard_to_open(i32 r, i32 c, char* landscape);
char at(i32 r, i32 c, char* landscape);
void print_grid(char* landscape);
i32 transform_lanscape(char* landscape, u32 minutes);

const constexpr i32 L = 50;

template <>
void
solution<18>::solve(std::ifstream& input)
{
    char landscape1[L * L];
    char landscape2[L * L];
    std::string line;
    for (i32 r = 0; std::getline(input, line); ++r) {
        for (i32 c = 0; c < line.length(); ++c) {
            landscape1[r*L + c] = line[c];
            landscape2[r*L + c] = line[c];
        }
    }

    std::cout << transform_lanscape(landscape1, 10) << '\n';
    std::cout << transform_lanscape(landscape2, 1000000000) << '\n';
}

i32 transform_lanscape(char* landscape, u32 T) {
    std::unordered_map<std::string, u32> seen;
    for (u32 minute = 0; minute < T; ++minute) {
        char transformed[L * L];
        for (i32 r = 0; r < L; ++r) {
            for (i32 c = 0; c < L; ++c) {
                if (open_to_tree(r, c, landscape)) {
                    transformed[r*L + c] = '|';
                } else if (tree_to_lumberyard(r, c, landscape)) {
                    transformed[r*L + c] = '#';
                } else if (lumberyard_to_open(r, c, landscape)) {
                    transformed[r*L + c] = '.';
                } else {
                    transformed[r*L + c] = landscape[r*L + c];
                }
            }
        }

        for (i32 i = 0; i < L * L; ++i) {
            landscape[i] = transformed[i];
        }
        auto key = std::string{landscape};
        if (!seen.contains(key)) {
            seen[key] = minute;
        } else {
            u32 cycle_len = minute - seen[key];
            return transform_lanscape(landscape, ((T - minute) % cycle_len) - 1);
        }
    }

    i32 lumberyards = 0;
    i32 trees = 0;
    for (i32 r = 0; r < L; ++r) {
        for (i32 c = 0; c < L; ++c) {
            lumberyards += landscape[r*L + c] == '#';
            trees += landscape[r*L + c] == '|';
        }
    }

    return lumberyards * trees;
}

bool open_to_tree(i32 r, i32 c, char* landscape) {
    if (at(r, c, landscape) != '.') {
        return false;
    }
    i32 count = 0;
    for (i32 rr = r - 1; rr <= r + 1; ++rr) {
        for (i32 cc = c - 1; cc <= c + 1; ++cc) {
            if (rr == r and cc == c) {
                continue;
            }
            count += at(rr, cc, landscape) == '|';
        }
    }

    return count >= 3;
}

bool tree_to_lumberyard(i32 r, i32 c, char* landscape) {
    if (at(r, c, landscape) != '|') {
        return false;
    }
    i32 count = 0;
    for (i32 rr = r - 1; rr <= r + 1; ++rr) {
        for (i32 cc = c - 1; cc <= c + 1; ++cc) {
            if (rr == r and cc == c) {
                continue;
            }
            count += at(rr, cc, landscape) == '#';
        }
    }

    return count >= 3;
}

bool lumberyard_to_open(i32 r, i32 c, char* landscape) {
    if (at(r, c, landscape) != '#') {
        return false;
    }
    bool found_tree = false;
    bool found_lumberyard = false;
    for (i32 rr = r - 1; rr <= r + 1; ++rr) {
        for (i32 cc = c - 1; cc <= c + 1; ++cc) {
            if (rr == r and cc == c) {
                continue;
            }
            char neighbor = at(rr, cc, landscape);
            if (neighbor == '#') {
                found_tree = true;
            } else if (neighbor == '|') {
                found_lumberyard = true;
            }
        }
    }

    return not (found_tree and found_lumberyard);
}

char at(i32 r, i32 c, char* landscape) {
    if (r < L and r >= 0 and c < L and c >= 0) {
        return landscape[r*L + c];
    }
    return 0;
}

void print_grid(char* landscape) {
    for (i32 r = 0; r < L; ++r) {
        for (i32 c = 0; c < L; ++c) {
            std::cout << landscape[r*L + c];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
