#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <stdlib.h>

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

struct hecs
{
    int r{0}, s{0}, q{0};
};

std::map<std::string, hecs> directions = {{"n",{0,1,-1}}, {"s",{0,-1,1}}, {"ne", {1,0,-1}}, {"sw",{-1,0,1}}, {"nw",{-1,1,0}}, {"se",{1,-1,0}}};

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
    if (myfile.is_open())
    {
        getline(myfile,line);
    }
    myfile.close();
    int maxDist{0};
    hecs h({0,0,0});
    for (std::string s : splitLine(line, ","))
    {
        hecs d = directions[s];
        h.q += d.q;
        h.r += d.r;
        h.s += d.s;
        if (abs(h.q) > maxDist) maxDist = abs(h.q);
        if (abs(h.r) > maxDist) maxDist = abs(h.r);
        if (abs(h.s) > maxDist) maxDist = abs(h.s);
    }


    int ansA{0};

    if (abs(h.q) > ansA) ansA = abs(h.q);
    if (abs(h.r) > ansA) ansA = abs(h.r);
    if (abs(h.s) > ansA) ansA = abs(h.s);

    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << maxDist << std::endl;
    
}