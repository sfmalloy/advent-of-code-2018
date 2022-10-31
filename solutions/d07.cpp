#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <deque>

#include "solution.hpp"
#include "utils.hpp"

using path_map = std::unordered_map<char, std::unordered_set<char>>;

struct worker
{
    int time;
    char step;

    worker(int t=0, char s=0)
        : time(t),
          step(s)
    { }
};

std::string
get_order(const path_map& src_to_dst, path_map dst_to_src)
{
    std::deque<char> todo;
    for (const auto& pair : src_to_dst) 
    {
        if (!dst_to_src.contains(pair.first))
            todo.push_back(pair.first);
    }

    std::string order = "";
    while (todo.size() > 0)
    {
        std::sort(std::begin(todo), std::end(todo));
        for (auto it = std::begin(dst_to_src); it != std::end(dst_to_src); ++it)
        {
            if (it->second.size() > 0)
            {
                auto pos = it->second.find(todo.front());
                if (pos != nullptr)
                    it->second.erase(pos);
                if (it->second.size() == 0)
                    todo.push_back(it->first);
            }
        }
        order += todo.front();
        todo.pop_front();
    }

    return order;
}

template<>
void
solution<7>::solve(std::ifstream& input)
{
    path_map prereqs;
    path_map sources;
    std::string line;
    while (std::getline(input, line)) 
    {
        auto split_line = split(line, " ");
        prereqs[split_line[1][0]].insert(split_line[7][0]);
        sources[split_line[7][0]].insert(split_line[1][0]);
    }

    std::string order = get_order(prereqs, sources);
    std::cout << order << '\n';

    u32 total = 0;
    constexpr const u32 num_workers = 5;
    worker* workers = new worker[num_workers];
    bool working = true;
    std::unordered_set<char> done;
    while (working)
    {
        working = false;
        for (int i = 0; i < num_workers; ++i)
        {
            if (workers[i].step == 0)
            {
                for (char c : order)
                {
                    if (!done.contains(c) && (!sources.contains(c) || sources.at(c).size() == 0))
                    {
                        workers[i] = { 60 + c - 'A' + 1, c };
                        done.insert(c);
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < num_workers; ++i)
        {
            if (workers[i].time > 0)
            {
                working = true;
                --workers[i].time;
            }
            
            if (workers[i].step != 0 && workers[i].time == 0)
            {
                for (auto src = std::begin(sources); src != std::end(sources); ++src)
                {
                    auto pos = src->second.find(workers[i].step);
                    if (pos != nullptr)
                    {
                        working = true;
                        src->second.erase(pos);
                    }
                }
                workers[i].step = 0;
            }
        }
        ++total;
    }

    delete[] workers;
    std::cout << total - 1 << '\n';
}
