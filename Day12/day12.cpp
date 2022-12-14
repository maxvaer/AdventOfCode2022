#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

struct Nodelist;

struct Node {
    std::size_t x;
    std::size_t y;
    int height;
    std::size_t value = SIZE_MAX;
    int edge = 1;
    bool visited = false;

    Nodelist getNeighbours(const Nodelist& nList, std::size_t maxX, std::size_t maxY);
};

struct Nodelist {
    std::vector<Node*> nodes{};

    Nodelist() = default;

    Nodelist(const Nodelist& other) {
        nodes.reserve(other.nodes.size());
        for (const auto* n:other.nodes) {
            nodes.emplace_back(new Node(*n));
        }
    }

    void addNode(Node* n) {
        for (Node* node: nodes) {
            if (n->x == node->x && n->y == node->y) {
                return;
            }
        }

        nodes.emplace_back(n);
    }

    Node* findStart(Node* start) {
        for (Node* n: nodes) {
            if (n->x == start->x && n->y == start->y) {
                removeNode(n);
                return n;
            }
        }

        return nullptr;
    }

    Node* findSmallestNode() {
        std::size_t lowest = SIZE_MAX;
        Node* cur{};
        for (Node* n: nodes) {
            if (n->value >= 0 && n->value < lowest) {
                lowest = n->value;
                cur = n;
            }
        }

        removeNode(cur);

        return cur;
    }

    void removeNode(Node* node) {
        std::size_t index = 0;
        for(std::size_t i=0; i < nodes.size(); ++i){
            if (nodes[i]->x == node->x && nodes[i]->y == node->y) {
                index = i;
                break;
            }
        }
        nodes.erase(nodes.begin()+index);
    }
};

Nodelist Node::getNeighbours(const Nodelist& nList, std::size_t maxX, std::size_t maxY) {
    Nodelist neighbours {};
    for (auto n:nList.nodes) {
        //Left
        if (x>0 && (n->x == x-1) && (n->y == y) && n->height <= height+1 && !n->visited)
            neighbours.addNode(n);

        //Up
        if (y>0 && (n->x == x) && (n->y == y-1) && n->height <= height+1 && !n->visited)
            neighbours.addNode(n);

        //Right
        if (x<maxX && (n->x == x+1) && (n->y == y) && n->height <= height+1 && !n->visited)
            neighbours.addNode(n);

        //Down
        if (y<maxY && (n->x == x) && (n->y == y+1) && n->height <= height+1 && !n->visited)
            neighbours.addNode(n);
    }

    return neighbours;
}



static void part1() {
    //std::ifstream infile ("Day12/test.txt");
    std::ifstream infile ("Day12/puzzle.txt");

    std::string line;

    Nodelist nodes{};
    std::size_t row = 0;
    std::size_t maxX = 0;
    std::size_t maxY = 0;

    Node* start = {};
    Node* end = {};

    while (infile >> line) {
        maxX = line.size();
        for (std::string::size_type i = 0; i < line.size(); i++) {
            Node* node = new Node{};
            node->x = i;
            node->y = row;
            if (line[i] == 'S') {
                node->height = 'a' - '0';
                start = node;
            } else if (line[i] == 'E') {
                node->height = 'z' - '0';
                end = node;
                nodes.addNode(node);
            } else {
                node->height = line[i] - '0';
                nodes.addNode(node);
            }
        }
        row++;
        maxY = row;
    }

    Nodelist priority{};
    Nodelist neighbours{};
    start->value = 0;
    start->visited = true;
    priority.addNode(start);
    while(!priority.nodes.empty()) {
        Node* cur = priority.findSmallestNode();
        cur->visited = true;
        if(cur->x == end->x && cur->y == end->y) {
            std::cout << "Steps:" << cur->value << "\n";
            break;
        }
        neighbours = cur->getNeighbours(nodes, maxX, maxY);
        for (auto& n: neighbours.nodes) {
            n->value = cur->value + n->edge;
            priority.addNode(n);
        }
    }

}


static void part2() {
    //std::ifstream infile ("Day12/test.txt");
    std::ifstream infile ("Day12/puzzle.txt");

    std::string line;

    Nodelist nodes{};
    std::size_t row = 0;
    std::size_t maxX = 0;
    std::size_t maxY = 0;

    Node* end = {};

    Nodelist possibleStarts{};


    while (infile >> line) {
        maxX = line.size();
        for (std::string::size_type i = 0; i < line.size(); i++) {
            Node* node = new Node{};
            node->x = i;
            node->y = row;
            if (line[i] == 'S' || line[i] == 'a') {
                node->height = 'a' - '0';
                possibleStarts.addNode(node);
                nodes.addNode(node);
            } else if (line[i] == 'E') {
                node->height = 'z' - '0';
                end = node;
                nodes.addNode(node);
            } else {
                node->height = line[i] - '0';
                nodes.addNode(node);
            }
        }
        row++;
        maxY = row;
    }


    std::set<std::size_t>stepsOfAllRouts{};
    for (auto& s: possibleStarts.nodes) {
        Node* start = nodes.findStart(s);
        Nodelist priority{};
        Nodelist neighbours{};
        start->value = 0;
        start->visited = true;
        priority.addNode(start);
        while(!priority.nodes.empty()) {
            Node* cur = priority.findSmallestNode();
            cur->visited = true;
            if(cur->x == end->x && cur->y == end->y) {
                stepsOfAllRouts.insert(cur->value);
                for (auto& n: nodes.nodes) {
                    n->value = SIZE_MAX;
                    n->visited = false;
                }

                break;
            }
            neighbours = cur->getNeighbours(nodes, maxX, maxY);
            for (auto& n: neighbours.nodes) {
                n->value = cur->value + n->edge;
                priority.addNode(n);
            }
        }
    }
    std::cout << "Shortest Path:" << *(stepsOfAllRouts.begin()) << "\n";
}



void day12() {
    std::cout << "Day12:\n";
    part1();
    part2();
    std::cout << "--------" << std::endl;
}