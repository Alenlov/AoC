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
    std::vector<std::pair<int,int>> positions;
    int minX{1<<30}, minY{1<<30}, maxX{-1}, maxY{-1};
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, ", ");
            int x = std::stoi(split[0]);
            int y = std::stoi(split[1]);
            positions.push_back({x, y});
            if (x < minX) minX = x;
            if (x > maxX) maxX = x;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
        }
    }
    myfile.close();
    int maxDist{10000};
    std::map<std::pair<int,int>,int> sizeOfGrids;
    int sizeOfSafe{0};
    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            int minDist{1<<30}, totDist{0};
            std::vector<int> minIds;
            for (int id = 0; id < positions.size(); id++)
            {
                int dist = abs(x - positions[id].first) + abs(y - positions[id].second);
                if (dist < minDist)
                {
                    minDist = dist;
                    minIds = {id};
                }
                else if (dist == minDist)
                {
                    minIds.push_back(id);
                }
                totDist += dist;
                
                
            }
            if (totDist < maxDist)
            {
                ++sizeOfSafe;
            }
            if(minIds.size() == 1)
            {
                if ( (x == minX) || (x == maxX) || (y == minY) || (y == maxY) )
                {
                    sizeOfGrids[positions[minIds[0]]] = -1;
                }
                else
                {
                    if (sizeOfGrids[positions[minIds[0]]] != -1)
                    {
                        sizeOfGrids[positions[minIds[0]]] += 1;
                    }
                }
            }
        }
    }
    int maxS{0};
    for (auto [p, s] : sizeOfGrids)
    {
        if (s > maxS)
        {
            maxS = s;
        }
    }
    std::cout << "Answer part A: " << maxS << std::endl;
    std::cout << "Answer part B: " << sizeOfSafe << std::endl;
    
}