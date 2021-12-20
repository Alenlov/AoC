#include "comp.h"
#include <vector>
#include <string>
#include <iostream>

Computer::Computer(const std::vector<std::string> inProgram){
    registerA = 0;
    registerB = 0;

    program = inProgram;
}

void Computer::runProgram(int head)
{
    bool running = true;
    while(running){
        std::string line = program[head];
        std::string instruction = line.substr(0,3);
        if(instruction == "hlf"){
            std::string reg = line.substr(4,1);
            if(reg == "a"){
                registerA /= 2;
            } else if(reg == "b"){
                registerB /= 2;
            }
            head += 1;
        } else if(instruction == "tpl"){
            std::string reg = line.substr(4,1);
            if(reg == "a"){
                registerA *= 3;
            } else if(reg == "b"){
                registerB *= 3;
            }
            head += 1;
        } else if (instruction == "inc"){
            std::string reg = line.substr(4,1);
            if(reg == "a"){
                registerA += 1;
            } else if(reg == "b"){
                registerB += 1;
            }
            head += 1;
        } else if (instruction == "jmp"){
            int offset = std::stoi(line.substr(4,line.size()));
            head += offset;
        } else if (instruction == "jie"){
            std::string reg = line.substr(4,1);
            int offset = std::stoi(line.substr(7,line.size()));
            if((reg == "a")&&((registerA % 2) == 0)){
                head += offset;
            } else if((reg == "b")&&((registerB % 2)==0)){
                head += offset;
            } else {
                head += 1;
            }
        } else if (instruction == "jio"){
            std::string reg = line.substr(4,1);
            int offset = std::stoi(line.substr(7,line.size()));
            if((reg == "a")&&(registerA == 1)){
                head += offset;
            } else if((reg == "b")&&(registerB ==1)){
                head += offset;
            } else {
                head += 1;
            }
        }
        if (head >= program.size()){
            running = false;
        }
    }
    std::cout << "Program finished" << std::endl;
}

        // Get register
int Computer::getRegisterA() const
{
    return registerA;
}
int Computer::getRegisterB() const
{
    return registerB;
}

void Computer::setRegisterA(int const a){
    registerA = a;
}
void Computer::setRegisterB(int const b){
    registerB = b;
}