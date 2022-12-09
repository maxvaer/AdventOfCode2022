#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

bool isConerMove(std::string dir, int oldDirX, int oldDirY) {
    // --- to |
    if (dir == "U" || dir == "D") {
        if (oldDirX != 0 && oldDirY ==0)
            return true;
    }

    // | to ---
    if (dir == "L" || dir == "R") {
        if (oldDirX == 0 && oldDirY != 0)
            return true;
    }

    return false;
}
/*         +1
 X       -1H+1
           -1
 */
bool isTouching(int xT, int yT, int xH, int yH) {
    int difX = xT - xH;
    int difY = yT - yH;


    // --
    if ((difX == 1 || difX == -1) && difY==0)
        return true;

    // |
    if ((difY == 1 || difY == -1) && difX ==0)
        return true;

    // /
    if((difX == 1 || difX == -1) && ((difY == 1 || difY == -1)))
        return true;

    // H covers T
    if (difX == 0 && difY == 0)
        return true;

    return false;
}

static void part1() {
    //std::ifstream infile ("Day9/test.txt");
    std::ifstream infile ("Day9/puzzle.txt");

    std::string dir;
    int distance = 0;

    std::set<std::pair<int, int>> visitedUniq {};
    std::vector<std::pair<int, int>> visited {};
    int xH = 0;
    int yH = 0;

    int xT = 0;
    int yT = 0;

    int dirX = 0;
    int dirY = 0;
    while (infile >> dir >> distance) {

        if (dir == "R") {
            dirX = 1;
            dirY = 0;
        }
        if (dir == "L") {
            dirX = -1;
            dirY = 0;
        }

        if (dir == "U") {
            dirY = 1;
            dirX = 0;
        }

        if (dir == "D") {
            dirY = -1;
            dirX = 0;
        }

        for (int i=0; i<distance; ++i) {
            //Skip if touching
            if (!(isTouching(xT,yT,xH + dirX,yH + dirY))) {
                xT = xH;
                yT = yH;
            }

            visited.emplace_back(xT,yT);
            visitedUniq.insert({xT,yT});

            xH = xH + dirX;
            yH = yH + dirY;
        }

    }

    std::cout << "Visited places:" << visited.size() << "\n";
}

static void moveTowards(int& destX, int& destY, int& targetX, int& targetY) {
    int diffX = targetX - destX;
    int diffY = targetY -destY;
    if (diffX > 1 || diffX < -1 || diffY > 1 || diffY < -1) {
        diffX = std::clamp(diffX, -1, 1);
        diffY = std::clamp(diffY, -1, 1);
        destX += diffX;
        destY += diffY;
    }

}

static void part2() {
    //std::ifstream infile ("Day9/test.txt");
    std::ifstream infile ("Day9/puzzle.txt");

    std::string dir;
    int distance = 0;

    std::set<std::pair<int, int>> visitedUniq {};
    std::array<std::pair<int, int>, 10> rope {};

    int dirX = 0;
    int dirY = 0;
    while (infile >> dir >> distance) {

        if (dir == "R") {
            dirX = 1;
            dirY = 0;
        }
        if (dir == "L") {
            dirX = -1;
            dirY = 0;
        }

        if (dir == "U") {
            dirY = 1;
            dirX = 0;
        }

        if (dir == "D") {
            dirY = -1;
            dirX = 0;
        }

        for (int i=0; i<distance; ++i) {
            rope[0].first += dirX;
            rope[0].second += dirY;

            for(std::size_t j=1; j<rope.size(); ++j) {
                moveTowards(rope[j].first, rope[j].second, rope[j-1].first, rope[j-1].second);
            }
            visitedUniq.insert(rope.back());
        }

    }

    std::cout << "Visited places2:" << visitedUniq.size() << "\n";
}

void day9() {
    std::cout << "Day9:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}