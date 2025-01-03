#include <iostream>
#include <unordered_map>
#include <string>

#include "solution.hpp"
#include "utils.hpp"

// global d19_registers for convenience
i32 registers[6]{0, 0, 0, 0, 0};

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

std::unordered_map<std::string, itype> instruction_fn{
    { "addr", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] + registers[b]; } },
    { "addi", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] + b; } },
    { "mulr", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] * registers[b]; } },
    { "muli", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] * b; } },
    { "banr", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] & registers[b]; } },
    { "bani", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] & b; } },
    { "borr", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] | registers[b]; } },
    { "bori", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] | b; } },
    { "setr", [](i32 a, i32 b, i32 c) { registers[c] = registers[a]; } },
    { "seti", [](i32 a, i32 b, i32 c) { registers[c] = a; } },
    { "gtir", [](i32 a, i32 b, i32 c) { registers[c] = a > registers[b]; } },
    { "gtri", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] > b; } },
    { "gtrr", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] > registers[b]; } },
    { "eqir", [](i32 a, i32 b, i32 c) { registers[c] = a == registers[b]; } },
    { "eqri", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] == b; } },
    { "eqrr", [](i32 a, i32 b, i32 c) { registers[c] = registers[a] == registers[b]; } }
};

struct ProgramLine {
    itype ins;
    i32 a;
    i32 b;
    i32 c;
};

void run(i32* ip, const std::vector<ProgramLine>& prog);

#define D19_DEBUG

template<>
void
solution<19>::solve(std::ifstream& input)
{
    std::string line;

    std::getline(input, line);
    auto [_, ip_s] = fixed_split<2>(line);
    i32* ip = &registers[convert<u32>(ip_s)];

    std::vector<ProgramLine> prog;
    while (std::getline(input, line)) 
    {
        auto [ins, sa, sb, sc] = fixed_split<4>(line);
        i32 a = convert<i32>(sa);
        i32 b = convert<i32>(sb);
        i32 c = convert<i32>(sc);
        prog.emplace_back(instruction_fn[ins], a, b, c);
    }

    // run(ip, prog);
    // std::cout << registers[0] << '\n';

    for (i32 i = 0; i < 6; ++i)
    {
        registers[i] = 0;
    }
    registers[0] = 1;
    run(ip, prog);

    std::cout << registers[0] << '\n';
}

void run(i32* ip, const std::vector<ProgramLine>& prog)
{
    while (*ip >= 0 && *ip < prog.size())
    {
#ifdef D19_DEBUG
        if (*ip == 8)
        {
            std::cout << *ip << " [";
            for (auto reg : registers)
            {
                std::cout << reg << ", ";
            }
            std::cout << "] ";
        }
#endif
        prog[*ip].ins(prog[*ip].a, prog[*ip].b, prog[*ip].c);
        *ip += 1;
#ifdef D19_DEBUG
        if (*ip == 8)
        {
            // 10551315
            //  2413327
            std::cout << *ip << " [";
            for (auto reg : registers)
            {
                std::cout << reg << ", ";
            }
            std::cout << "]\n";
        }
#endif
    }
}
