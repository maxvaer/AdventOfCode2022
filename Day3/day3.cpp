#include <iostream>
#include <fstream>

static void part1() {
    //std::ifstream myfile ("Day3/test.txt");
    std::ifstream myfile ("Day3/puzzle.txt");
    std::string content;
    int sum = 0;
    while (myfile >> content){
        std::string compartmentOne = content.substr(0, content.length()/2);
        std::string compartmentTwo = content.substr(content.length()/2);
        std::size_t found = compartmentOne.find_first_of(compartmentTwo);
        const char duplicate = compartmentOne[found];
        if (std::islower(duplicate)) {
            sum += duplicate-'a'+1;
        } else {
            sum += duplicate-'A'+26+1;
        }
    }
    std::cout << "Sum of priorities:" << sum << "\n";
}

static void part2() {
    //std::ifstream myfile ("Day3/test.txt");
    std::ifstream myfile ("Day3/puzzle.txt");
    int sum = 0;
    std::string first;
    std::string second;
    std::string third;
    while (myfile >> first >> second >> third){

        std::size_t firstFoundIndex = 0;
        firstFoundIndex = first.find_first_of(second);
        std::size_t secondFoundIndex = first.find_first_of(third, firstFoundIndex);

        const char duplicate = first[secondFoundIndex];
        if (std::islower(duplicate)) {
            sum += duplicate-'a'+1;
        } else {
            sum += duplicate-'A'+26+1;
        }
    }
    std::cout << "Group sum:" << sum << "\n";
}

void day3() {
    std::cout << "Day3:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}
