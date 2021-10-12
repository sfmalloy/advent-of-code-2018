#include <iostream>
#include <unordered_map>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

class timestamp
{
public:
    timestamp(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 id, bool is_awake)
        : m_year(year),
          m_month(month),
          m_day(day),
          m_hour(hour),
          m_minute(minute),
          m_id(id),
          m_is_awake(is_awake)
    {
        m_encoding = ((u64) m_year << 35) + ((u64) m_month << 21) + ((u64) m_day << 16) + ((u64) m_hour << 11) + ((u64) m_minute << 6);
    }

    bool
    operator<(const timestamp& other)
    {
        return m_encoding < other.m_encoding;
    }

    bool
    operator==(const timestamp& other)
    {
        return m_encoding == other.m_encoding;
    }

    std::string
    to_string() const
    {
        return std::to_string(m_id) + " => "
            + std::to_string(m_year) + "/"
            + std::to_string(m_month) + "/"
            + std::to_string(m_day) + " "
            + std::to_string(m_hour) + ":"
            + std::to_string(m_minute);
    }

    u32
    id()
    {
        return m_id;
    }

    void
    set_id(u32 id)
    {
        m_id = id;
    }

    bool
    is_awake()
    {
        return m_is_awake;
    }

    u32
    minute()
    {
        return m_minute;
    }

    u32
    hour()
    {
        return m_hour;
    }

private:
    u32 m_year;
    u32 m_month;
    u32 m_day;
    u32 m_hour;
    u32 m_minute;
    u32 m_id;
    bool m_is_awake;
    u64 m_encoding;
};

template <>
void
solution<4>::solve(std::ifstream& input)
{
    // std::unordered_map<u32, std::vector<timestamp>> guard_states;
    std::vector<timestamp> state_list;

    std::string line;
    while (std::getline(input, line))
    {
        auto [time_str, status] = fixed_split<2>(line, "] ");
        auto [date, time] = fixed_split<2>(time_str.substr(1), " ");
        auto [year, month, day] = type_split<u32, 3>(date, "-");
        auto [hour, minute] = type_split<u32, 2>(time, ":");

        u32 id = 0;
        if (status[0] == 'G')
        {
            size_t num_idx = status.find('#') + 1;
            size_t space_idx = status.find(' ', num_idx);
            id = std::stoul(status.substr(num_idx, space_idx - num_idx));
        }

        state_list.emplace_back(year, month, day, hour, minute, id, status[0] == 'w');
    }

    std::sort(std::begin(state_list), std::end(state_list));

    std::unordered_map<u32, u32> sleep_times;

    for (u32 i = 0; i < state_list.size(); ++i)
    {
        if (i > 0 && state_list[i].id() == 0)
            state_list[i].set_id(state_list[i - 1].id());

        if (!state_list[i].is_awake())
            sleep_times[state_list[i].id()] += state_list[i].minute();
    }

    u32 max = std::max_element(std::begin(sleep_times), std::end(sleep_times), [] (const auto& p1, const auto& p2) {
        return p1.second < p2.second;
    })->second;

    std::cout << max << '\n';
}