#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
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

std::string toHash(std::vector<std::set<std::string>> floorPlan)
{
    return "";
}

std::vector<std::set<std::string>> fromHash(std::string hashString)
{
    std::vector<std::set<std::string>> floorPlan;

    return floorPlan;
}

bool isValid(std::vector<int> state, int numChips)
{
    bool res = true;
    for (int i = 0; i < numChips; i++)
    {
        if (state[i] != state[numChips+i]) 
        {
            for (int j = 0; j < numChips; j++)
            {
                if (state[i] == state[numChips +j] && i != j) {
                    return(false);
                }
            }

        }
    }
    return(res);
    
}

int main(int argc, char* argv[])
{
    std::ifstream myfile;
    std::string line;

    std::vector<int> state = { 1, 3, 3, 3, 3, 1, 2, 2, 2, 2, 1, 0}; 
    std::set<std::vector<int>> visited;
    std::deque<std::vector<int>> toVisit;
    visited.insert(state);
    toVisit.push_back(state);
    int numChips = 5;
    if(isValid(state, numChips))
    {
        std::cout << "Fungerar!\n";
    }
    else
    {
        std::cout << "Fungerar ej!\n";
    }
    /*myfile.open(argv[1]);
    if (myfile.is_open())
    {
        int floor = 0;
        while(getline(myfile,line))
        {
            floor += 1;
            std::vector<std::string> lineVec = splitLine(line);
            for(std::size_t idx = 0; idx < lineVec.size(); idx++)
            {
                std::string currentPart = lineVec.at(idx);
                std::size_t genIdx = currentPart.find("generator",0);
                std::size_t micIdx = currentPart.find("microchip",0);
                if(genIdx == 0)
                {
                    // We got a generator
                    std::string generatorName = lineVec.at(idx-1);
                    std::cout << "Generator: " << generatorName << " on floor " << floor << std::endl;
                }
                else if (micIdx == 0)
                {
                    // We got a microchip
                    std::string microchipName = lineVec.at(idx-1);
                    std::size_t dashId = microchipName.find("-",0);
                    microchipName = microchipName.substr(0,dashId);
                    std::cout << "Microchip: " << microchipName << " on floor " << floor << std::endl;

                }
            }

        }
    }*/
}