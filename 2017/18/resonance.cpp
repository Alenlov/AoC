#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>

struct program
{
    int head;
    std::map<char, long> reg;
    bool waiting{false};
    std::queue<long> rcvMsg;
    int msgSent{0};
};

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

// Returns true if at least one program can take another step.
// false if both programs have terminated.
bool runPrograms(const std::vector<std::vector<std::string>> instructions, program &pA, program &pB)
{
    /* std::map<int, program> programs;
    programs[0] = pA;
    programs[1] = pB;
    for (auto &prog : programs)
    { */
    

        if(pA.head >= instructions.size())
        {
            pA.waiting = true;
        }
        else
        {
        std::string inst = instructions[pA.head][0];
        char lhs = instructions[pA.head][1][0];
        if (!pA.reg.contains(lhs)) pA.reg[lhs] = 0;
        if (inst == "set")
        {
            char rhs = instructions[pA.head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! pA.reg.contains(rhs)) pA.reg[rhs] =0;
                val = pA.reg[rhs];
            }
            else
            {
                val = std::stol(instructions[pA.head][2]);
            }
            pA.reg[lhs] = val;
            ++pA.head;
        }
        else if (inst == "mul")
        {
            char rhs = instructions[pA.head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! pA.reg.contains(rhs)) pA.reg[rhs] =0;
                val = pA.reg[rhs];
            }
            else
            {
                val = std::stol(instructions[pA.head][2]);
            }
            pA.reg[lhs] *= val;
            ++pA.head;
        }
        else if (inst == "add")
        {
            char rhs = instructions[pA.head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! pA.reg.contains(rhs)) pA.reg[rhs] =0;
                val = pA.reg[rhs];
            }
            else
            {
                val = std::stol(instructions[pA.head][2]);
            }
            pA.reg[lhs] += val;
            ++pA.head;
        }
        else if (inst == "jgz")
        {
            char rhs = instructions[pA.head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! pA.reg.contains(rhs)) pA.reg[rhs] =0;
                val = pA.reg[rhs];
            }
            else
            {
                val = std::stol(instructions[pA.head][2]);
            }
            if (lhs == '1')
            {
                pA.head += val;
            }
            else if (pA.reg[lhs] > 0)
            {
                pA.head += val;
            }
            else
            {
                ++pA.head;
            }
        }
        else if (inst == "mod")
        {
            char rhs = instructions[pA.head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! pA.reg.contains(rhs)) pA.reg[rhs] =0;
                val = pA.reg[rhs];
            }
            else
            {
                val = std::stol(instructions[pA.head][2]);
            }
            //std::cout << pA.reg[lhs] % val << " " << pA.reg[lhs] << " " << val << std::endl;;
            pA.reg[lhs] %= val;
            //std::cout << pA.reg[lhs] << std::endl;
            ++pA.head;
        }
        else if (inst == "snd")
        {
            pB.rcvMsg.push(pA.reg[lhs]);
            ++pA.msgSent;
            ++pA.head;
        }
        else if (inst == "rcv")
        {
            if (pA.rcvMsg.size() > 0)
            {
                pA.reg[lhs] = pA.rcvMsg.front();
                pA.rcvMsg.pop();
                ++pA.head;
                pA.waiting = false;
            }
            else
            {
                pA.waiting = true;
            }
        }
    }
    
    if (pA.waiting && pB.waiting)
    {
        return false;
    }
    else
    {
        return true;
    }
    
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
    std::vector<std::vector<std::string>> instructions;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            instructions.push_back(splitLine(line));
        }
    }
    myfile.close();
    std::map<char, long> reg;
    bool firstFound{false};
    int head{0};
    long lastFreq{};
    while( head < instructions.size())
    {
        std::string inst = instructions[head][0];
        char lhs = instructions[head][1][0];
        if (!reg.contains(lhs)) reg[lhs] = 0;
        if (inst == "set")
        {
            char rhs = instructions[head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! reg.contains(rhs)) reg[rhs] =0;
                val = reg[rhs];
            }
            else
            {
                val = std::stol(instructions[head][2]);
            }
            reg[lhs] = val;
            ++head;
        }
        else if (inst == "mul")
        {
            char rhs = instructions[head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! reg.contains(rhs)) reg[rhs] =0;
                val = reg[rhs];
            }
            else
            {
                val = std::stol(instructions[head][2]);
            }
            reg[lhs] *= val;
            ++head;
        }
        else if (inst == "add")
        {
            char rhs = instructions[head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! reg.contains(rhs)) reg[rhs] =0;
                val = reg[rhs];
            }
            else
            {
                val = std::stol(instructions[head][2]);
            }
            reg[lhs] += val;
            ++head;
        }
        else if (inst == "jgz")
        {
            char rhs = instructions[head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! reg.contains(rhs)) reg[rhs] =0;
                val = reg[rhs];
            }
            else
            {
                val = std::stol(instructions[head][2]);
            }
            if (reg[lhs] > 0)
            {
                head += val;
            }
            else
            {
                ++head;
            }
        }
        else if (inst == "mod")
        {
            char rhs = instructions[head][2][0];
            long val;
            if (int(rhs) >= int('a') && int(rhs) <= int('z'))
            {
                if(! reg.contains(rhs)) reg[rhs] =0;
                val = reg[rhs];
            }
            else
            {
                val = std::stol(instructions[head][2]);
            }
            //std::cout << reg[lhs] % val << " " << reg[lhs] << " " << val << std::endl;;
            reg[lhs] %= val;
            //std::cout << reg[lhs] << std::endl;
            ++head;
        }
        else if (inst == "snd")
        {
            if (! reg.contains(lhs)) reg[lhs] = 0;
            lastFreq = reg[lhs];
            ++head;
        }
        else if (inst == "rcv")
        {
            if (reg[lhs] != 0)
            {
                if (! firstFound)
                {   
                    std::cout << "Head " << head << std::endl;
                    std::cout << "Answer part A: " << lastFreq << std::endl;
                    firstFound = true;
                    break;
                }
            }
            ++head;
        }
        
        
    }

    program pA;
    pA.head = 0;
    pA.reg['p'] = 0;
    program pB;
    pB.head = 0;
    pB.reg['p'] = 1;

    bool running{true};
    while(running){
        runPrograms(instructions, pA, pB);
        running = runPrograms(instructions, pB, pA);
    }
    std::cout << "Answer part B: " << pB.msgSent << std::endl;


    
    
}