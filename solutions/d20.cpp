#include <iterator>
#include <memory>
#include <print>
#include <vector>

#include "solution.hpp"

constexpr const u32 INDENT_DELTA = 2;

struct Node {
    virtual void output(u32 indent) = 0;

    void print_indent(u32 indent) {
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

    void output(u32 indent) override {
        print_indent(indent);
        std::println("{}", str);
    }

    virtual ~StringNode() { }
};

struct BranchNode : public Node {
    std::vector<std::shared_ptr<Node>> choices;

    BranchNode()
    : choices{}
    { }

    void output(u32 indent) override {
        print_indent(indent);
        std::println("or(");
        for (auto choice : choices) {
            choice->output(indent + INDENT_DELTA);
        }
        print_indent(indent);
        std::println(")");
    }

    virtual ~BranchNode() { }
};

struct MultiNode : public Node {
    std::vector<std::shared_ptr<Node>> parts;

    MultiNode()
    : parts{}
    { }

    void output(u32 indent) override {
        print_indent(indent);
        std::println("concat(");
        for (auto parts : parts) {
            parts->output(indent + INDENT_DELTA);
        }
        print_indent(indent);
        std::println(")");
    }

    virtual ~MultiNode() { }
};

std::shared_ptr<Node> build_tree(std::string::iterator& iter, std::string::iterator end, u32 indent = 0) {
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
    if (base.length() > 0) {
        subregex->parts.push_back(std::make_shared<StringNode>(base));
    }
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
}
