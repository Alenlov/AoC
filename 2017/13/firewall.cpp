#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

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
    std::map<int,int> scanners;
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
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, ": ");
            scanners[std::stoi(split[0])] = std::stoi(split[1]);
        }
        
    }
    myfile.close();
    int penalty{0};
    for (auto [steps, depth] : scanners)
    {
        int cycle{0};
        cycle = depth*2 - 2;
        if (steps % cycle == 0)
        {
            penalty += steps*depth;
        }
    }
    std::cout << "Answer part A: " << penalty << std::endl;

    int delay{0};
    bool caught{true};
    while(caught)
    {
        caught = false;
        delay += 1;
        for (auto [steps, depth] : scanners)
        {
            int cycle{0};
            cycle = depth*2 - 2;
            if ((steps+delay) % cycle == 0)
            {
                caught = true;
                break;
            }
        }
    }
    
    std::cout << "Answer part B: " << delay << std::endl;
}