#include <iostream>

#include "solution.hpp"

struct node
{
    char value;
    node* next;
};

class char_list
{
public:
    char_list(const std::string& chars)
        : m_begin(nullptr),
          m_end(nullptr),
          m_size(0)
    {
        for (const char c : chars)
            push_back(c);    
    }

    ~char_list()
    {
        node* curr = m_begin;
        while (curr != nullptr)
        {
            node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void
    push_back(char c)
    {
        node* new_node = new node{c, nullptr};
        if (m_end != nullptr)
        {
            m_end->next = new_node;
            m_end = m_end->next;
        }
        else if (m_begin == nullptr)
        {
            m_begin = new_node;
            m_end = m_begin;
        }
        
        ++m_size;
    }

    size_t
    size() const
    {
        return m_size;
    }

private:
    node* m_begin;
    node* m_end;

    size_t m_size;
};

template <>
void
solution<5>::solve(std::ifstream& input)
{
    char_list lst("abcd");
    std::cout << lst.size() << '\n';
}
