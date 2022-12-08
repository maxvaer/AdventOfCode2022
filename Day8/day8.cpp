#include <iostream>
#include <fstream>
#include <vector>


bool isVisible(const std::vector<std::vector<int>>& trees, std::size_t x, std::size_t y) {
    if (x==0 || y==0 || x==trees[0].size()-1 || y==trees.capacity()-1)
        return true;

    const int height = trees[y][x];
    //Horizontal <--
    bool left = true;
    for (int i = x-1; i >= 0; i--) {
        int otherTreeHeight = trees[y][i];
        if(otherTreeHeight>=height) {
            left = false;
            break;
        }
    }
    //Horizontal -->
    bool right = true;
    for (std::size_t i = x+1; i < trees[y].size(); i++) {
        int otherTreeHeight = trees[y][i];
        if(otherTreeHeight>=height) {
            right = false;
            break;
        }
    }

    //Vertical ^
    bool up = true;
    for (int i = y-1; i >= 0; i--) {
        int otherTreeHeight = trees[i][x];
        if(otherTreeHeight>=height) {
            up = false;
            break;
        }
    }

    //Vertical v
    bool down = true;
    for (std::size_t i = y+1; i < trees.size(); i++) {
        int otherTreeHeight = trees[i][x];
        if(otherTreeHeight>=height) {
            down = false;
            break;
        }
    }

    return up || down || left || right;
}

int treeScore(const std::vector<std::vector<int>>& trees, std::size_t x, std::size_t y) {

    const int height = trees[y][x];
    //Horizontal <--
    int left = 0;
    for (int i = x-1; i >= 0; i--) {
        left++;
        int otherTreeHeight = trees[y][i];
        if(otherTreeHeight>=height) {
            break;
        }
    }
    //Horizontal -->
    int right = 0;
    for (std::size_t i = x+1; i < trees[y].size(); i++) {
        right++;
        int otherTreeHeight = trees[y][i];
        if(otherTreeHeight>=height) {
            break;
        }
    }

    //Vertical ^
    int up = 0;
    for (int i = y-1; i >= 0; i--) {
        up++;
        int otherTreeHeight = trees[i][x];
        if(otherTreeHeight>=height) {
            break;
        }
    }

    //Vertical v
    int down = 0;
    for (std::size_t i = y+1; i < trees.size(); i++) {
        down++;
        int otherTreeHeight = trees[i][x];
        if(otherTreeHeight>=height) {
            break;
        }
    }

    return up * down * left * right;
}

static void part1() {
    //std::ifstream infile ("Day8/test.txt");
    std::ifstream infile ("Day8/puzzle.txt");
    std::string line;

    std::vector<std::vector<int>> trees{};
    while (infile >> line) {
        std::vector<int> row{};
        for (const char &c: line) {
            row.push_back(c-'0');
        }
        trees.push_back(row);
    }
    std::size_t visibleTrees = 0;
    for (std::size_t y = 0; y < trees.size(); y++) {
        for (std::size_t x = 0; x < trees[0].size(); x++) {
            if (isVisible(trees,x,y))
                visibleTrees++;
        }
    }
    std::cout << "Visible Trees:" << visibleTrees << "\n";
}

static void part2() {
    //std::ifstream infile ("Day8/test.txt");
    std::ifstream infile ("Day8/puzzle.txt");
    std::string line;

    std::vector<std::vector<int>> trees{};
    while (infile >> line) {
        std::vector<int> row{};
        for (const char &c: line) {
            row.push_back(c-'0');
        }
        trees.push_back(row);
    }
    int scenicScore= 0;
    for (std::size_t y = 0; y < trees.size(); y++) {
        for (std::size_t x = 0; x < trees[0].size(); x++) {
                int currentScore = treeScore(trees, x, y);
                if (currentScore > scenicScore)
                    scenicScore = currentScore;
        }
    }
    std::cout << "Tree Score:" << scenicScore << "\n";
}


void day8() {
    std::cout << "Day8:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}