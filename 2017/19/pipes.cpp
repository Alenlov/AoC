#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

std::set<char> letters{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char turn{'+'};
std::pair<int,int> turnLeft(std::pair<int,int> dir) {return std::make_pair(dir.second, -dir.first);}
std::pair<int,int> turnRight(std::pair<int,int> dir) {return std::make_pair(-dir.second, dir.first);}

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

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    if (argc > 1)
    {
        myfile.open(argv[1]);
    }
    else
    {
        return -1;
    }
    std::vector<std::string> map;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            map.push_back(line);
        }
    }
    myfile.close();
    std::pair<int,int> dir{0,1}, pos{0,0};
    std::size_t startX = map[0].find("|",0);
    pos.first = startX;

    std::cout << pos.first << "," << pos.second << std::endl;
    std::cout << map[pos.second][pos.first] << std::endl;

    std::string ansA{""};
    int numSteps{0};
    bool inMap{true};
    while(inMap)
    {
        pos.first += dir.first;
        pos.second += dir.second;
        ++numSteps;
        if (0 <= pos.second && pos.second <= map.size() && 0 <= pos.first && pos.first <= map[pos.second].length())
        {    
            char newSpot = map[pos.second][pos.first];
            if (newSpot == ' ') 
            {
                inMap = false;
                break;
            }
            
            if (letters.contains(newSpot)){
                std::cout << pos.first << "," << pos.second << " : " << newSpot << " d:" << dir.first << "," << dir.second << std::endl;
                ansA += newSpot;
            }            
            if (newSpot == turn)
            {
                std::pair<int,int> dirL = turnLeft(dir);
                char testSpot = map[pos.second+dirL.second][pos.first+dirL.first];
                if (testSpot != ' ')
                {
                    dir = dirL;
                }
                else
                {
                    dir = turnRight(dir);
                }
            }
        }
        else
        {
            inMap = false;
        }

    }

    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << numSteps << std::endl;
}