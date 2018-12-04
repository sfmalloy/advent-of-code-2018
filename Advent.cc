#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Day.hpp"

// Finished days
#include "Day01.hpp"
#include "Day02.hpp"
#include "Day03.hpp"

void runSingle(const int& day);

void runAll();

const int DAYS_COMPLETED = 2;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "./Advent -s <day_number> OR\n"
                  << "./Advent -a"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string option = argv[1];
    if (option == "-a") {
        runAll();
    } else if (option == "-s" && argc == 3) {
        int day = std::stoi(argv[2]);
        runSingle(day);
    }


    return EXIT_SUCCESS;
}

void runSingle(const int& day) {
    std::string dayStr = (day < 10 ? "Day0" : "Day") + std::to_string(day);
    std::ifstream in1, in2;
    in1.open((dayStr + ".txt").c_str());
    in2.open((dayStr + ".txt").c_str());

    std::cout << dayStr << ":" << std::endl;

    switch(day) {
        case 1:
            Day<1>::solve1(in1, std::cout);
            Day<1>::solve2(in2, std::cout);
            break;
        case 2:
            Day<2>::solve1(in1, std::cout);
            Day<2>::solve2(in2, std::cout);
            break;
        case 3:
            Day<3>::solve1(in1, std::cout);
            Day<3>::solve2(in2, std::cout);
            break;
        default:
            std::cout << "Day not complete";
    }
}

void runAll() {
    std::cout << "All days:" << std::endl;
    for (int i = 1; i <= DAYS_COMPLETED; ++i) {
        runSingle(i);
        std::cout << std::endl;
    }
}