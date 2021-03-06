#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "Day.hpp"
#include "Timer.hpp"

// Finished days
#include "Day01.hpp"
#include "Day02.hpp"
#include "Day03.hpp"
#include "Day04.hpp"
#include "Day05.hpp"
#include "Day06.hpp"
#include "Day08.hpp"
#include "Day11.hpp"
#include "Day22.hpp"

void runSingle(const int& day);

void runAll();

const int DAYS_COMPLETED[] = { 1, 2, 3, 4, 5, 6, 8, 11, 22 };

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

    std::cout << "Day " << day << ":" << std::endl;

    Timer t;
    
    switch(day) {
        case 1:
            t.start();
            std::cout << "Part 1: ";
            Day<1>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<1>::solve2(in2, std::cout);
            t.stop();
            break;
        case 2:
            t.start();
            std::cout << "Part 1: ";
            Day<2>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<2>::solve2(in2, std::cout);
            t.stop();
            break;
        case 3:
            t.start();
            std::cout << "Part 1: ";
            Day<3>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<3>::solve2(in2, std::cout);
            t.stop();
            break;
        case 4:
            t.start();
            std::cout << "Part 1: ";
            Day<4>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<4>::solve2(in2, std::cout);
            t.stop();
            break;
        case 5:
            t.start();
            std::cout << "Part 1: ";
            Day<5>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<5>::solve2(in2, std::cout);
            t.stop();
            break;
        case 6:
            t.start();
            std::cout << "Part 1: ";
            Day<6>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<6>::solve2(in2, std::cout);
            t.stop();
            break;
        case 8:
            t.start();
            std::cout << "Part 1: ";
            Day<8>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<8>::solve2(in2, std::cout);
            t.stop();
            break;
        case 11:
            t.start();
            std::cout << "Part 1: ";
            Day<11>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<11>::solve2(in2, std::cout);
            t.stop();
            break;
        case 22:
            t.start();
            std::cout << "Part 1: ";
            Day<22>::solve1(in1, std::cout);
            std::cout << "Part 2: ";
            Day<22>::solve2(in2, std::cout);
            t.stop();
            break;
        default:
            std::cout << "Day not complete";
    }

    std::cout << "Time: " << std::fixed << std::setprecision(3) << t.getDurationMs() << " ms" << std::endl;
}

void runAll() {
    std::cout << "All days:\n" << std::endl;
    for (const int& i : DAYS_COMPLETED) {
        runSingle(i);
        std::cout << std::endl;
    }
}