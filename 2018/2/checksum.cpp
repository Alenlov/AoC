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
    long countTwo{0}, countThree{0};
    std::vector<std::string> ids;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            ids.push_back(line);
            int two{0}, three{0};
            std::map<char,int> charCount;
            for (char c : line)
            {
                charCount[c] += 1;
            }
            for (auto [c, i] : charCount)
            {
                if (i == 2) two = 1;
                if (i == 3) three = 1;
            }
            countTwo += two;
            countThree += three;
        }
    }
    myfile.close();

    std::cout << "Answer part A: " << countTwo * countThree << std::endl;
    for (int i = 0; i < ids.size(); i++)
    {
        std::string s1{ids[i]};
        for (int j = i+1; j < ids.size(); j++)
        {
            std::string s2{ids[j]};
            int numErr{0};
            for (int k = 0; k < s1.size(); k++)
            {
                if (s1[k] != s2[k]) ++numErr;
                if (numErr > 1) break;
            }

            if (numErr == 1)
            {
                std::cout << "Answer part B: ";
                for (int k = 0; k < s1.size(); k++)
                {
                    if (s1[k] == s2[k]) std::cout << s1[k];
                }
                std::cout << std::endl;
                return 1;
            }
        }
    }
    
}