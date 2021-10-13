#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>
#include <tuple>

#include "solution.hpp"
#include "utils.hpp"

class timestamp
{
public:
    timestamp(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 id, bool is_awake, const std::string& state)
        : m_year(year),
          m_month(month),
          m_day(day),
          m_hour(hour),
          m_minute(minute),
          m_id(id),
          m_is_awake(is_awake),
          m_state(state)
    {
        m_encoding = ((u64) m_year << 35)
            + ((u64) m_month << 21)
            + ((u64) m_day << 16)
            + ((u64) m_hour << 11)
            + ((u64) m_minute << 6);
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
        return std::to_string(m_id)    + " => "
            + std::to_string(m_year)   + "/"
            + std::to_string(m_month)  + "/"
            + std::to_string(m_day)    + " "
            + std::to_string(m_hour)   + ":"
            + std::to_string(m_minute) + " => "
            + m_state;
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

    std::string m_state;
};

std::ostream&
operator<<(std::ostream& out, const timestamp& t)
{
    out << t.to_string();
    return out;
}

template <>
void
solution<4>::solve(std::ifstream& input)
{
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

        state_list.emplace_back(year, month, day, hour, minute, id, status[0] == 'w', status);
    }

    std::sort(std::begin(state_list), std::end(state_list));
    std::unordered_map<u32, std::array<u32, 60>> minutes_asleep;

    for (u32 i = 0; i < state_list.size(); ++i)
    {
        if (i > 0 && state_list[i].id() == 0)
        {
            u32 id = state_list[i - 1].id();
            state_list[i].set_id(id);
            if (!state_list[i].is_awake())
                for (u32 m = state_list[i].minute(); m < state_list[i + 1].minute(); ++m)
                    ++minutes_asleep[id][m];
        }
    }

    std::pair<u32, u32> max_asleep = std::make_pair(0, 0);
    for (const auto& [id, minutes] : minutes_asleep)
    {
        u32 total = std::accumulate(std::begin(minutes), std::end(minutes), 0);

        if (total > max_asleep.second)
            max_asleep = std::make_pair(id, total);
    }

    std::pair<u32, u32> max_minute = std::make_pair(0, 0);
    for (u32 m = 0; m < 60; ++m)
    {
        u32 curr_minute_slept = minutes_asleep[max_asleep.first][m];
        if (curr_minute_slept > max_minute.second)
            max_minute = std::make_pair(m, curr_minute_slept);
    }

    std::cout << max_asleep.first * max_minute.first << '\n';

    std::tuple<u32, u32, u32> frequent_minute = std::make_tuple<u32, u32, u32>(0, 0, 0);
    for (const auto& [id, minutes] : minutes_asleep)
        for (u32 m = 0; m < 60; ++m)
            if (minutes[m] > std::get<2>(frequent_minute))
                frequent_minute = std::make_tuple<u32, u32, u32>((u32) id, (u32) m, (u32) minutes[m]);

    std::cout << std::get<0>(frequent_minute) * std::get<1>(frequent_minute) << '\n';
}
