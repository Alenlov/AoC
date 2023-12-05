#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
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
    long freq{0};
    std::vector<std::pair<char, long>> changes;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            char sign = line[0];
            long val = std::stol(line.substr(1,line.size()-1));
            changes.push_back({sign,val});
            if (line[0] == '+')
            {
                freq += std::stol(line.substr(1,line.size()-1) );
            }
            else
            {
                freq -= std::stol(line.substr(1,line.size()-1) );
            }
        }
    }
    myfile.close();
    std::cout << "Answer part A: " << freq << std::endl;
    std::unordered_set<long> freqs{0};
    freq = 0;
    bool foundSame{false};
    int indx{0};
    while(!foundSame)
    {
        std::pair<char,long> c = changes[indx];
        if (c.first == '+')
        {
            freq += c.second;
        }
        else
        {
            freq -= c.second;
        }
        if (freqs.contains(freq))
        {
            foundSame = true;
        }
        else
        {
            freqs.insert(freq);
            ++indx;
            indx %= changes.size();
        }
    }
    
    std::cout << "Answer part B: " << freq << std::endl; 
}