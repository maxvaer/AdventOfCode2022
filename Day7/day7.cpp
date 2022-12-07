#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>

struct Node
{
    int iterateTreePart2(int spaceToFree) {
        if (!isFolder)
            return INT_MAX;

        int smallest = INT_MAX;
        for (Node *c: child) {
             int result = c->iterateTreePart2(spaceToFree);
             if (result < smallest && result >= spaceToFree)
                 smallest = result;
        }

        int cFolderSize = this->folderSize();
        if (cFolderSize >= spaceToFree && cFolderSize <= smallest)
            return cFolderSize;


        return smallest;
    }

    int iterateTreePart1() {
        if (!isFolder)
            return 0;

        int sum = 0;
        int cFolderSize = this->folderSize();
        if (cFolderSize <= 100000)
            sum += cFolderSize;

        for (Node *c: child) {
            sum += c->iterateTreePart1();
        }

        return sum;
    }

    int folderSize() {
        int sum = 0;
        if (!isFolder) {
            return size;
        }

        for (Node *c: child) {
            sum += c->folderSize();
        }

        return sum;
    }

    std::string key;
    bool isFolder{};
    int size{};
    std::vector<Node *>child;
    Node *parent{};
};

Node *newNode(std::string key, Node *parent)
{
    Node *temp = new Node;
    temp->parent = parent;
    temp->isFolder = true;
    temp->key = std::move(key);
    return temp;
}

Node *newNode(std::string key, int size)
{
    Node *temp = new Node;
    temp->isFolder = false;
    temp->size = size;
    temp->key = std::move(key);
    return temp;
}

static void part1() {
    //std::ifstream infile ("Day7/test.txt");
    std::ifstream infile ("Day7/puzzle.txt");
    std::string line;

    Node *root {};
    Node *current{};

    while (std::getline(infile, line)){
        std::istringstream inStream(line);
        if (line == "$ cd /") {
            Node *newFolder = newNode("/", nullptr);
            current = newFolder;
            root = newFolder;
            continue;
        }

        if (line.starts_with("$ cd")) {
            std::string del;
            std::string arg;
            inStream >> del >> del >> arg;
            //Switch to prev folder
            if(arg == "..") {
                current = current->parent;
            } else {
                //Create new Folder
                Node *newFolder = newNode(arg, current);
                current->child.push_back(newFolder);
                current = newFolder;
            }
        }

        if (!(line.starts_with("dir") || line.starts_with("$"))) {
            int size = 0;
            std::string fileName;

            inStream >> size >> fileName;
            Node *newFile = newNode(fileName, size);
            current->child.push_back(newFile);
        }

    }

    std::cout << "Sum:" << root->iterateTreePart1() << "\n";

    int fsSpace = 70000000;
    int updateSpace = 30000000;
    int unUsedSpace = fsSpace - root->folderSize();
    int spaceToFree = updateSpace - unUsedSpace;
    std::cout << "Smallest Folder:" << root->iterateTreePart2(spaceToFree) << "\n";
}

void day7() {
    std::cout << "Day7:\n";
    part1();
    std::cout << "--------" << std::endl;
}