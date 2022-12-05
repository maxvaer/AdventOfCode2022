#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>

std::vector<int> findLocations(std::string const &sample, char findIt)
{
    std::vector<int> characterLocations;
    for(std::size_t i =0; i < sample.size(); i++)
        if(sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

static void parseStacks(const std::string &line, std::unordered_map<int, std::vector<char>> &preStack,
                        std::set<int> &keySet) {
    for (char c = 'A'; c <= 'Z'; ++c) {
        std::vector<int> locations = findLocations(line,c);
        for (int const &location: locations) {
            keySet.insert(location);
            preStack[location].push_back(c);
        }
    }
}

static void parseMoves(const std::string &line, std::vector<std::vector<int>> &moves) {
    std::vector<int> move {};
    std::istringstream inStream(line);
    int numberOfItems = 0;
    int source = 0;
    int target = 0;
    std::string del = "";
    inStream >> del >> numberOfItems >> del >> source >> del >> target;
    move.emplace_back(numberOfItems);
    move.emplace_back(source-1);
    move.emplace_back(target-1);
    moves.emplace_back(move);
}

static void normalizeStacks(const std::unordered_map<int, std::vector<char>> &preStack, std::set<int> &keySet,
                            std::vector<std::vector<char>> &stacks) {
    for(auto const &key : keySet) {
        stacks.emplace_back(preStack.at(key));
    }
}

void doMove(std::vector<std::vector<char>>& stacks, const std::vector<int>& move) {
    int numberOfElemets = move[0];
    int source = move[1];
    int target = move[2];

    std::vector<char>& sourceStack = stacks[source];
    std::vector<char>& targetStack = stacks[target];
    for (int i=1; i<=numberOfElemets; i++) {
        char movingElement = sourceStack.front();
        targetStack.insert(targetStack.cbegin(),movingElement);
        sourceStack.erase(sourceStack.cbegin());
    }

}

void doMoveWithCrane9001(std::vector<std::vector<char>>& stacks, const std::vector<int>& move) {
    int numberOfElemets = move[0];
    int source = move[1];
    int target = move[2];

    std::vector<char>& sourceStack = stacks[source];
    std::vector<char>& targetStack = stacks[target];
    auto itBegin = sourceStack.cbegin();
    auto itEnd = sourceStack.cbegin()+numberOfElemets;

    targetStack.insert(targetStack.cbegin(),itBegin,itEnd);
    sourceStack.erase(itBegin, itEnd);
}

void doMoves(std::vector<std::vector<char>>& stacks, const std::vector<std::vector<int>>& moves) {
    for (auto const &move: moves) {
        doMove(stacks, move);
    }
}

void doMovesWithCrane9001(std::vector<std::vector<char>>& stacks, const std::vector<std::vector<int>>& moves) {
    for (auto const &move: moves) {
        doMoveWithCrane9001(stacks, move);
    }
}

void printResult(std::vector<std::vector<char>> stacks) {
    std::cout << "Result:";
    for (auto const &stack: stacks) {
        std::cout << stack.front();
    }
    std::cout << "\n";
}

static void part1() {
    //std::ifstream infile ("Day5/test.txt");
    std::ifstream infile ("Day5/puzzle.txt");
    std::string line;

    bool readMoves = false;
    std::vector<std::vector<int>> moves {};
    std::unordered_map<int, std::vector<char>> preStack;
    std::set<int> keySet{};
    while (std::getline(infile,line)){
        if (line.empty()) {
            readMoves = true;
            continue;
        }
        if (line.find("[") != std::string::npos) {
            parseStacks(line, preStack, keySet);
        }

        if (readMoves) {
            parseMoves(line, moves);
        }
    }

    std::vector<std::vector<char>> stacks;
    normalizeStacks(preStack, keySet, stacks);

    doMoves(stacks, moves);
    printResult(stacks);
}

static void part2() {
    //std::ifstream infile ("Day5/test.txt");
    std::ifstream infile ("Day5/puzzle.txt");
    std::string line;

    bool readMoves = false;
    std::vector<std::vector<int>> moves {};
    std::unordered_map<int, std::vector<char>> preStack;
    std::set<int> keySet{};
    while (std::getline(infile,line)){
        if (line.empty()) {
            readMoves = true;
            continue;
        }
        if (line.find("[") != std::string::npos) {
            parseStacks(line, preStack, keySet);
        }

        if (readMoves) {
            parseMoves(line, moves);
        }
    }

    std::vector<std::vector<char>> stacks;
    normalizeStacks(preStack, keySet, stacks);

    doMovesWithCrane9001(stacks, moves);
    printResult(stacks);
}

void day5() {
    std::cout << "Day5:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}