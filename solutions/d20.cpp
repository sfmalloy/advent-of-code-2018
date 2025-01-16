#include <cassert>
#include <iterator>
#include <limits>
#include <memory>
#include <print>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "solution.hpp"
#include "vec.hpp"

constexpr const u32 INDENT_DELTA = 2;

struct Node {
    inline static const std::unordered_map<char, Vec2> dir{
        {'N', Vec2{0, 1}},
        {'S', Vec2{0, -1}},
        {'E', Vec2{1, 0}},
        {'W', Vec2{-1, 0}}
    };

    virtual void output(u32 indent) = 0;
    virtual std::pair<Vec2, i64> find_farthest(Vec2 pos) = 0;
    virtual std::vector<std::pair<Vec2, i64>> find_dists(Vec2 pos, i64 dist, std::unordered_map<Vec2, i64>& dists) = 0;
    virtual std::vector<Vec2> count_nodes(Vec2 pos, std::unordered_set<Vec2>& nodes) = 0;

    void
    print_indent(u32 indent) {
        for (u32 i = 0; i < indent; ++i) {
            std::print(" ");
        }
    }

};

struct StringNode : public Node {
    std::string str;

    StringNode(const std::string& s)
    : str{s}
    { }

    void
    output(u32 indent) override {
        print_indent(indent);
        std::println("{}", str);
    }
    
    std::pair<Vec2, i64>
    find_farthest(Vec2 pos) override {
        for (char c : str) {
            pos += dir.at(c);
        }
        return std::make_pair(pos, str.length());
    }

    std::vector<std::pair<Vec2, i64>>
    find_dists(Vec2 pos, i64 dist, std::unordered_map<Vec2, i64>& dists) override {
        for (char c : str) {
            pos += dir.at(c);
            ++dist;
            if (!dists.contains(pos)) {
                dists[pos] = std::numeric_limits<i64>::max();
            }
            dists[pos] = std::min(dists[pos], dist);
        }
        return std::vector{std::make_pair(pos, dist)};
    }

    std::vector<Vec2>
    count_nodes(Vec2 pos, std::unordered_set<Vec2> &nodes) override {
        for (char c : str) {
            pos += dir.at(c);
            nodes.insert(pos);
        }
        return std::vector<Vec2>{pos};
    }

    virtual ~StringNode() { }
};

struct BranchNode : public Node {
    std::vector<std::shared_ptr<Node>> choices;

    BranchNode()
    : choices{}
    { }

    void
    output(u32 indent) override {
        print_indent(indent);
        std::println("or(");
        for (auto choice : choices) {
            choice->output(indent + INDENT_DELTA);
        }
        print_indent(indent);
        std::println(")");
    }


    std::pair<Vec2, i64>
    find_farthest(Vec2 pos) override {
        Vec2 far_pos{pos.r, pos.c};
        i64 far_dist = 0;
        for (auto choice : choices) {
            auto [curr, dist] = choice->find_farthest(pos);
            if (far_dist < dist and curr != pos) {
                far_pos = curr;
                far_dist = dist;
            }
        }
        return std::make_pair(far_pos, far_dist);
    }

    std::vector<std::pair<Vec2, i64>>
    find_dists(Vec2 pos, i64 dist, std::unordered_map<Vec2, i64> &dists) override {
        std::vector<std::pair<Vec2, i64>> res;
        if (dist >= 1000) {
            return res;
        }
        for (auto choice : choices) {
            auto next = choice->find_dists(pos, dist, dists);
            for (auto pair : next) {
                res.push_back(pair);
            }
        }
        return res;
    }

    std::vector<Vec2>
    count_nodes(Vec2 pos, std::unordered_set<Vec2> &nodes) override {
        std::vector<Vec2> res;
        std::unordered_set<Vec2> unique;
        for (auto choice : choices) {
            auto inner = choice->count_nodes(pos, nodes);
            for (auto i : inner) {
                if (!unique.contains(i)) {
                    res.push_back(i);
                    unique.insert(i);
                }
            }
        }
        return res;
    }

    virtual ~BranchNode() { }
};

