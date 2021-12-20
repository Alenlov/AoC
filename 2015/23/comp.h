
#ifndef COMP_H
#define COMP_H

#include <string>
#include <vector>


class Computer
{
    private :
        int registerA;
        int registerB;
        std::vector<std::string> program;
    
    public :
        // Constructor
        Computer(const std::vector<std::string> program);

        // Run program
        void runProgram(int head = 0);

        // Get register
        int getRegisterA() const;
        int getRegisterB() const;

        void setRegisterA(int const a);
        void setRegisterB(int const b);

};

#endif