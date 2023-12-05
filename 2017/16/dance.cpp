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

std::vector<std::string> danceMoves;

void oneDance(std::vector<char>& programs)
{
    int numProgs = programs.size();
    for (std::string m : danceMoves)
    {
        
        if (m[0] == 's')
        {
            int num = std::stoi(m.substr(1,-1));
            std::vector<char> newOrder(numProgs);
            for (int i = 0; i < numProgs; i++)
            {
                newOrder[i] = programs[ (numProgs - num + i) % numProgs ];
            }
            programs = newOrder;
        }
        else if (m[0] == 'x')
        {
            std::vector<std::string> thisMove = splitLine(m.substr(1,-1),"/");
            int lhsI = std::stoi(thisMove[0]);
            int rhsI = std::stoi(thisMove[1]);
            char lhsC = programs[lhsI];
            char rhsC = programs[rhsI];
            programs[lhsI] = rhsC;
            programs[rhsI] = lhsC;

        }
        else if (m[0] == 'p')
        {
            std::vector<std::string> thisMove = splitLine(m.substr(1,-1),"/");
            char lhsC = thisMove[0][0];
            char rhsC = thisMove[1][0];
            int lhsI, rhsI;
            for (int i = 0; i < numProgs; i++)
            {
                if (programs[i] == lhsC) lhsI = i;
                if (programs[i] == rhsC) rhsI = i;   
            }
            programs[lhsI] = rhsC;
            programs[rhsI] = lhsC;
        }
        
    }
}

std::string toString(std::vector<char> programs)
{
    std::string out = "";
    for(char c : programs) out += c;
    return out;
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
    if (myfile.is_open())
    {
        getline(myfile,line);
    }
    myfile.close();
    int numProgs{16};
    danceMoves = splitLine(line, ",");
    std::vector<char> programs(numProgs);
    for (int i = 0; i < numProgs; i++)
    {
        char p = 'a' + i;
        programs[i] = p;
    }
    std::string progString = toString(programs);
    std::map<std::string,int> positions;
    int loop{0};
    positions[progString] = loop;
    oneDance(programs);
    loop++;
    progString = toString(programs);
    positions[progString] = loop;
    std::cout << "Answer part A: ";
    for(char c : programs)
    {
        std::cout << c;
    }
    std::cout << std::endl;
    bool loopFound{false};
    while (!loopFound)
    {
        oneDance(programs);
        loop++;
        progString = toString(programs);
        if (positions.contains(progString))
        {
            loopFound = true;
            std::cout << progString << std::endl;
        }
        else
        {
            positions[progString] = loop;
        }
    }
    int toFind = 1000000000 % loop;
    for (auto [s, v] : positions)
    {
        if (v == toFind)
        {
            std::cout << "Answer part B: " << s << std::endl;
        }
    }
    
}