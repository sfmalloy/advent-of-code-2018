#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Day.hpp"

struct Claim {
    int id, left, top, width, height;
};

std::vector<Claim> getClaims(std::ifstream& in);

std::vector<std::vector<int>> proccessClaims(std::vector<Claim> claims);

template<>
void Day<3>::solve1(std::ifstream& in, std::ostream& out) {
    std::vector<Claim> claims = getClaims(in);
    std::vector<std::vector<int>> fabric = proccessClaims(claims);
    
    long overlap = 0;
    
    for (size_t i = 0; i < fabric.size(); ++i) {
        for (size_t j = 0; j < fabric[i].size(); ++j) {
            if (fabric[i][j] > 1)
                ++overlap;
        }
    }

    out << overlap << std::endl;
}

template<>
void Day<3>::solve2(std::ifstream& in, std::ostream& out) {
    std::vector<Claim> claims = getClaims(in);
    std::vector<std::vector<int>> fabric = proccessClaims(claims);

    Claim best = claims[0];

    for (Claim c : claims) {
        bool intact = true;
        for (int i = 0; i < c.width; ++i) {
            for (int j = 0; j < c.height; ++j) {
                if (fabric[c.left + i][c.top + j] > 1) {
                    intact = false;
                    break;
                }
            }
            if (!intact)
                break;
        }

        if (intact) {
            best = c;
            break;
        }
    }

    out << best.id << std::endl;
}

std::vector<Claim> getClaims(std::ifstream& in) {
    std::string claimNum, at, leftTop, widthHeight;
    std::vector<Claim> claims;

    while (in >> claimNum >> at >> leftTop >> widthHeight) {
        leftTop.pop_back();

        Claim c;
        c.id = std::stoi(claimNum.substr(1));
        c.left = std::stoi(leftTop.substr(0, leftTop.find(",")));
        c.top = std::stoi(leftTop.substr(leftTop.find(",") + 1));
        c.width = std::stoi(widthHeight.substr(0, widthHeight.find("x")));
        c.height = std::stoi(widthHeight.substr(widthHeight.find("x") + 1));

        claims.push_back(c);
    }
    
    return claims;
}

std::vector<std::vector<int>> proccessClaims(std::vector<Claim> claims) {
    std::vector<std::vector<int>> fabric(1000, std::vector<int> (1000, 0));

    for (Claim c : claims) {
        for (int i = 0; i < c.width; ++i) {
            for (int j = 0; j < c.height; ++j) {
                ++fabric[c.left + i][c.top + j];
            }
        }
    }

    return fabric;
}
