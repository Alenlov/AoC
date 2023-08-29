#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <deque>

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
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            
            if(line == "") {
                moving = true;
            }
            if(! moving) {
                //std::cout << line << std::endl;
                for (int i = 0; i < 9; i++) {
                    std::size_t indx = 1 + i*4;
                    //std::cout << line[indx] << " ";
                    char toPlace = line[indx];
                    if (int(toPlace) > 64) {
                        stacksForA[i].push_back(toPlace);
                        stacksForB[i].push_back(toPlace);
                    }
                }
                //std::cout << std::endl;
            } else if (line.length() > 2)
            {
                std::vector<std::string> lineSplit = splitLine(line);
                int numToMove = std::stoi(lineSplit[1]);
                int from = std::stoi(lineSplit[3]);
                int to = std::stoi(lineSplit[5]);
                std::deque<char> intermediate;
                for(int i = 0; i < numToMove; i++) {
                    stacksForA[to-1].push_front(stacksForA[from-1].front());
                    stacksForA[from-1].pop_front();
                    intermediate.push_front(stacksForB[from-1].front());
                    stacksForB[from-1].pop_front();
                }
                for(char c : intermediate) {
                    stacksForB[to-1].push_front(c);
                }
                intermediate.clear();
            }
            
        }
    }
    myfile.close();
  /*   for(std::deque<char> s : stacksForA) {
        for(char c : s) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

    } */
     for(std::deque<char> s : stacksForB) {
        for(char c : s) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

    }
    std::cout << "Answer problem a : ";
    for(std::deque<char> s : stacksForA) {
        std::cout << s.front();
    }
    std::cout << std::endl;
    std::cout << "Answer problem b : ";
    for(std::deque<char> s : stacksForB) {
        std::cout << s.front();
    }
    std::cout << std::endl;
}