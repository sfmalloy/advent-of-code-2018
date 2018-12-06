#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <array>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <functional>
#include <tuple>
#include <numeric>

#include "Day.hpp"

struct TimeStamp {
    int month, day, hour, minute;
    std::string status;
};

std::vector<TimeStamp> getTimeStamps(std::ifstream& in);

void sortStamps(std::vector<TimeStamp>& stamps);

std::unordered_map<int, std::vector<std::pair<int, int>>> mapStamps(const std::vector<TimeStamp>& stamps);

template<>
void Day<4>::solve1(std::ifstream& in, std::ostream& out) {
    std::vector<TimeStamp> stamps = getTimeStamps(in);
    std::unordered_map<int, std::vector<std::pair<int, int>>> idToSleep = mapStamps(stamps);

    // Find ID with most sleep time
    int idMax = 0, maxTimeSum = 0;
    for (const auto& i : idToSleep) {
        int currTimeSum = std::accumulate(i.second.begin(), i.second.end(), 0, [](const int& currSum, const std::pair<int, int>& p){ return currSum + p.second - p.first; });

        if (maxTimeSum < currTimeSum) {
            idMax = i.first;
            maxTimeSum = currTimeSum;
        }
    }

    // Go through time vector and get minute most sleeped on.
    // Decided to brute force it since there are only 60 minutes in an hour...
    auto bestVector = idToSleep[idMax];
    std::pair<int, int> maxFrequency = { 0, 0 };

    for (int i = 0; i < 60; ++i) {
        std::pair<int, int> currFrequency = { i, 0 };
        for (auto p : bestVector) {
            if (i >= p.first && i < p.second)
                ++currFrequency.second;
        }

        if (maxFrequency.second < currFrequency.second)
            maxFrequency = currFrequency;
    }

    out << idMax * maxFrequency.first << std::endl;
}

template<>
void Day<4>::solve2(std::ifstream& in, std::ostream& out) {
    std::vector<TimeStamp> stamps = getTimeStamps(in);
    std::unordered_map<int, std::vector<std::pair<int, int>>> idToSleep = mapStamps(stamps);

    std::pair<int, int> maxFrequency = { 0, 0 };
    int idMax = 0;
    
    // Taken from solve1 and just iterating over all ids rather than just one.
    for (auto i : idToSleep) {
        auto currVector = i.second;

        for (int k = 0; k < 60; ++k) {
            std::pair<int, int> currFrequency = { k, 0 };
            for (auto p : currVector) {
                if (k >= p.first && k < p.second)
                    ++currFrequency.second;
            }

            if (maxFrequency.second < currFrequency.second) {
                maxFrequency = currFrequency;
                idMax = i.first;
            }
        }
    }

    out << idMax * maxFrequency.first << std::endl;
}

// Extracts time stamps from input and calls sort on them
// then returns time stamps sorted
std::vector<TimeStamp> getTimeStamps(std::ifstream& in) {
    std::string stampDate, stampTime, status;
    std::vector<TimeStamp> stamps;

    while (in >> stampDate >> stampTime && std::getline(in, status)) {
        int month = std::stoi(stampDate.substr(6, 8));
        int day = std::stoi(stampDate.substr(9, 11));
        int hour = std::stoi(stampTime.substr(0, 2));
        int minute = std::stoi(stampTime.substr(3, 5));

        stamps.push_back({month, day, hour, minute, status.substr(1)});
    }

    sortStamps(stamps);

    return stamps;
}

void sortStamps(std::vector<TimeStamp>& stamps) {
    std::array<std::queue<TimeStamp>, 10> digits;

    // Radix sort
    for (size_t i = 0; i < 8; ++i) {
        for (TimeStamp& s : stamps) {
            int key;
            if (i <= 1)
                key = s.minute;
            else if (i <= 3)
                key = s.hour;
            else if (i <= 5)
                key = s.day;
            else
                key = s.month;

            if (i % 2 == 0)
                key %= 10;
            else
                key /= 10;

            digits[key].push(s);
        }

        size_t index = 0;
        for (std::queue<TimeStamp>& q : digits) {
            while (!q.empty()) {
                stamps[index] = q.front();
                q.pop();
                ++index;
            }
        }
    }
}

std::unordered_map<int, std::vector<std::pair<int, int>>> mapStamps(const std::vector<TimeStamp>& stamps) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> idToSleep;
    
    int id, startSleep = 0;
    for (const TimeStamp& s : stamps) {
        if (s.status.find('G') != std::string::npos) {
            size_t start = s.status.find("#");
            id = std::stoi(s.status.substr(start + 1, s.status.substr(start).find(' ')));
        } else if (s.status == "falls asleep") {
            startSleep = s.minute;
        } else {
            idToSleep[id].push_back({startSleep, s.minute});
        }
    }

    return idToSleep;
}