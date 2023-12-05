#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fmt/format.h>
#include <set>
#include <queue>

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

std::string knotHash(std::string input)
{   
    int size{256};
    std::vector<int> hash(size);
    for (int i = 0; i < size; i++) hash[i] = i;
    std::vector<int> lengths;
    for(char c : input) lengths.push_back(int(c));
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);
    int skip{0}, pos{0};

    for (int round = 0; round < 64; round++) {
        for (int l : lengths)
        {
            std::vector<int> toFlip(l);
            for (int i = 0; i < l; i++) 
            {
                toFlip[l-1-i] = hash[(pos+i)%size];
            }
            for (int i = 0; i < l; i++) 
            {
                hash[(pos+i)%size] = toFlip[i];
            }
            pos += l + skip;
            pos %= size;
            skip++;
        }
    }
    std::string hashString{""};
    for (int j = 0; j < 16; j++)
    {
        int val = hash[(j*16)];
        for (int i = 1; i < 16; i++)
        {   
            val = val ^ hash[(j*16)+i];
        }
        std::string hexString = fmt::format("{:02X}", val);
        hashString += hexString;
        
        
    }
    return hashString;
}

std::string knotHashBin(std::string input)
{   
    int size{256};
    std::vector<int> hash(size);
    for (int i = 0; i < size; i++) hash[i] = i;
    std::vector<int> lengths;
    for(char c : input) lengths.push_back(int(c));
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);
    int skip{0}, pos{0};

    for (int round = 0; round < 64; round++) {
        for (int l : lengths)
        {
            std::vector<int> toFlip(l);
            for (int i = 0; i < l; i++) 
            {
                toFlip[l-1-i] = hash[(pos+i)%size];
            }
            for (int i = 0; i < l; i++) 
            {
                hash[(pos+i)%size] = toFlip[i];
            }
            pos += l + skip;
            pos %= size;
            skip++;
        }
    }
    std::string hashString{""};
    for (int j = 0; j < 16; j++)
    {
        int val = hash[(j*16)];
        for (int i = 1; i < 16; i++)
        {   
            val = val ^ hash[(j*16)+i];
        }
        std::string hexString = fmt::format("{:08B}", val);
        hashString += hexString;
        
        
    }
    return hashString;
}

std::set<std::pair<int,int>> dirs{ {1,0}, {-1,0}, {0,1}, {0,-1}  };

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    if (argc > 1)
    {
        line = argv[1];
    }
    else
    {
        return -1;
    }
    int numSquares{0};
    std::set<std::pair<int,int>> squares;
    std::vector<std::string> hashes(128);
    for (int i = 0; i < 128; i++)
    {
        std::string binHash = knotHashBin(line + "-" + std::to_string(i));
        for (int j = 0; j < binHash.size(); j++)
        {
            char c = binHash[j];
            if (int(c) == int('1'))
            {
                numSquares++;
                squares.insert(std::make_pair(i,j));
            }
        }
        hashes[i] = binHash;
    }
    std::cout << "Answer part A: " << numSquares << std::endl;
    int numGroups{0};
    while(squares.size() > 0)
    {
        numGroups++;
        std::set<std::pair<int,int>> thisGroup;
        std::pair<int,int> head = *squares.begin();
        squares.erase(head);
        thisGroup.insert(head);
        std::queue<std::pair<int,int>> heads;
        heads.push(head);
        while(!heads.empty())
        {
            head = heads.front();
            heads.pop();
            for (std::pair<int,int> d : dirs)
            {
                if (squares.contains({head.first+d.first, head.second+d.second}))
                {
                    if (!thisGroup.contains({head.first+d.first, head.second+d.second}))
                    {
                        thisGroup.insert({head.first+d.first, head.second+d.second});
                        heads.push({head.first+d.first, head.second+d.second});
                        squares.erase({head.first+d.first, head.second+d.second});
                    }
                }
            }
        }
    }

    std::cout << "Answer part B: " << numGroups << std::endl;
}