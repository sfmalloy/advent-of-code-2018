#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

// global registers for convenience
i32 reg[4]{0, 0, 0, 0};

// instruction declarations
inline void addr(i32 a, i32 b, i32 c);
inline void addi(i32 a, i32 b, i32 c);

inline void mulr(i32 a, i32 b, i32 c);
inline void muli(i32 a, i32 b, i32 c);

inline void banr(i32 a, i32 b, i32 c);
inline void bani(i32 a, i32 b, i32 c);

inline void borr(i32 a, i32 b, i32 c);
inline void bori(i32 a, i32 b, i32 c);

inline void setr(i32 a, i32 b, i32 c);
inline void seti(i32 a, i32 b, i32 c);

inline void gtir(i32 a, i32 b, i32 c);
inline void gtri(i32 a, i32 b, i32 c);
inline void gtrr(i32 a, i32 b, i32 c);

inline void eqir(i32 a, i32 b, i32 c);
inline void eqri(i32 a, i32 b, i32 c);
inline void eqrr(i32 a, i32 b, i32 c);

using itype = void(*)(i32, i32, i32);

template<>
void
solution<16>::solve(std::ifstream& input)
{
    std::unordered_map<itype, std::vector<u32>> instructions{
        { addr, std::vector<u32>(16, 0) },
        { addi, std::vector<u32>(16, 0) },
        { mulr, std::vector<u32>(16, 0) },
        { muli, std::vector<u32>(16, 0) },
        { banr, std::vector<u32>(16, 0) },
        { bani, std::vector<u32>(16, 0) },
        { borr, std::vector<u32>(16, 0) },
        { bori, std::vector<u32>(16, 0) },
        { setr, std::vector<u32>(16, 0) },
        { seti, std::vector<u32>(16, 0) },
        { gtir, std::vector<u32>(16, 0) },
        { gtri, std::vector<u32>(16, 0) },
        { gtrr, std::vector<u32>(16, 0) },
        { eqir, std::vector<u32>(16, 0) },
        { eqri, std::vector<u32>(16, 0) },
        { eqrr, std::vector<u32>(16, 0) }
    };
    
    u32 super_valid = 0;
    for (;;)
    {
        std::string before_line = readline(input);
        if (before_line.size() == 0)
            break;
        auto before = type_split<i32>(split(before_line, ": ")[1].substr(1), ", ");
        auto [op, a, b, c] = type_split<i32, 4>(readline(input));
        auto after = type_split<i32>(split(readline(input), ":  ")[1].substr(1), ", ");
        readline(input);
        
        u32 count = 0;
        for (auto& [inst, counts] : instructions)
        {
            for (u32 i = 0; i < 4; ++i)
                reg[i] = before[i];
            inst(a, b, c);
            bool valid = true;
            for (u32 i = 0; i < 4; ++i)
            {
                if (reg[i] != after[i])
                {
                    valid = false;
                    break;
                }
            }
            count += valid;
            if (valid)
                ++counts[op];
        }
        if (count >= 3)
            ++super_valid;
    }

    std::cout << super_valid << '\n';
    readline(input);

    std::vector<itype> opcodes(16, nullptr);
    bool finished = false;
    while (!finished)
    {
        for (i32 opcode = 0; opcode < 16; ++opcode)
        {
            if (opcodes[opcode] == nullptr)
            {
                std::unordered_set<itype> instrs;
                for (auto& [inst, counts] : instructions)
                {
                    if (counts[opcode] > 0)
                        instrs.insert(inst);
                }
                if (instrs.size() == 1)
                    opcodes[opcode] = *instrs.begin();
                instructions.erase(opcodes[opcode]);
            }
        }

        finished = true;
        for (auto op : opcodes)
        {
            if (op == nullptr)
            {
                finished = false;
                break;
            }
        }
    }

    for (i32 i = 0; i < 4; ++i)
        reg[i] = 0;
    std::string line;
    while (std::getline(input, line))
    {
        auto [op, a, b, c] = type_split<i32, 4>(line);
        opcodes[op](a, b, c);
    }
    std::cout << reg[0] << '\n';
}

inline void
addr(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] + reg[b];
}

inline void
addi(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] + b;
}

inline void
mulr(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] * reg[b];
}

inline void
muli(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] * b;
}

inline void
banr(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] & reg[b];
}

inline void
bani(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] & b;
}

inline void
borr(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] | reg[b];
}

inline void
bori(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] | b;
}

inline void 
setr(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a];
}

inline void
seti(i32 a, i32 b, i32 c)
{
    reg[c] = a;
}

inline void
gtir(i32 a, i32 b, i32 c)
{
    reg[c] = a > reg[b];
}

inline void
gtri(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] > b;
}

inline void
gtrr(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] > reg[b];
}

inline void
eqir(i32 a, i32 b, i32 c)
{
    reg[c] = a == reg[b];
}

inline void
eqri(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] == b;
}

inline void
eqrr(i32 a, i32 b, i32 c)
{
    reg[c] = reg[a] == reg[b];
}
