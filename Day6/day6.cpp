#include <iostream>
#include <fstream>

bool isCharDuplication(std::string s)
{
    for (std::size_t i = 0; i < s.length(); i++)
        for (std::size_t j = i+1; j < s.length(); j++)
            if (s[i] == s[j])
                return true;
    return false;
}

static void part1() {
    //std::ifstream infile ("Day6/test.txt");
    std::ifstream infile ("Day6/puzzle.txt");
    std::string line;

    while (infile >> line){
        for(std::string::size_type i = 3; i < line.size(); ++i) {
            std::string sub;
            for(int x = 3; x >= 0; x--) {
                sub.push_back(line[i-x]);
            }
            if (!isCharDuplication(sub)) {
                std::cout << "Index 4 character marker:" << i + 1 << "\n";
                break;
            }
        }
    }
}

static void part2() {
    //std::ifstream infile ("Day6/test.txt");
    std::ifstream infile ("Day6/puzzle.txt");
    std::string line;

    while (infile >> line){
        for(std::string::size_type i = 13; i < line.size(); ++i) {
            std::string sub;
            for(int x = 13; x >= 0; x--) {
                sub.push_back(line[i-x]);
            }
            if (!isCharDuplication(sub)) {
                std::cout << "Index 14 character marker:" << i + 1 << "\n";
                break;
            }
        }
    }
}

void day6() {
    std::cout << "Day6:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}
