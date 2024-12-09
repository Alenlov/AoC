#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <map>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <set>
struct nanobot
{
    long x,y,z,r;
};

struct square
{
    long x,y,z,dx,dy,dz;
};

bool within(nanobot source, nanobot other)
{
    return (abs(source.x-other.x) + abs(source.y-other.y) + abs(source.z-other.z)) <= source.r;
}

bool within(square sq, nanobot bot)
{
    
}

bool overlap(nanobot lhs, nanobot rhs)
{
    return (abs(lhs.x-rhs.x) <= (lhs.r + rhs.r)) && (abs(lhs.y-rhs.y) <= (lhs.r + rhs.r)) && (abs(lhs.z-rhs.z) <= (lhs.r + rhs.r));
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
    long lx{0}, rx{0}, ly{0}, ry{0}, lz{0}, rz{0};
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
                if ((n.x - n.r) < lx) lx = n.x - n.r;
                if ((n.x + n.r) > rx) rx = n.x + n.r;
                if ((n.y - n.r) < ly) ly = n.y - n.r;
                if ((n.y + n.r) > ry) ry = n.y + n.r;
                if ((n.z - n.r) < lz) lz = n.z - n.r;
                if ((n.z + n.r) > rz) rz = n.z + n.r;
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
    
    std::unordered_set<int> allNodes;
    long ansA{0};
    for (int i{0}; i < nanobots.size(); i++)
    {
        if (within(nanobots[maxInd], nanobots[i]))
        {
            ++ansA;
        }
        
    }
    
    std::cout << "Answer part A: " << ansA << std::endl;

    for (long x{lx}; x < rx; x++)
    {

    }

    std::cout << nanobots.size() << std::endl;

}