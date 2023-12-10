#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <map>

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
    int opcode, A, B, C;
};

struct memory
{
    std::vector<int> m{0,0,0,0};
    std::vector<int> startM{0,0,0,0};
    bool print{false};
    
    void resetMem()
    {
        m = startM;
    }

    void printMem()
    {
        if (!print) return;
        for (int i : m)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
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
        printMem();
        m[i.C] = m[i.A] == m[i.B];
        printMem();
    } //(equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.

};

struct testCase
{
    instruction i;
    memory before, after;

    bool isSame()
    {
        for (int j{0}; j < before.m.size(); j++)
        {
            if (after.startM[j] != before.m[j])
            {
                return false;
            }
        }
        return true;
    }
};





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
    std::vector<testCase> testCases;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            if(line.substr(0,7) == "Before:")
            {
                std::vector<std::string> befSplit = splitLine(line.substr(9, 10),", ");
                memory before;
                before.startM[0] = std::stoi(befSplit[0]);
                before.startM[1] = std::stoi(befSplit[1]);
                before.startM[2] = std::stoi(befSplit[2]);
                before.startM[3] = std::stoi(befSplit[3]);
                getline(myfile,line);
                instruction i;
                std::vector<std::string> insSplit = splitLine(line, " ");
                i.opcode = std::stoi(insSplit[0]);
                i.A = std::stoi(insSplit[1]);
                i.B = std::stoi(insSplit[2]);
                i.C = std::stoi(insSplit[3]);

                getline(myfile, line);
                std::vector<std::string> aftSplit = splitLine(line.substr(9, 10),", ");
                memory after;
                after.startM[0] = std::stoi(aftSplit[0]);
                after.startM[1] = std::stoi(aftSplit[1]);
                after.startM[2] = std::stoi(aftSplit[2]);
                after.startM[3] = std::stoi(aftSplit[3]);
                
                testCase t;
                t.i = i;
                t.before = before;
                t.after = after;
                testCases.push_back(t);
            }
            else if (line.length() > 0)
            {
                instruction i;
                std::vector<std::string> insSplit = splitLine(line, " ");
                i.opcode = std::stoi(insSplit[0]);
                i.A = std::stoi(insSplit[1]);
                i.B = std::stoi(insSplit[2]);
                i.C = std::stoi(insSplit[3]);
                instructions.push_back(i);
            }
                      
        }
    }
    
    myfile.close();



    std::map<int,std::unordered_set<std::string>> opCodes;
    for (int i{0}; i < 16; i++)
    {
        opCodes[i] = operators;
    }
    

    int ansA{0};
    for (testCase t : testCases)
    {
        int numInst{0};
        t.before.resetMem();
        t.before.addr(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("addr");
        }

        t.before.resetMem();
        t.before.addi(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("addi");
        }

        t.before.resetMem();
        t.before.mulr(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("mulr");
        }
        
        t.before.resetMem();
        t.before.muli(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("muli");
        }
        
        t.before.resetMem();
        t.before.banr(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("banr");
        }
        
        t.before.resetMem();
        t.before.bani(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("bani");
        }
        
        t.before.resetMem();
        t.before.borr(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("borr");
        }
        
        t.before.resetMem();
        t.before.bori(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("bori");
        }
        
        t.before.resetMem();
        t.before.setr(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("setr");
        }
        
        t.before.resetMem();
        t.before.seti(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("seti");
        }
        
        t.before.resetMem();
        t.before.gtir(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("gtir");
        }

        t.before.resetMem();
        t.before.gtri(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("gtri");
        }
        
        t.before.resetMem();
        t.before.gtrr(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("gtrr");
        }
        
        t.before.resetMem();
        t.before.eqir(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("eqir");
        }
        
        t.before.resetMem();
        t.before.eqri(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("eqri");
        }
        
        t.before.resetMem();
        t.before.eqrr(t.i);
        if (t.isSame())
        {
            ++numInst;
        }
        else
        {
            opCodes[t.i.opcode].erase("eqrr");
        }
        
        if (numInst >= 3) ++ansA;
    }

    std::cout << "Answer part A: " << ansA << std::endl;

    
    while(!operators.empty())
    {
        std::string toRemove;
        for (int j{0}; j < 16; j++)
        {
            if (opCodes[j].size() == 1)
            {
                std::string cand = *opCodes[j].begin();
                if (operators.contains(cand))
                {
                    toRemove = cand;
                    operators.erase(cand);
                    break;
                }
            }
        }

        for (int j{0}; j < 16; j++)
        {
            if (opCodes[j].size() > 1)
            {
                opCodes[j].erase(toRemove);
            }
        }
    }


    for (auto const [c,op] : opCodes)
    {
        std::cout << c << " : ";
        for (std::string s : op)
        {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
    
    memory m;
    for (instruction i : instructions)
    {
        std::string inst = *opCodes[i.opcode].begin();
        if(inst == "addr") m.addr(i);
        if(inst == "addi") m.addi(i);
        if(inst == "mulr") m.mulr(i);
        if(inst == "muli") m.muli(i);
        if(inst == "banr") m.banr(i);
        if(inst == "bani") m.bani(i);
        if(inst == "borr") m.borr(i);
        if(inst == "bori") m.bori(i);
        if(inst == "setr") m.setr(i);
        if(inst == "seti") m.seti(i);
        if(inst == "gtir") m.gtir(i);
        if(inst == "gtri") m.gtri(i);
        if(inst == "gtrr") m.gtrr(i);
        if(inst == "eqir") m.eqir(i);
        if(inst == "eqri") m.eqri(i);
        if(inst == "eqrr") m.eqrr(i);
    }
    
    std::cout << "Answer part B: " << m.m[0] << std::endl;
}