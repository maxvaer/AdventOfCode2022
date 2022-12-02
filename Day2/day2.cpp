#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

static const char myRock = 'X';
static const char myPAPER = 'Y';
static const char myScissors = 'Z';
static const char opponentRock = 'A';
static const char opponentPAPER = 'B';
static const char opponentScissors = 'C';
static const char draw = 'Y';
static const char win = 'Z';
static const char lose = 'X';

int moveBonus(char myMove) {
    switch (myMove) {
        case myRock:
            return 1;
        case myPAPER:
            return 2;
        case myScissors:
            return 3;
        default:
            return 0;
    }
}

bool isDraw(char opponentMove, char myMove) {
    if (opponentMove == opponentPAPER && myMove == myPAPER)
        return true;
    if (opponentMove == opponentScissors && myMove == myScissors)
        return true;
    if (opponentMove == opponentRock && myMove == myRock)
        return true;
    return false;
}

char sabotageGame(char opponentMove, char desiredOutput) {
    if (opponentMove == opponentRock) {
        if (desiredOutput == win)
            return myPAPER;
        if (desiredOutput == draw)
            return myRock;
        if (desiredOutput == lose)
            return myScissors;
    }
    if (opponentMove == opponentPAPER) {
        if (desiredOutput == win)
            return myScissors;
        if (desiredOutput == draw)
            return myPAPER;
        if (desiredOutput == lose)
            return myRock;
    }
    if (opponentMove == opponentScissors) {
        if (desiredOutput == win)
            return myRock;
        if (desiredOutput == draw)
            return myScissors;
        if (desiredOutput == lose)
            return myPAPER;
    }
    return  0;
}

int playRound(char opponentMove, char myMove) {
    int bonus = moveBonus(myMove);

    if (isDraw(opponentMove , myMove))
        return 3+bonus;
    if (myMove == myRock && opponentMove == opponentScissors)
        return 6+bonus;
    if (myMove == myPAPER && opponentMove == opponentRock)
        return 6+bonus;
    if (myMove == myScissors && opponentMove == opponentPAPER)
        return 6+bonus;

    return bonus;
}

std::vector<std::pair<char, char>> getMoves() {
    std::vector<std::pair<char, char>> moves {};
    //std::ifstream myfile ("Day2/test.txt");
    std::ifstream myfile ("Day2/puzzle.txt");
    char opponentMove, myMove;
    int sum = 0;
    while (myfile >> opponentMove >> myMove){
        moves.emplace_back(opponentMove, myMove);
        sum += playRound(opponentMove, myMove);
    }
    return moves;
}

static void part1() {
    const auto moves = getMoves();
    int sum = 0;
    for (const auto &move: moves) {
        sum += playRound(move.first, move.second);
    }

    std::cout << "Sum:" << sum << "\n";
}

static void part2() {
    const auto moves = getMoves();
    int sum = 0;
    for (const auto &move: moves) {
        sum += playRound(move.first, sabotageGame(move.first,move.second));
    }

    std::cout << "Sum Sabotage:" << sum << "\n";
}

void day2() {
    std::cout << "Day2:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}


