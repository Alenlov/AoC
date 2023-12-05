#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

std::pair<int,int> turn(std::pair<int,int> dir, char d)
{
    std::pair<int,int> newDir;
    if (d == 'l')
    {
        newDir.first = dir.second;
        newDir.second = -dir.first;
    }
    else if (d == 'r')
    {
        newDir.first = -dir.second;
        newDir.second = dir.first;
    }

    return newDir;
}

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
    std::set<std::pair<int,int>> infected, infectedB, weakened, flagged;
    int y{0}, x{0};
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            x = 0;
            for(char c : line)
            {
                if(c == '#') infected.insert({x,y});
                if(c == '#') infectedB.insert({x,y});
                ++x;
            }
            ++y;
        }
        
    }
    myfile.close();
    
    std::pair<int,int> pos = {x/2, y/2};
    std::pair<int,int> dir{0,-1};
    int maxSteps{10000}, infections{0};
    for(int burst = 0; burst < maxSteps; burst++)
    {
        if(infected.contains(pos))
        {
            dir = turn(dir,'r');
            infected.erase(pos);
            pos.first = pos.first + dir.first;
            pos.second = pos.second + dir.second;
        }
        else
        {
            dir = turn(dir,'l');
            infected.insert(pos);
            pos.first = pos.first + dir.first;
            pos.second = pos.second + dir.second;
            ++infections;
        }
    }
    std::cout << "Answer part A: " << infections << std::endl;

    pos = {x/2, y/2};
    dir = {0,-1};
    int maxBursts{10000000}, infectionsB{0};
    for(int burst = 0; burst < maxBursts; burst++)
    {
        if(infectedB.contains(pos))
        {
            dir = turn(dir,'r');
            infectedB.erase(pos);
            flagged.insert(pos);
        }
        else if (flagged.contains(pos))
        {
            dir = turn(dir,'r');
            dir = turn(dir,'r');
            flagged.erase(pos);
        }
        else if (weakened.contains(pos))
        {
            weakened.erase(pos);
            infectedB.insert(pos);
            ++infectionsB;
        }
        else
        {
            dir = turn(dir,'l');
            weakened.insert(pos);
        }
        pos.first = pos.first + dir.first;
        pos.second = pos.second + dir.second;
    }
    std::cout << "Answer part B: " << infectionsB << std::endl;
}