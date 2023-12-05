#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <unordered_set>

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
    std::unordered_set<int> claimIds;
    std::map<std::pair<int,int>,std::vector<int>> claims;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            std::vector<std::string> split1 = splitLine(line," @ ");
            std::vector<std::string> split2 = splitLine(split1[1],": ");
            std::vector<std::string> startSplit = splitLine(split2[0],",");
            std::vector<std::string> sizeSplit = splitLine(split2[1],"x");
            int sX = std::stoi(startSplit[0]), sY = std::stoi(startSplit[1]);
            int width = std::stoi(sizeSplit[0]), height = std::stoi(sizeSplit[1]);
            int id = std::stoi(split1[0].substr(1,-1));
            claimIds.insert(id);
            for (int w = 0; w < width; w++)
            {
                for (int h = 0; h < height; h++)
                {
                    claims[{sX+w,sY+h}].push_back(id);
                }
            }
        }
    }
    myfile.close();
    int overlaps{0};
    for (auto [p, n] : claims)
    {
        if(n.size()>1)
        {
            overlaps++;
            if (claimIds.size() > 1)
            {
                for (int id : n)
                {
                    claimIds.erase(id);
                }
            }
        }
    }
    std::cout << "Answer part A: " << overlaps << std::endl;
    std::cout << "Answer part B: " << *claimIds.begin() << std::endl;
}