#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <utility>
#include <functional>
#include <stdexcept>
#include <set>


struct Monkey {
    uint64_t newVal(uint64_t a, uint64_t b) const {
        std::function<uint64_t(uint64_t,uint64_t)> operation;

        if (operand == "+")
            operation = std::plus<uint64_t>{};
        else
            operation = std::multiplies<uint64_t>{};

        return operation(a, b);
    }

    uint64_t worry(uint64_t a, uint64_t b) const {
        if (b == 0) {
            b = a;
        }
        return newVal(a, b);
    }

    std::queue<uint64_t> items;
    int test{};
    std::string operand;
    uint64_t newValWeight{};
    int trueMonkey{};
    int falseMonkey{};
    int inspectedItems{};
};

std::vector<Monkey> getMonkeys() {
    //std::ifstream infile ("Day11/test.txt");
    std::ifstream infile ("Day11/puzzle.txt");

    std::string line;

    std::vector<Monkey> monkeys{};
    Monkey monkey;
    while (std::getline(infile, line)) {
        std::istringstream sstream(line);

        if(line.starts_with("Monkey")) {
            monkey = {};
        }

        if(line.starts_with("  Starting items")) {
            std::string sub = line.substr(18);
            std::istringstream ss(sub);
            std::string token;
            uint64_t item;
            char del;
            while(ss >> item >> del) {
                monkey.items.push(item);
            }
            monkey.items.push(item);
        }

        if(line.starts_with("  Operation:")) {
            uint64_t newValWeight = 0;
            std::string operand;
            std::string strWeight;
            std::string del;
            sstream >> del >> del >> del >> del >> operand >> strWeight;
            try {
                newValWeight = stoull(strWeight);
            } catch (...) {

            }
            monkey.operand = operand;
            monkey.newValWeight = newValWeight;
        }

        if(line.starts_with("  Test:")) {
            std::string del;
            int test;
            sstream >> del >> del >> del >> test;
            monkey.test = test;
        }

        if(line.starts_with("    If true:")) {
            int trueMonkey;
            std::string del;
            sstream >> del >> del >> del >> del >> del >> trueMonkey;
            monkey.trueMonkey = trueMonkey;
        }

        if(line.starts_with("    If false:")) {
            int falseMonkey;
            std::string del;
            sstream >> del >> del >> del >> del >> del >> falseMonkey;
            monkey.falseMonkey = falseMonkey;
            monkeys.emplace_back(monkey);
        }
    }
    return monkeys;
}

static void part1() {
    std::vector<Monkey> monkeys = getMonkeys();

    for (int i = 0; i < 20; ++i) {
        for (auto &mk: monkeys) {
            if(mk.items.empty())
                continue;

            while(!mk.items.empty()) {
                uint64_t item = mk.items.front();
                mk.items.pop();

                mk.inspectedItems++;
                uint64_t worryLevel = mk.worry(item, mk.newValWeight);
                worryLevel = worryLevel / 3;
                int nextMonkey = 0;
                if (worryLevel % mk.test == 0)
                    nextMonkey = mk.trueMonkey;
                else
                    nextMonkey = mk.falseMonkey;

                monkeys[nextMonkey].items.push(worryLevel);
            }
        }
    }

    std::set<int> inspectedItems;
    for (auto &mk: monkeys) {
        inspectedItems.insert(mk.inspectedItems);
    }

    std::cout << "Result Part1: " << *(inspectedItems.rbegin()) * *(std::next(inspectedItems.rbegin())) << "\n";

}


static void part2() {
    std::vector<Monkey> monkeys = getMonkeys();

    int gcm = 1;
    for (auto &mk: monkeys) {
        gcm *= mk.test;
    }

    for (int i = 0; i < 10000; ++i) {
        for (auto &mk: monkeys) {
            if(mk.items.empty())
                continue;

            while(!mk.items.empty()) {
                uint64_t item = mk.items.front();
                mk.items.pop();

                mk.inspectedItems++;
                uint64_t worryLevel = mk.worry(item, mk.newValWeight);
                int nextMonkey = 0;
                if ((worryLevel % mk.test == 0))
                    nextMonkey = mk.trueMonkey;
                else
                    nextMonkey = mk.falseMonkey;

                worryLevel = worryLevel % gcm;
                monkeys[nextMonkey].items.push(worryLevel);
            }
        }
    }

    std::set<uint64_t> inspectedItems;
    for (auto &mk: monkeys) {
        inspectedItems.insert(mk.inspectedItems);
    }
    uint64_t result = *(inspectedItems.rbegin()) * *(std::next(inspectedItems.rbegin()));
    std::cout << "Result Part2: " << result << "\n";

}

void day11() {
    std::cout << "Day11:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}