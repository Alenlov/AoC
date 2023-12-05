#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

std::map<char,int> mem{{'a',0},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0},{'g',0},{'h',0}};
std::map<char,int> memB{{'a',1},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0},{'g',0},{'h',0}};

bool notPrime(int b)
{
    if (b % 2 == 0) return true;
    for (int div = 3; div < b/2; div+=2)
    {
        if (b % div == 0) return true;
    }
    return false;
}

int getVal(std::string in)
{
    if(in.length() > 1)
    {
        return std::stoi(in);
    }
    else if (mem.contains(in[0]))
    {
        return mem[in[0]];
    }
    else
    {
        return std::stoi(in);
    }
    
}

int getValB(std::string in)
{
    if(in.length() > 1)
    {
        return std::stoi(in);
    }
    else if (memB.contains(in[0]))
    {
        return memB[in[0]];
    }
    else
    {
        return std::stoi(in);
    }
    
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
    std::vector<std::vector<std::string>> code;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            code.push_back(splitLine(line));
        }
    }
    myfile.close();
    

    int head{0};
    int numMul{0};
    while(head < code.size())
    {
        std::vector<std::string> instruction = code[head];
        if (instruction[0] == "set")
        {
            mem[instruction[1][0]] = getVal(instruction[2]);
            ++head;
        }
        else if (instruction[0] == "sub")
        {
            mem[instruction[1][0]] -= getVal(instruction[2]);
            ++head;
        }
        else if (instruction[0] == "mul")
        {
            mem[instruction[1][0]] *= getVal(instruction[2]);
            ++head;
            ++numMul;
        }
        else if (instruction[0] == "jnz")
        {
            if(getVal(instruction[1]) != 0)
            {
                head += getVal(instruction[2]);
            }
            else
            {
                ++head;
            }
        }
    }
    std::cout << "Answer part A: " << numMul << std::endl;

    head = 0;
    while(head < 9)
    {
        std::cout << "head:" << head << " a:" << memB['a'] << " b:" << memB['b'] << " c:" << memB['c'] << " d:" << memB['d'] << " e:" << memB['e'] << " f:" << memB['f'] << " g:" << memB['g'] << " h:" << memB['h'] << std::endl;
        std::vector<std::string> instruction = code[head];
        if (instruction[0] == "set")
        {
            memB[instruction[1][0]] = getValB(instruction[2]);
            ++head;
        }
        else if (instruction[0] == "sub")
        {
            memB[instruction[1][0]] -= getValB(instruction[2]);
            ++head;
        }
        else if (instruction[0] == "mul")
        {
            memB[instruction[1][0]] *= getValB(instruction[2]);
            ++head;
            ++numMul;
        }
        else if (instruction[0] == "jnz")
        {
            if(getValB(instruction[1]) != 0)
            {
                head += getValB(instruction[2]);
            }
            else
            {
                ++head;
            }
        }
    }
    int h{0};
    for(int v = memB['b']; v <= memB['c']; v+=17)
    {
        if (notPrime(v))
        {
            ++h;
        }
    }
    std::cout << "Answer part B: " << h << std::endl;
}