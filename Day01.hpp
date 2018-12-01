#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

static void solve(std::ifstream& in, std::ostream& out) {
    int frequency = 0;
    std::string change;

    while (in >> change) {
        int changeNum = std::stoi(change.substr(1));
        if(change[0] == '+')
            frequency += changeNum;
        else
            frequency -= changeNum;
    }

    out << frequency << std::endl;
}

static void solve2(std::ifstream& in, std::ostream& out) {
    int frequency = 0;
    std::string change;

    std::vector<int> values;

    while (in >> change) {
        int changeNum = std::stoi(change.substr(1));
        if(change[0] == '+')
            values.push_back(changeNum);
        else
            values.push_back(-changeNum);
    }

    std::set<int> found;
    bool foundF = true;

    for (size_t i = 0; foundF; ++i) {
        frequency += values[i];
        foundF = found.insert(frequency).second;

        if (i == values.size() - 1)
            i = -1;
    }

    out << frequency << std::endl;
}
