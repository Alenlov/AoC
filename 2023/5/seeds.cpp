#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <map>

struct range
{
    long fromStart, toStart, length;
};

struct seedRange
{
    long startSeed, length;
};

struct convMap
{
    std::string from, to;
    std::vector<range> ranges;
};

bool inRange(long fromVal, range r)
{
    if ((fromVal >= r.fromStart) && (fromVal < (r.fromStart + r.length) ))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<seedRange> mapRange(seedRange s, std::vector<range> ranges)
{
    std::vector<seedRange> newRange;
    long seedStart = s.startSeed;
    long seedLength = s.length;
    bool seedsLeft{true};
    while(seedsLeft)
    {
        bool foundRange{false};
        long minVal{0};
        if (seedLength == 0) break;
        for (range r : ranges)
        {
            if ((r.fromStart > seedStart))
            {
                if (minVal == 0 || r.fromStart < minVal) minVal = r.fromStart;
            }
             
            if (inRange(seedStart, r))
            {
                foundRange = true;
                long startVal{r.toStart + (seedStart - r.fromStart)};
                seedRange newS;
                newS.startSeed = startVal;
                if (seedLength < (r.fromStart - seedStart) + r.length)
                {
                    newS.length = seedLength;
                    seedsLeft = false;
                }
                else
                {
                    newS.length = (r.fromStart - seedStart) + r.length;
                    seedStart = seedStart + newS.length;
                    seedLength = seedLength - newS.length;
                }
                newRange.push_back(newS);
                break;
            }
        }
        if (!foundRange)
        {
            seedRange newS;
            newS.startSeed = seedStart;
            if (minVal != 0)
            {
                if (seedLength < minVal - seedStart)
                {
                    newS.length = seedLength;
                    seedsLeft = false;
                }
                else
                {
                    newS.length = minVal - seedStart;
                    seedStart = minVal;
                    seedLength = seedLength - newS.length;
                }
            }
            else
            {
                newS.length = seedLength;
                seedsLeft = false;
            }
            newRange.push_back(newS);
        }
    }
    return newRange;
}

long matchVal(long fromVal, std::vector<range> ranges)
{
    for (range r : ranges)
    {
        if (inRange(fromVal, r))
        {
            return r.toStart + (fromVal - r.fromStart);
        }
    }
    return fromVal;

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
    const std::regex seedLine("seeds: (.+)");
    const std::regex mapLine("([a-z]+)-to-([a-z]+) map:");
    std::smatch m;
    std::ifstream myfile;
    std::string line;
    std::vector<long> seeds;
    std::vector<seedRange> seedsB;
    if (argc > 1)
    {
        myfile.open(argv[1]);
    }
    else
    {
        return -1;
    }
    std::map<std::string, convMap> maps;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            if (std::regex_match(line, m, seedLine))
            {
                std::vector<std::string> seed = splitLine(m[1]);
                for (std::string s : seed)
                {
                    seeds.push_back(std::stol(s));
                }
                for (int i{0}; i < seed.size(); i+=2)
                {
                    seedRange s;
                    s.startSeed = std::stol(seed[i]);
                    s.length = std::stol(seed[i+1]);
                    seedsB.push_back(s);
                }
            }
            else if (std::regex_match(line, m, mapLine))
            {
                convMap c;
                c.from = m[1];
                c.to = m[2];
                while(getline(myfile,line))
                {
                    if (line.length() == 0) break;
                    std::vector<std::string> rSplit = splitLine(line, " ");
                    range r;
                    r.fromStart = std::stol(rSplit[1]);
                    r.toStart = std::stol(rSplit[0]);
                    r.length = std::stol(rSplit[2]);
                    c.ranges.push_back(r);
                }
                maps[c.from] = c;
            }
            
            
        }
    }
    myfile.close();
    std::string nextMap{"seed"};
    while (nextMap != "location")
    {
        std::vector<long> newSeeds;
        for (long s : seeds)
        {
            newSeeds.push_back(matchVal(s, maps[nextMap].ranges));
        }
        nextMap = maps[nextMap].to;
        seeds = newSeeds;
    }
    long ansA = seeds[0];
    for (long s : seeds)
    {
        if (s < ansA) ansA = s;
    }
    std::cout << "Answer part A: " << ansA << std::endl;
    nextMap = "seed";
    
    while (nextMap != "location")
    {
        std::vector<seedRange> newSeeds;
        for (seedRange s : seedsB)
        {
            //t << s.startSeed << " " << s.startSeed+s.length-1 << " " << s.length << std::endl;
            for (seedRange newS : mapRange(s, maps[nextMap].ranges))
            {
                newSeeds.push_back(newS);
            }
        }
        nextMap = maps[nextMap].to;
        seedsB = newSeeds;
    }
    long ansB = seedsB[0].startSeed;
    for (auto s : seedsB)
    {
    
        if (s.startSeed < ansB) ansB = s.startSeed;
    }
    std::cout << "Answer part B: " << ansB << std::endl;
}