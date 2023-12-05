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

bool isSymb(char c)
{
    return !(c == '.' || (c >= '0' && c <= '9'));
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
    std::vector<std::string> schematic;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            schematic.push_back(line);
        }
    }
    myfile.close();
    bool buildingNum{false};
    int startX{0};
    long sumA{0}, sumB{0};
    std::map<std::pair<int,int>, std::vector<int>> gears;
    std::string number{""};
    for (int y{0}; y < schematic.size(); y++)
    {
        for (int x{0}; x < schematic[y].length(); x++)
        {
            char c = schematic[y][x];
            if (c >= '0' && c <= '9')
            {
                if(buildingNum)
                {
                    number += c;
                }
                else if (!buildingNum)
                {
                    buildingNum = true;
                    startX = x;
                    number += c;
                }   
            }
            if ((buildingNum && (c < '0' || c > '9')) || (buildingNum && (x + 1 >= schematic[y].length())))
            {
                buildingNum = false;
                int num = std::stoi(number);
                number = "";
                // kolla om bredvid symbol
                bool nextToSymb{false};
                for (int dx{startX-1}; dx <= x; dx++)
                {
                    for (int dy{y-1}; dy <= y+1; dy++)
                    {
                        if ((0<=dy)&&(dy<schematic.size())&&(0<=dx)&&(dx<schematic[y].length()))
                        {
                            if (isSymb(schematic[dy][dx]))
                            {
                                if (schematic[dy][dx] == '*')
                                {
                                    gears[{dy,dx}].push_back(num);
                                }
                                nextToSymb = true;
                            }
                        }
                    }
                }
                if (nextToSymb)
                {
                    sumA += num;
                }
            }
        }
    }

    for (auto const [k,v] : gears)
    {
        if (v.size() == 2)
        {
            int ratio{1};
            for (int g : v)
            {
                ratio *= g;
            }
            sumB += ratio;
        }
    }
    std::cout << "Answer part A: " << sumA << std::endl;
    std::cout << "Answer part B: " << sumB << std::endl;
}