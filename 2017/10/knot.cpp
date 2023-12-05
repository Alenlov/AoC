#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include <fmt/format.h>
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
    int size{256};
    if (argc > 1)
    {
        myfile.open(argv[1]);

        
    }
    else
    {
        return -1;
    }
    std::vector<int> hash(size);
    for (int i = 0; i < size; i++) hash[i] = i;
    if (myfile.is_open())
    {
        getline(myfile,line);
    }
    myfile.close();
    std::vector<int> lengths;
    for(std::string s : splitLine(line, ",")) lengths.push_back(std::stoi(s));
    int skip{0}, pos{0};
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
        for (int h : hash) std::cout << h << " ";
        std::cout << std::endl;
    }

    std::cout << "Answer part A: " << hash[0]*hash[1] << std::endl;

    std::vector<int> hashB(size);
    for (int i = 0; i < size; i++) hashB[i] = i;
    std::vector<int> lengthsB;
    for(char c : line) lengthsB.push_back(int(c));
    lengthsB.push_back(17);
    lengthsB.push_back(31);
    lengthsB.push_back(73);
    lengthsB.push_back(47);
    lengthsB.push_back(23);
    skip = 0;
    pos = 0;
    for (int round = 0; round < 64; round++) {
        for (int l : lengthsB)
        {
            std::vector<int> toFlip(l);
            for (int i = 0; i < l; i++) 
            {
                toFlip[l-1-i] = hashB[(pos+i)%size];
            }
            for (int i = 0; i < l; i++) 
            {
                hashB[(pos+i)%size] = toFlip[i];
            }
            pos += l + skip;
            pos %= size;
            skip++;
        }
    }
    std::string hashString{""};
    for (int j = 0; j < 16; j++)
    {
        int val = hashB[(j*16)];
        for (int i = 1; i < 16; i++)
        {   
            val = val ^ hashB[(j*16)+i];
        }
        std::string hexString = fmt::format("{:x}", val);
        if (hashString.length() == 1) 
        {
            hashString += "0" + hexString;
        }
        else
        {
            hashString += hexString;
        }
        
    }
    std::cout << "Answer part B: " << hashString << " : " << hashString.size() << std::endl;
   
    
}