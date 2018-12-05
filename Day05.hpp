#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <cctype>
#include <algorithm>
#include <tuple>

#include "Day.hpp"

bool checkCase(const char& c1, const char& c2);

size_t react(std::string& input);

void reactSingle(std::string& input, const char& sub);

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

    std::pair<char, size_t> maxLetter = { ' ', 0 };
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    for (size_t i = 0; i < 26; ++i) {
        size_t tempCount = 0;

        for (size_t j = 0; j < input.size(); ++j) {
            if (alphabet[i] == std::tolower(input[j]))
                ++tempCount;
        }

        if (tempCount > maxLetter.second)
            maxLetter = { alphabet[i], tempCount };
    }

    reactSingle(input, maxLetter.first);
    react(input);
    out << input << std::endl;
}

bool checkCase(const char& c1, const char& c2) {
    return (((std::islower(c1) && std::isupper(c2)) || (std::islower(c2) && std::isupper(c1))) && std::tolower(c1) == std::tolower(c2));
}

size_t react(std::string& input) {
    bool hasRemoved = true;
    
    while (input.size() > 0 && hasRemoved) {
        hasRemoved = false;
        std::vector<bool> destroyed(input.size(), false);

        for (size_t i = 0; i < input.size() - 1; ++i) {
            if (checkCase(input[i], input[i + 1])) {
                destroyed[i] = true;
                destroyed[i + 1] = true;
                hasRemoved = true;
                ++i;
            }
        }

        std::string tempInput;

        for (size_t i = 0; i < input.size(); ++i) {
            if (!destroyed[i])
                tempInput.push_back(input[i]);
        }

        input = tempInput;
    }

    return input.size();
}

void reactSingle(std::string& input, const char& sub) {
    std::string tempInput;

    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] != sub && input[i] != std::toupper(sub)) {
            tempInput.push_back(input[i]);
        }
    }

    input = tempInput;
}