#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <cctype>
#include <algorithm>
#include <tuple>

#include "Day.hpp"

bool checkCase(const char& c1, const char& c2);

size_t react(std::string input);

std::string removeLetter(std::string input, const char& sub);

template<>
void Day<5>::solve1(std::ifstream& in, std::ostream& out) {
    std::string input;
    in >> input;

    out << react(input) << std::endl;
}

template<>
void Day<5>::solve2(std::ifstream& in, std::ostream& out) {
    std::string input;
    in >> input;

    size_t smallestSize = input.size();
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (const char& l : alphabet) {
        size_t currReact = react(removeLetter(input, l));

        if (currReact < smallestSize)
            smallestSize = currReact;
    }

    out << smallestSize << std::endl;
}

bool checkCase(const char& c1, const char& c2) {
    return (std::islower(c1) && std::isupper(c2)) || (std::islower(c2) && std::isupper(c1));
}

size_t react(std::string input) {
    bool hasRemoved = true;
    
    while (input.size() > 0 && hasRemoved) {
        hasRemoved = false;

        std::string tempInput;
        for (size_t i = 0; i < input.size(); ++i) {
            if (i < input.size() - 1 && std::tolower(input[i]) == std::tolower(input[i + 1]) && checkCase(input[i], input[i + 1])) {
                hasRemoved = true;
                ++i;
            } else {
                tempInput.push_back(input[i]);
            }
        }

        input = tempInput;
    }

    return input.size();
}

std::string removeLetter(std::string input, const char& sub) {
    std::string newInput;
    
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] != sub && input[i] != std::toupper(sub))
            newInput.push_back(input[i]);
    }

    return newInput;
}