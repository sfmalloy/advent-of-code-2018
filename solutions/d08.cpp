#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

struct node
{
    std::vector<node*> children;
    std::vector<u32> metadata;

    node()
        : children(),
          metadata()
    { }
    node(const node&) = delete;
    node operator=(const node&) = delete;

    ~node()
    {
        for (auto* c : children)
            delete c;
    }
};

u32 g_idx;

node*
tree(const std::vector<u32> data)
{
    if (g_idx >= data.size())
        return nullptr;
    u32 C = data[g_idx];
    u32 M = data[g_idx + 1];
    node* root = new node();
    g_idx += 2;
    for (u32 i = 0; i < C; ++i)
        root->children.push_back(tree(data));
    for (u32 i = 0; i < M; ++i)
        root->metadata.push_back(data[g_idx + i]);
    g_idx += M;
    return root;
}

u32
metasum(node* root)
{
    if (root == nullptr)
        return 0;
    u32 sum = std::accumulate(std::begin(root->metadata), std::end(root->metadata), 0);
    for (auto* child : root->children)
        sum += metasum(child);
    return sum;
}

u32
value(node* root)
{
    if (root == nullptr)
        return 0;
    u32 val = 0;
    if (root->children.size() > 0)
    {
        for (u32 m : root->metadata)
        {
            if (m <= root->children.size())
                val += value(root->children[m - 1]);
        }
    }
    else
        val = std::accumulate(std::begin(root->metadata), std::end(root->metadata), 0);

    return val;
}

template<>
void
solution<8>::solve(std::ifstream& input)
{
    g_idx = 0;
    auto vec = type_split<u32>(readline(input));
    node* root = tree(vec);
    std::cout << metasum(root) << '\n';
    std::cout << value(root) << '\n';
    delete root;
}
