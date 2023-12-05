#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
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
    std::map<std::string, std::vector<std::string>> pipes;
    std::set<std::string> allPrograms;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line," <-> ");
            std::string lhs = split[0];
            std::vector<std::string> rhs = splitLine(split[1],", ");
            pipes[lhs] = rhs;
            allPrograms.insert(lhs);
        }
    }
    myfile.close();
    std::set <std::string> fromZero;
    fromZero.insert("0");
    std::queue<std::string> heads;
    heads.push("0");
    while(heads.size() > 0) {
        std::string head = heads.front();
        heads.pop();

        for (std::string d : pipes[head])
        {
            if (!fromZero.contains(d))
            {
                fromZero.insert(d);
                heads.push(d);
            }
        }
    }

    std::cout << "Answer part A: " << fromZero.size() << std::endl;

    int numGroups{0};
    while (allPrograms.size() > 0)
    {
        numGroups++;
        std::set<std::string> thisGroup;
        std::string head = *allPrograms.begin();
        heads.push(head);
        allPrograms.erase(head);
        thisGroup.insert(head);
        while(!heads.empty())
        {
            head = heads.front();
            heads.pop();
            for (std::string d : pipes[head])
            {
                if (!thisGroup.contains(d))
                {
                    thisGroup.insert(d);
                    heads.push(d);
                    allPrograms.erase(d);
                }
            }
        }
    }
    std::cout << "Answer part B: " << numGroups << std::endl;
    
}