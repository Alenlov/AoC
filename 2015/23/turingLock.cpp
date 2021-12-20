#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "comp.h"





int main(int argc, char* argv[]){
    if (argc == 1){
        std::cout << "Need an input with file name!" << std::endl;
        return 0;
    }
    std::vector<std::string> program;
    std::ifstream myfile;
    std::string line;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile, line)){
            program.push_back(line);
        }
    }
    myfile.close();
    Computer comp = Computer(program);
    comp.runProgram();
    std::cout << "After running the program we have " << comp.getRegisterB() << " in register B." <<std::endl;

    comp.setRegisterA(1);
    comp.setRegisterB(0);
    comp.runProgram();
    std::cout << "After running the program we have " << comp.getRegisterB() << " in register B." <<std::endl;
}