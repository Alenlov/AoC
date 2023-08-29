#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <deque>
#include "directory.h"

std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos)
    {
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0)
        {
            vectorOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }
    return vectorOfStrings;
}

bool uniqueChars(std::string input) {
    for( int i = 0; i < input.length()-1; i ++) {
        if(input.find(input[i], i+1) != std::string::npos ) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    bool moving = false;
    std::vector<std::deque<char>> stacksForA(9);
    std::vector<std::deque<char>> stacksForB(9);
    Directory * head = NULL;
    if (myfile.is_open()) {
        while(getline(myfile,line)) 
        {
            std::vector<std::string> instructions = splitLine(line);
            if (instructions[0] == "$") {
                if (instructions[1] == "cd") {
                    if (head == NULL) {
                        head = new Directory(instructions[2]);
                    } else if (instructions[2] == ".." ) {
                        head = head->getRoot();
                    } else {
                        head = head->getSubDirByName(instructions[2]);
                    }
                } else if (instructions[1] == "ls") {

                }
            } else if (instructions[0] == "dir") {
                head->addSubDir(instructions[1]);
            } else {
                head->addFile(instructions[1], std::stoi(instructions[0]));
            }
        }
    }
    /* Directory * d = new Directory("/");
    d->addFile("b.txt", 14848514);
    d->addFile("c.dat", 8504156);
    d->addSubDir("a");
    d->addSubDir("e");
    d->setSize();
    d->print(); */
    // find root:
    while( head->getRoot() != NULL) {
        head = head->getRoot();
    }
    head->setSize();
    std::cout << "Total size of small directories is " << head->calcSmall() << std::endl;

    int maxSize = 70000000;
    int updateSize = 30000000;
    int spaceToFree = updateSize - (maxSize - head->getSize());
    int smallest = maxSize;
    std::deque<Directory *> toVisit;
    toVisit.push_back(head);
    while(!toVisit.empty()) {
        Directory * dir = toVisit.front();
        toVisit.pop_front();
        if(dir->getSize() > spaceToFree && dir->getSize() < smallest) {
            smallest = dir->getSize();
        }
        std::map<std::string, Directory *> subDirs = dir->getSubDir();
        for(auto const& [k, v] :  subDirs) {
            toVisit.push_back(v);
        }
    }

    std::cout << "The directory with minimal necessary space has size " << smallest << std::endl;

}