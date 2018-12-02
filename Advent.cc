#include <iostream>
#include <fstream>

#include "Day02.hpp"

int main(int argc, char* argv[]) {
    std::ifstream file1("Day02.txt");
    std::ifstream file2("Day02.txt");
    solve(file1, std::cout);
    solve2(file2, std::cout);
}