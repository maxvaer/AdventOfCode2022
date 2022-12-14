#include <iostream>
#include <fstream>
#include <string>
#include <variant>
#include <vector>
#include <utility>
#include <algorithm>


enum class TriState {
    yes,no,unknown
};

struct VTree {
    std::vector<std::variant<std::shared_ptr<VTree>,int>> value {};
};

std::string getSubForBrackets(std::string str, std::size_t startIndex) {
    std::size_t cOpen = 0;
    std::size_t cClose = 0;

    std::size_t indexOpen = 0;
    std::size_t indexClose = 0;

    for (std::size_t i = startIndex; i < str.size(); ++i) {
        char c = str[i];
        if (c == '[') {
            if (cOpen == 0)
                indexOpen = i;
            cOpen++;
        }
        if (c == ']')
            cClose++;

        if (cOpen == cClose) {
            indexClose = i;
            break;
        }
    }

    return std::string(str.cbegin()+indexOpen, str.cbegin()+indexClose+1);
}

std::shared_ptr<VTree> insert(std::string str) {
    auto vTree = std::make_shared<VTree>();

    std::string sub = str.substr(1, str.size()-2);

    std::string curNumber;
    for (std::size_t i = 0; i < sub.size(); ++i) {
        char c = sub[i];
        if (c == '[') {
            std::string bracketSub = getSubForBrackets(sub, i);
            i += bracketSub.size();
            auto vt = insert(bracketSub);
            vTree->value.emplace_back(vt);
        }

        if (isdigit(c))
            curNumber += c;
        if (c == ',' || i+1 == sub.size()){
            int number = stoi(curNumber);
            vTree->value.emplace_back(number);
            curNumber = "";
        }


    }

    return vTree;
}

TriState checkRightOrder(std::shared_ptr<VTree> left, std::shared_ptr<VTree> right) {
    TriState isRightOrder = TriState::unknown;

    std::size_t size = left->value.size();
    if (right->value.size() < size)
        size = right->value.size();

    for (std::size_t i = 0; i < size; ++i) {
        auto &leftValue = left->value[i];
        auto &rightValue = right->value[i];

        if (std::holds_alternative<int>(leftValue) && std::holds_alternative<std::shared_ptr<VTree>>(rightValue)) {
            auto upgrade = std::make_shared<VTree>();
            upgrade->value.emplace_back(leftValue);
            isRightOrder = checkRightOrder(upgrade, std::get<std::shared_ptr<VTree>>(rightValue));
            if(isRightOrder == TriState::unknown)
                continue;
            else
                return isRightOrder;
        }else if (std::holds_alternative<int>(rightValue) && std::holds_alternative<std::shared_ptr<VTree>>(leftValue)) {
            auto upgrade = std::make_shared<VTree>();
            upgrade->value.emplace_back(rightValue);
            isRightOrder = checkRightOrder(std::get<std::shared_ptr<VTree>>(leftValue), upgrade);
            if(isRightOrder == TriState::unknown)
                continue;
            else
                return isRightOrder;
        }else if (std::holds_alternative<std::shared_ptr<VTree>>(leftValue) &&
            std::holds_alternative<std::shared_ptr<VTree>>(rightValue)) {
            isRightOrder = checkRightOrder(std::get<std::shared_ptr<VTree>>(leftValue), std::get<std::shared_ptr<VTree>>(rightValue));
            if(isRightOrder == TriState::unknown)
                continue;
            else
                return isRightOrder;
        } else {
            if(std::get<int>(leftValue) < std::get<int>(rightValue)) {
                return TriState::yes;
            } else if (std::get<int>(leftValue) > std::get<int>(rightValue)){
                return TriState::no;
            }
        }

    }

    if(left->value.size() < right->value.size())
        isRightOrder = TriState::yes;
    if(left->value.size() > right->value.size())
        isRightOrder = TriState::no;

    return isRightOrder;
}

static void part1() {
    //std::ifstream infile ("Day13/test.txt");
    std::ifstream infile ("Day13/puzzle.txt");

    std::string line;
    auto left = std::make_shared<VTree>();
    auto right = std::make_shared<VTree>();

    std::size_t pairIndex = 0;
    std::size_t sum = 0;

    bool isLeft = true;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            if (isLeft) {
                left = insert(line);
                isLeft = false;
            } else {
                right = insert(line);
                isLeft = true;
                pairIndex++;
                if(checkRightOrder(left, right) == TriState::yes)
                    sum += pairIndex;
            }
        }
    }
    std::cout << "Sum:" << sum << "\n";
}

static void part2() {
    //std::ifstream infile ("Day13/test.txt");
    std::ifstream infile ("Day13/puzzle.txt");

    std::string line;

    std::vector<std::string >packets {};

    while (std::getline(infile, line)) {
        if (line.empty())
            continue;
        packets.emplace_back(line);
    }
    packets.emplace_back("[[2]]");
    packets.emplace_back("[[6]]");

    std::sort(packets.begin(),packets.end(),[](const auto& lhs, const auto& rhs){
        return checkRightOrder(insert(lhs), insert(rhs)) == TriState::yes;
    });

    std::size_t index1 = 0;
    std::size_t index2 = 0;
    for (std::size_t i = 0; i < packets.size(); ++i) {
        if(packets[i] == "[[2]]")
            index1 = i+1;
        if(packets[i] == "[[6]]")
            index2 = i+1;
    }
    std::cout << "Result:" << index1 * index2 << "\n";
}

void day13() {
    std::cout << "Day13:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}