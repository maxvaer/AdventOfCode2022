#include <iostream>
#include <fstream>
#include <string>
#include <utility>

bool fullyContains(std::pair <int, int> p1, std::pair <int, int> p2) {
    //p1 contains p2
    if (p1.first <= p2.first && p1.second >= p2.second)
        return true;

    //p2 contains p1
    if (p2.first <= p1.first && p2.second >= p1.second)
        return true;

    return false;
}

bool noCut(std::pair <int, int> p1, std::pair <int, int> p2) {
    if (p1.second < p2.first)
        return true;
    if (p2.second < p1.first)
        return true;

    return false;
}

static void part1() {
    //std::ifstream infile ("Day4/test.txt");
    std::ifstream infile ("Day4/puzzle.txt");
    std::string line;
    int count = 0, a = 0, b = 0, c = 0, d = 0;
    char del;
    while (infile >> a >> del >> b >> del >> c >> del >> d){
        std::pair <int, int> p1 (a,b);
        std::pair <int, int> p2 (c,d);
        if(fullyContains(p1,p2))
            count++;

    }
    std::cout << "Count Part1:" << count << "\n";
}


static void part2() {
    //std::ifstream infile ("Day4/test.txt");
    std::ifstream infile ("Day4/puzzle.txt");
    std::string line;
    int count = 0, a = 0, b = 0, c = 0, d = 0;
    char del;
    while (infile >> a >> del >> b >> del >> c >> del >> d){
        std::pair <int, int> p1 (a,b);
        std::pair <int, int> p2 (c,d);
        if(!noCut(p1,p2))
            count++;

    }
    std::cout << "Count Part2:" << count << "\n";
}


void day4() {
    std::cout << "Day4:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}
