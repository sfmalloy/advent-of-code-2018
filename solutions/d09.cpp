#include <iostream>

#include "solution.hpp"
#include "utils.hpp"

struct marble
{
    marble(u32 value)
        : prev(this)
        , next(this)
        , val(value)
    { }

    marble* prev;
    marble* next;
    u32 val;
};

class circle
{
public:
    circle()
        : m_curr(new marble(0))
        , m_size(1)
    { }
    
    u32 
    place(u32 val)
    {
        u32 score = 0;
        if (val % 23 != 0)
        {
            auto a = m_curr->next;
            auto b = a->next;
            a->next = new marble(val);
            b->prev = a->next;
            a->next->prev = a;
            a->next->next = b;

            m_curr = a->next;
            ++m_size;
        }
        else
        {
            score += val;
            for (u32 i = 0; i < 7; ++i)
                m_curr = m_curr->prev;
            score += m_curr->val;

            auto old = m_curr;
            old->prev->next = old->next;
            old->next->prev = old->prev;
            m_curr = old->next;

            delete old;
            --m_size;
        }

        return score;
    }

    marble*
    curr()
    {
        return m_curr;
    }

    ~circle()
    {
        for (u64 i = 0; i < m_size; ++i)
        {
            auto next = m_curr->next;
            m_curr->next = nullptr;
            m_curr->prev = nullptr;
            delete m_curr;
            m_curr = next;
        }
    }

    u64
    size()
    {
        return m_size;
    }
private:
    marble* m_curr;
    u64 m_size;
};

u32
play(u32 player_count, u32 max_points)
{
    u32* players = new u32[player_count]();
    circle c;
    u32 curr_player = 0;
    u32 max = 0;
    for (u32 i = 1; i <= max_points; ++i)
    {
        players[curr_player] += c.place(i);
        max = players[curr_player] > max ? players[curr_player] : max;
        ++curr_player;
        if (curr_player == player_count)
            curr_player = 0;
    }

    delete[] players;
    return max;
}

template<>
void
solution<9>::solve(std::ifstream& input)
{
    auto [player_str, points_str] = fixed_split<2>(readline(input), "; ");
    u32 player_count = convert<u32>(split(player_str, " ")[0]);
    u32 max_points = convert<u32>(split(points_str, " ")[4]);
    std::cout << play(player_count, max_points) << '\n';
    std::cout << play(player_count, max_points * 100) << '\n';
}
