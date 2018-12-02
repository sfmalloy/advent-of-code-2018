#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

void solve(std::ifstream& in, std::ostream& out) {
    std::string line;

    int twoCount = 0, threeCount = 0;

    while (in >> line) {
        std::unordered_map<char, int> letters;
        for (const char& c : line)
            ++letters[c];

        bool foundTwo = false, foundThree = false;
        
        for (const std::pair<char, int>& pair : letters) {
            if (pair.second == 2 && !foundTwo) {
                ++twoCount;
                foundTwo = true;
            } else if (pair.second == 3 && !foundThree) {
                ++threeCount;
                foundThree = true;
            }
            
            if (foundTwo && foundThree)
                break;
        }
    }

    out << twoCount * threeCount << std::endl;
    
}

void solve2(std::ifstream& in, std::ostream& out) {
    std::string line;

    std::vector<std::string> boxes;

    while (in >> line) {
        boxes.push_back(line);
    }

    size_t i = 0, boxSize = boxes[0].size();

    std::string a, b;

    for (const std::string& box : boxes) {
        for (size_t j = i; j < boxes.size(); ++j) {
            size_t diff = boxSize;
            std::string tempBox = boxes[j];
            for (size_t k = 0; k < boxSize; ++k) {
                if (box[k] == tempBox[k])
                    --diff;
            }

            if (diff == 1) {
                a = box;
                b = tempBox;
                break;
            }
        }
    }

    size_t n = 0;
    for (; a[n] == b[n] && n < boxSize; ++n) { }

    a = a.substr(0, n) + a.substr(n + 1);

    out << a << std::endl;
}
