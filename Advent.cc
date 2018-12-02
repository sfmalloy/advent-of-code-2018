#include <iostream>
#include <fstream>

#include "Day01.hpp"

int main(int argc, char* argv[]) {
    std::ifstream file1("Day01.txt");
    std::ifstream file2("Day01.txt");
    solve(file1, std::cout);
    solve2(file2, std::cout);
}