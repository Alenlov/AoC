#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>



int main(int argc, char const *argv[])
{
    int serialNumber{0};
    if (argc > 1)
    {
       serialNumber = std::stoi(argv[1]);
    }
    else
    {
        return -1;
    }
    std::cout << serialNumber << std::endl;
    int maxX{300}, maxY{300};
    int sizeTotalPower[maxX][maxY];
    std::map<std::pair<int,int>, int> powerLevel;
    for (int y = 0; y < maxY; y++)
    {
        for (int x = 0; x < maxX; x++)
        {
            int rackID = x + 10;
            int power = rackID*y + serialNumber;
            power *= rackID;
            power /= 100;
            power %= 10;
            power -= 5;
            powerLevel[{x,y}] = power;
            int powerL = powerLevel[{x,y}];
            if (x-1 >= 0) powerL += sizeTotalPower[x-1][y];
            if (y-1 >= 0) powerL += sizeTotalPower[x][y-1];
            if (x-1 >= 0 && y-1 >= 0) powerL -= sizeTotalPower[x-1][y-1];
            sizeTotalPower[x][y] = powerL;
        }
    }
    std::pair<int,int> maxSquare, maxSquareA;
    int maxSize{0};
    int maxPowerLevel{-100}, maxPowerLevelA{-100};
    
    for (int size = 1; size <= 300; size ++)
    {
        //std::cout << size << std::endl;
        for (int y = 0; y < maxY - (size - 1); y++)
        {
            for (int x = 0; x < maxX - (size - 1); x++)
            {
                int totPower = sizeTotalPower[x+size-1][y+size-1];
                if (x-1 >= 0) totPower -= sizeTotalPower[x-1][y+size-1];
                if (y-1 >= 0) totPower -= sizeTotalPower[x+size-1][y-1];
                if (x-1 >= 0 && y-1 >= 0) totPower += sizeTotalPower[x-1][y-1];


                if (totPower > maxPowerLevel)
                {
                    maxPowerLevel = totPower;
                    maxSquare = {x,y};
                    maxSize = size;
                }
                if (size == 3)
                {
                    if (totPower > maxPowerLevelA)
                    {
                        maxPowerLevelA = totPower;
                        maxSquareA = {x,y};
                    }
                }
            }
        }
    }
    
    std::cout << "Answer part A: " << maxSquareA.first << "," <<maxSquareA.second << std::endl;
    std::cout << "Answer part B: " << maxSquare.first << "," << maxSquare.second << "," << maxSize << std::endl;

}   

