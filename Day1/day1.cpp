#include <iostream>
#include <fstream>
#include <string>
#include <set>

static std::multiset<int, std::greater<> > getCalories() {
    std::multiset<int, std::greater<> > calories;
    int currentTotalCalories = 0;

    std::string line;
    //std::ifstream myfile ("test.txt");
    std::ifstream myfile ("Day1/puzzle.txt");
    while (std::getline(myfile,line)){
        if (line.empty()){
            calories.insert(currentTotalCalories);
            currentTotalCalories = 0;
        }else{
            int currentCalories = std::stoi(line);
            currentTotalCalories += currentCalories;
        }
    }


    return calories;
}

static void part1() {
    auto calories = getCalories();
    std::cout << "Max Calories:" << *calories.cbegin() << std::endl;
}

static void part2() {
    auto calories = getCalories();
    int topThreeCalories = (*calories.cbegin() + *next(calories.cbegin(),1) + *next(calories.cbegin(),2));
    std::cout << "Sum of top 3 Calories:" << topThreeCalories << std::endl;
}

void day1() {
    std::cout << "Day1:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}



