#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

static void part1() {
    //std::ifstream infile ("Day10/test.txt");
    std::ifstream infile ("Day10/puzzle.txt");

    std::string cmd;
    std::string line;

    int regX = 1;
    int cycles = 1;

    int sum = 0;
    int interestingSignals[] = {20,60,100,140,180,220};

    while (std::getline(infile, line)) {
        std::istringstream inStream(line);

        int arg = 0;
        int neededCylces = 1;
        if (line.starts_with("addx")) {
            inStream >> cmd >> arg;
            neededCylces = 2;
        }

        while (neededCylces != 0) {
            int oldCylce = cycles;
            auto position = std::find(std::begin(interestingSignals), std::end(interestingSignals), cycles);
            if (position != std::end(interestingSignals)) {
                sum += (cycles * regX);
                std::cout << "RESULT:" << sum << "Cylce:" << cycles << "\n";
            }
            std::cout << "Cylce:" << cycles << " Register X:" << regX << "\n";
            cycles++;
            neededCylces--;
            if (neededCylces==0) {
                regX += arg;
            }
            std::cout << "After Cylce:" << oldCylce << " Register X:" << regX << "\n";
        }
    }
    std::cout << "Sum: " << sum << "\n";
}

static void part2() {
    //std::ifstream infile ("Day10/test.txt");
    std::ifstream infile ("Day10/puzzle.txt");

    std::string cmd;
    std::string line;

    int regX = 1;
    int cycles = 1;

    int interestingSignals[] = {20,60,100,140,180,220};

    int width = 40;

    while (std::getline(infile, line)) {
        std::istringstream inStream(line);

        int arg = 0;
        int neededCylces = 1;
        if (line.starts_with("addx")) {
            inStream >> cmd >> arg;
            neededCylces = 2;
        }

        while (neededCylces != 0) {
            if ((cycles -1) % width +1 == regX || (cycles -1) % width+1 == regX+1 || (cycles -1) % width+1 == regX+2) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
            if (cycles % width ==0) {
                std::cout << "\n";
            }
            cycles++;
            neededCylces--;
            if (neededCylces==0) {
                regX += arg;
            }

        }

    }
    std::cout << "\n";
}

void day10() {
    std::cout << "Day10:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}