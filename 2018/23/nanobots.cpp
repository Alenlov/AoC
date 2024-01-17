#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <map>

struct nanobot
{
    long x,y,z,r;
};

struct range
{
    long min, max;
    std::strong_ordering operator<=>(const range& other) const
    {
        return std::tie(min, max) <=> std::tie(other.min, other.max);
    }
};


bool within(nanobot source, nanobot other)
{
    return (abs(source.x-other.x) + abs(source.y-other.y) + abs(source.z-other.z)) <= source.r;
}

std::pair<int,int> operator+(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
    return {lhs.first+rhs.first,lhs.second+rhs.second};
}

std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos && (indx < line.length()))
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

void fixRanges(std::map<range,int>& ranges)
{
    
}

int main(int argc, char const *argv[])
{
    const std::regex reg("pos=<([-0-9]+),([-0-9]+),([-0-9]+)>, r=([0-9]+)");
    std::smatch m;
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
    std::vector<nanobot> nanobots;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            if (std::regex_match(line, m, reg))
            {
                
                nanobot n;
                n.x = std::stol(m[1]);
                n.y = std::stol(m[2]);
                n.z = std::stol(m[3]);
                n.r = std::stol(m[4]);
                nanobots.push_back(n);
            }
        }
    }
    myfile.close();
    long maxR{0}, maxInd{0};
    for (int i{0}; i < nanobots.size(); i++)
    {
        if (nanobots[i].r > maxR)
        {
            maxR = nanobots[i].r;
            maxInd = i;
        }
    }

    std::map<range, int> x, y, z;
    long ansA{0};
    for (int i{0}; i < nanobots.size(); i++)
    {
        range rx{.min = nanobots[i].x-nanobots[i].r, .max = nanobots[i].x+nanobots[i].r};
        x[rx] = 1;
        range ry{.min = nanobots[i].y-nanobots[i].r, .max = nanobots[i].y+nanobots[i].r};
        y[ry] = 1;
        range rz{.min = nanobots[i].y-nanobots[i].r, .max = nanobots[i].y+nanobots[i].r};
        z[rz] = 1;
        if (within(nanobots[maxInd], nanobots[i]))
        {
            ++ansA;
        }
    }

    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << nanobots.size() << std::endl;

}