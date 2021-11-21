#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

void
get_path(char curr, const std::unordered_map<char, std::vector<char>>& connections, std::unordered_map<char, bool>& is_done, std::string& path) 
{
    if (is_done.at(curr) && path.find(curr) == std::string::npos)
    {
        path += curr;
        is_done[curr] = false;
        return;
    }

    if (connections.find(curr) != std::end(connections) && !is_done.at(curr))
    {
        for (char c : connections.at(curr)) 
        {
            get_path(c, connections, is_done, path);
        }
        is_done[curr] = true;
        path += curr;
    }
}

template <>
void
solution<7>::solve(std::ifstream& input)
{
    std::unordered_map<char, bool> is_done;
    std::unordered_map<char, std::vector<char>> connections;
    std::unordered_set<char> unique_values;

    std::string line;
    while (std::getline(input, line))
    {
        std::vector<std::string> split_line = split(line, " ");
        char key = split_line[7][0];
        char value = split_line[1][0];
        connections[key].push_back(value);
        
        if (is_done.find(value) == std::end(is_done))
            is_done[value] = true;
        is_done[key] = false;

        unique_values.insert(value);
    }

    char start = 0;
    for (auto& [key, values] : connections)
    {
        std::sort(std::begin(values), std::end(values));
        if (start == 0 && unique_values.find(key) == std::end(unique_values)) 
            start = key;

        std::cout << key << " => ";
        for (char c : values) {
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }

    std::string path;
    get_path(start, connections, is_done, path);
    std::cout << path << '\n';
}
/*

is_done = [
    'A': true
    'B': true
    'C': true
    'D': false
    'E': false
    'F': false
]

A -> [ C ]
F -> [ C ]
B -> [ A ]
D -> [ A ]
E -> [ B D F ]

path => CABDFE

*/