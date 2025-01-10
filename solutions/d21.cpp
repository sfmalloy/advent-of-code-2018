#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils.hpp"
#include "solution.hpp"

using itype = void(*)(i64, i64, i64);
namespace d21
{

i64 registers[6]{0, 0, 0, 0, 0};

std::unordered_map<std::string, itype> instruction_fn{
    { "addr", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] + registers[b]; } },
    { "addi", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] + b; } },
    { "mulr", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] * registers[b]; } },
    { "muli", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] * b; } },
    { "banr", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] & registers[b]; } },
    { "bani", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] & b; } },
    { "borr", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] | registers[b]; } },
    { "bori", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] | b; } },
    { "setr", [](i64 a, i64 b, i64 c) { registers[c] = registers[a]; } },
    { "seti", [](i64 a, i64 b, i64 c) { registers[c] = a; } },
    { "gtir", [](i64 a, i64 b, i64 c) { registers[c] = a > registers[b]; } },
    { "gtri", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] > b; } },
    { "gtrr", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] > registers[b]; } },
    { "eqir", [](i64 a, i64 b, i64 c) { registers[c] = a == registers[b]; } },
    { "eqri", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] == b; } },
    { "eqrr", [](i64 a, i64 b, i64 c) { registers[c] = registers[a] == registers[b]; } }
};

struct ProgramLine {
    itype ins;
    i64 a;
    i64 b;
    i64 c;
};

}

i64 run(i64* ip, const std::vector<d21::ProgramLine>& prog, bool part2);
void debug(i64* ip);

template <>
void
solution<21>::solve(std::ifstream& input)
{
    std::string line;

    std::getline(input, line);
    auto [_, ip_s] = fixed_split<2>(line);
    i64* ip = &d21::registers[convert<u32>(ip_s)];

    std::vector<d21::ProgramLine> prog;
    while (std::getline(input, line)) 
    {
        auto [ins, sa, sb, sc] = fixed_split<4>(line);
        i64 a = convert<i64>(sa);
        i64 b = convert<i64>(sb);
        i64 c = convert<i64>(sc);
        prog.emplace_back(d21::instruction_fn[ins], a, b, c);
    }

    d21::registers[0] = 0;
    std::cout << run(ip, prog, false) << '\n';
    std::cout << run(ip, prog, true) << '\n';
}

i64 run(i64* ip, const std::vector<d21::ProgramLine>& prog, bool part2)
{
    i64 prev = 0;
    std::unordered_set<i64> seen;
    while (*ip >= 0 and *ip < prog.size()) {
        if (*ip + 2 == 30) {
            if (not part2) {
                return d21::registers[3];
            }
            if (seen.contains(d21::registers[3])) {
                return prev;
                std::cout << prev << '\n';
                break;
            }
            seen.insert(d21::registers[3]);
            prev = d21::registers[3];
        }
        prog[*ip].ins(prog[*ip].a, prog[*ip].b, prog[*ip].c);
        *ip += 1;
    }
    return 0;
}
