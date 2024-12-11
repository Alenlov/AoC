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
#include <queue>
#include <bit>

struct nanobot
{
    long x,y,z,r;
};


struct square
{
    long x,y,z,d;
    long num;
    bool operator<(const square& rhs) const
    {
        if (num != rhs.num)
        {
            return num < rhs.num;
        } else {
            return (abs(x)+abs(y)+abs(z)) > (abs(rhs.x)+abs(rhs.y)+abs(rhs.z));
        }
    }
};

bool within(nanobot source, nanobot other)
{
    return (abs(source.x-other.x) + abs(source.y-other.y) + abs(source.z-other.z)) <= source.r;
}

bool within(nanobot source, long x, long y, long z)
{
    return (abs(source.x-x) + abs(source.y-y) + abs(source.z-z)) <= source.r;
}

bool within(square sq, long x, long y, long z)
{
    return (sq.x <= x && x <= (sq.x + sq.d)) && (sq.y <= y && y <= (sq.y + sq.d)) && (sq.z <= z && z <= (sq.z + sq.d));
}

bool within(square sq, nanobot bot)
{
    // Check each corner of bot
    for (int d{-1}; d <= 1; d+=2)
    {
        if(within(sq, bot.x + d*bot.r, bot.y, bot.z)) return true;
        if(within(sq, bot.x, bot.y + d*bot.r, bot.z)) return true;
        if(within(sq, bot.x, bot.y, bot.z + d*bot.r)) return true;
    }
    // Check center of bot
    if(within(sq, bot.x, bot.y, bot.z)) return true;
    // Check corners of cube
    for(int dx = 0; dx <= 1; dx++)
    {
        for(int dy = 0; dy <= 1; dy++)
        {
            for(int dz = 0; dz <= 1; dz++)
            {
                if(within(bot, sq.x + dx*sq.d, sq.y + dy*sq.d, sq.z + dz*sq.d)) return true;
            }
        }
    }

    return false;
}

long countWithin(square sq, std::vector<nanobot> nanobots) 
{
    //std::cout << "SQUARE" << std::endl;
    //std::cout << sq.x << "," << sq.y << "," << sq.z << " : " << sq.d << std::endl;

    long counter{0};
    for (auto bot : nanobots)
    {
        if( within(sq, bot))
        {
            //std::cout << bot.x << "," << bot.y << "," << bot.z << " : " << bot.r << std::endl;
            ++counter;
        }
    }
    return counter;
}


std::vector<square> split(square sq)
{
    long newD = sq.d/2;
    std::vector<square> newSquares;
    for(int dx = 0; dx <= 1; dx++)
    {
        for(int dy = 0; dy <= 1; dy++)
        {
            for(int dz = 0; dz <= 1; dz++)
            {
                square newSq;
                newSq.d = newD;
                newSq.x = sq.x + dx*newD;
                newSq.y = sq.y + dy*newD;
                newSq.z = sq.z + dz*newD;
                newSquares.push_back(newSq);
            }
        }
    }
    return newSquares;
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

    square sq = {0,0,0,8};
    long maxDist{rx - lx};
    if ((ry-ly)>maxDist) maxDist = ry-ly;
    if ((rz-lz)>maxDist) maxDist = rz-lz;

    long powerOf2{1};
    while(powerOf2 < maxDist)
    {
        powerOf2 = powerOf2 << 1;
    }
    square init = {-(powerOf2/2),-(powerOf2/2),-(powerOf2/2),powerOf2};
    init.num = countWithin(init, nanobots);
    long ansB{0};
    std::priority_queue<square> squares;
    squares.push(init);
    bool found{false};
    while(!found)
    {
        square h = squares.top();
        //std::cout << h.x << "," << h.y << "," << h.z << " - " << h.d << " num " << h.num << std::endl;

        squares.pop();
        if(h.d==1)
        {
            long maxCount{0};
            for(int dx = 0; dx <= 1; dx++)
            {
                for(int dy = 0; dy <= 1; dy++)
                {
                    for(int dz = 0; dz <= 1; dz++)
                    {
                        //std::cout << "Checking point " << h.x + dx*h.d << "," << h.y + dy*h.d << "," << h.z + dz*h.d << std::endl;
                        long count{0};
                        for (auto bot : nanobots)
                        {
                            if(within(bot, h.x + dx*h.d, h.y + dy*h.d, h.z + dz*h.d))
                            {
                                //std::cout << "Within: " << bot.x << "," << bot.y << "," << bot.z << " : " << bot.r << std::endl;
                                ++count;
                            }
                        }
                        long newAnsB = abs(h.x+dx*h.d) + abs(h.y+dy*h.d) + abs(h.z+dz*h.d);
                        if (count > maxCount)
                        {
                            maxCount = count;
                            ansB = newAnsB;
                        }
                        else if (count == maxCount)
                        {
                            if (newAnsB < ansB)
                            {
                                ansB = newAnsB;
                            }
                        }
                    }
                }
            }
            found = true;
        }
        else
        {
            //std::cout << "Pushing the followinng: " << std::endl;
            for(auto s : split(h))
            {
                s.num = countWithin(s, nanobots);
                //std::cout << s.x << "," << s.y << "," << s.z << " - " << s.d << " num " << s.num << std::endl;
        
                squares.push(s);
            }
            //std::cout << " --- " << std::endl;
        }
    }
    std::cout << "Answer part B: " << ansB << std::endl;
}