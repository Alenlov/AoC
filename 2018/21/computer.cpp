#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <set>

std::unordered_set<std::string> operators{"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"};

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

struct instruction
{
    std::string type;
    int A, B, C;
};

struct computer
{
    std::map<int,int> instVisited;
    bool partA{false};
    long ansB{0}, count{0};
    std::unordered_set<long> findLoops;
    long prev;
    std::vector<long> m{0,0,0,0,0,0};
    std::vector<instruction> program;
    int ip{0};
    bool print{false};
    long iter{0};

    void printMem()
    {
        if (!print) return;
        std::cout << "ip " << ip << " " << m[ip] << " ";
        for (int i : m)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    long runProgram(long maxIter = -1)
    {
        long inst{m[ip]};
        iter = 0;
        while (inst < program.size())
        {
            //if (inst == 1) std::cout << "Inst " << inst << " m[2] " << m[2] << std::endl;
            m[ip] = inst;
            runInstruction(program[inst]);
            printMem();
            ++instVisited[inst];
            inst = m[ip] + 1;
            ++iter;
            if ((maxIter > 0) && (iter > maxIter)) break;
        }
        return iter;
    }

    void runInstruction(instruction i)
    {
        if (i.type == "addr") addr(i);
        else if (i.type == "addi") addi(i);
        else if (i.type == "mulr") mulr(i);
        else if (i.type == "muli") muli(i);
        else if (i.type == "banr") banr(i);
        else if (i.type == "bani") bani(i);
        else if (i.type == "borr") borr(i);
        else if (i.type == "bori") bori(i);
        else if (i.type == "setr") setr(i);
        else if (i.type == "seti") seti(i);
        else if (i.type == "gtir") gtir(i);
        else if (i.type == "gtri") gtri(i);
        else if (i.type == "gtrr") gtrr(i);
        else if (i.type == "eqir") eqir(i);
        else if (i.type == "eqri") eqri(i);
        else if (i.type == "eqrr") eqrr(i);
        
    }

    void addr(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] + m[i.B];
        printMem();
    }
    void addi(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] + i.B;
        printMem();
    }
    void mulr(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] * m[i.B];
        printMem();
    }
    void muli(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] * i.B;
        printMem();
    }
    void banr(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] & m[i.B];
        printMem();
    } //(bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
    void bani(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] & i.B;
        printMem();
    } //(bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
    void borr(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] | m[i.B];
        printMem();
    } //(bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
    void bori(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] | i.B;
        printMem();
    } //(bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
    void setr(instruction i)
    {
        printMem();
        m[i.C] = m[i.A];
        printMem();
    } //(set register) copies the contents of register A into register C. (Input B is ignored.)
    void seti(instruction i)
    {
        printMem();
        m[i.C] = i.A;
        printMem();
    } //(set immediate) stores value A into register C. (Input B is ignored.)
    void gtir(instruction i)
    {
        printMem();
        m[i.C] = i.A > m[i.B];
        printMem();
    } //(greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
    void gtri(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] > i.B;
        printMem();
    }// (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
    void gtrr(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] > m[i.B];
        printMem();
    } //(greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
    void eqir(instruction i)
    {
        printMem();
        m[i.C] = i.A == m[i.B];
        printMem();
    } //(equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
    void eqri(instruction i)
    {
        printMem();
        m[i.C] = m[i.A] == i.B;
        printMem();
    } //(equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
    void eqrr(instruction i)
    {
        if (!partA)
        {
            std::cout << "Anser part A: " << m[i.A] << std::endl;
            partA = true;
        }
        
        if (findLoops.contains(m[i.A]))
        {
            std::cout << "Answer part B: " << prev << std::endl;
            return;
        }
        else
        {
            findLoops.insert(m[i.A]);
            prev = m[i.A];
        }

        
        printMem();
        m[i.C] = m[i.A] == m[i.B];
        printMem();
    } //(equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.

};

long sumOfFactors(long num)
{
    long sum{num+1};
    for (int i{2} ; i*i < num; i++)
    {
        if (num % i == 0)
        {
            sum += i;
            sum += num/i;
        }
    }
    return sum;
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
    std::vector<instruction> instructions;
    computer comp;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, " ");
            if (split.size() == 2)
            {
                comp.ip = std::stoi(split[1]);
            }
            else
            {
                instruction i;
                i.type = split[0];
                i.A = std::stoi(split[1]);
                i.B = std::stoi(split[2]);
                i.C = std::stoi(split[3]);
                instructions.push_back(i);
            }
        }
    }
    myfile.close();
    comp.program = instructions;
    comp.runProgram();
}