struct MultiNode : public Node {
    std::vector<std::shared_ptr<Node>> parts;

    MultiNode()
    : parts{}
    { }

    void
    output(u32 indent) override {
        print_indent(indent);
        std::println("concat(");
        for (auto part : parts) {
            part->output(indent + INDENT_DELTA);
        }
        print_indent(indent);
        std::println(")");
    }

    std::vector<Vec2>
    count_nodes(Vec2 pos, std::unordered_set<Vec2> &nodes) override {
        std::vector<Vec2> res{pos};
        for (auto part : parts) {
            std::vector<Vec2> next;
            for (auto v : res) {
                auto inner = part->count_nodes(v, nodes);
                for (auto i : inner) {
                    next.push_back(i);
                }
            }
            res = next;
        }
        return res;
    }

    std::pair<Vec2, i64>
    find_farthest(Vec2 pos) override {
        i64 dist = 0;
        for (auto n : parts) {
            auto [curr, d] = n->find_farthest(pos);
            pos = curr;
            dist += d;
        }
        return std::make_pair(pos, dist);
    }

    std::vector<std::pair<Vec2, i64>>
    find_dists(Vec2 pos, i64 dist, std::unordered_map<Vec2, i64> &dists) override {
        std::vector<std::pair<Vec2, i64>> res = {std::make_pair(pos, dist)};
        for (auto part : parts) {
            std::vector<std::pair<Vec2, i64>> next;
            for (auto r : res) {
                auto inner = part->find_dists(r.first, r.second, dists);
                for (auto i : inner) {
                    next.push_back(i);
                }
            }
            res = next;
        }
        return res;
    }

    virtual ~MultiNode() { }
};

std::shared_ptr<Node>
build_tree(std::string::iterator& iter, std::string::iterator end, u32 indent = 0) {
    std::string base = "";

    std::shared_ptr<MultiNode> subregex = std::make_shared<MultiNode>();
    std::shared_ptr<BranchNode> branches = std::make_shared<BranchNode>();
    for (; iter != end and *iter != ')'; ++iter) {
        if (*iter == '(') {
            subregex->parts.push_back(std::make_shared<StringNode>(base));
            ++iter;
            subregex->parts.push_back(build_tree(iter, end, indent + 2));
            base = "";
        } else if (*iter == '|') {
            if (base.length() > 0) {
                subregex->parts.push_back(std::make_shared<StringNode>(base));
            }
            if (subregex->parts.size() > 1) {
                branches->choices.push_back(subregex);
            } else if (subregex->parts.size() == 1) {
                branches->choices.push_back(subregex->parts[0]);
            }
            subregex = std::make_shared<MultiNode>();
            base = "";
        } else {
            base += *iter;
        }
    }
    subregex->parts.push_back(std::make_shared<StringNode>(base));
    if (branches->choices.size() > 0) {
        if (subregex->parts.size() > 1) {
            branches->choices.push_back(subregex);
        } else if (subregex->parts.size() == 1) {
            branches->choices.push_back(subregex->parts[0]);
        }
        return branches;
    }
    return subregex;
}

template <>
void
solution<20>::solve(std::ifstream& input)
{
    std::string regex;
    input >> regex;
    // remove ^ and $
    regex = regex.substr(1);
    regex.pop_back();
    
    std::string::iterator r = std::begin(regex);
    auto tree = build_tree(r, std::end(regex));

    Vec2 start{0, 0};

    // part 1
    auto [res, dist] = tree->find_farthest(start);
    std::println("{}", dist);

    // part 2
    // get total number of nodes
    std::unordered_set<Vec2> nodes;
    nodes.insert(start);
    tree->count_nodes(start, nodes);

    // find distances of nodes that are UNDER 1000
    std::unordered_map<Vec2, i64> dists;
    auto idk = tree->find_dists(start, 0, dists);
    dists[start] = 0;
    i64 count = 0;
    for (auto [k, v] : dists) {
        if (v < 1000) {
            ++count;
        }
    }

    std::println("{}", nodes.size() - count, dists.size());
}
