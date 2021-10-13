#include <iostream>

#include "solution.hpp"

struct node
{
    char value;
    node* next;
};

/**
 * char_list -> A singley-linked list of chars.
 */
class char_list
{
public:
    char_list(const std::string& chars)
        : m_begin(nullptr),
          m_size(0)
    {
        for (const char c : chars)
            push_front(c);    
    }

    ~char_list()
    {
        while (m_size > 0)
            pop_front();
    }

    void
    push_front(char c)
    {
        node* n = new node{c, m_begin};
        m_begin = n;

        ++m_size;
    }

    void
    remove_after(node* pos)
    {
        node* to_remove = pos->next;
        if (to_remove == nullptr)
            return;
        pos->next = to_remove->next;
        to_remove->next = nullptr;

        delete to_remove;
        --m_size;
    }

    void
    pop_front()
    {
        node* temp = m_begin;
        m_begin = m_begin->next;

        delete temp;
        --m_size;
    }

    size_t
    size() const
    {
        return m_size;
    }

    node*
    begin() const
    {
        return m_begin;
    }

private:
    node* m_begin;

    u32 m_size;
};

std::ostream&
operator<<(std::ostream& out, const char_list& lst)
{
    node* curr = lst.begin();
    for (u32 i = 0; i < lst.size(); ++i)
    {
        out << curr->value;
        curr = curr->next;
    }

    return out;
}

void
trim(char_list& pair_polymers)
{
    while (true)
    {
        bool found = false;
        while (pair_polymers.begin()->value != pair_polymers.begin()->next->value 
               && tolower(pair_polymers.begin()->value) == tolower(pair_polymers.begin()->next->value))
        {
            pair_polymers.pop_front();
            pair_polymers.pop_front();
            found = true;
        }

        node* curr = pair_polymers.begin();
        while (curr->next != nullptr && curr->next->next != nullptr)
        {
            if (curr->next->value != curr->next->next->value 
                && tolower(curr->next->value) == tolower(curr->next->next->value))
            {
                pair_polymers.remove_after(curr);
                pair_polymers.remove_after(curr);
                found = true;
            }
            else
                curr = curr->next;
        }

        if (!found)
            break;
    }
}

template <>
void
solution<5>::solve(std::ifstream& input)
{
    std::string poly_str;
    input >> poly_str;

    char_list pair_polymers(poly_str);
    trim(pair_polymers);
    std::cout << pair_polymers.size() << '\n';
    
    char remove = 'a';
    u32 min_len = poly_str.size();

    while (remove <= 'z')
    {
        std::string trimmed_str = "";
        for (const char c : poly_str)
        {
            if (tolower(c) != remove)
                trimmed_str += c;
        }
        char_list polymers(trimmed_str);
        
        trim(polymers);
        min_len = min_len < polymers.size() ? min_len : polymers.size();
        ++remove;
    }

    std::cout << min_len << '\n';
}
