#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <tuple>
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

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    std::vector<std::vector<std::string>> program;
    if(myfile.is_open()) {
        while(getline(myfile,line)){
            program.push_back(splitLine(line));
        }

    }
    myfile.close();
    int cycle = 0;
    int x = 1;
    int head = 0;
    int cyclesToComplete = 0;
    int output = 0;
    std::string instruction = "";
    std::string display = "";
    while(head < program.size()) {
        // starting cycle
        cycle += 1;
        if(cyclesToComplete == 0) {
            instruction = program[head][0];
            if(instruction == "noop") {
                cyclesToComplete = 1;
            } else if (instruction == "addx") {
                cyclesToComplete = 2;
            }
        }
        
        // during cycle
        if ((cycle - 20)%40 == 0) {
            output += cycle * x;
        }
        if (abs(((cycle-1) % 40 )- x) <= 1) {
            display += "#";
        } else {
            display += ".";
        }

        // after cycle

        cyclesToComplete -= 1;
        if (cyclesToComplete == 0){
            if( instruction == "addx") {
                x += std::stoi(program[head][1]);
            }
            head += 1;
        }
    }
    std::cout << "Output is " << output << std::endl;

    std::cout << display.substr(0,40) << std::endl;
    std::cout << display.substr(40,40) << std::endl;
    std::cout << display.substr(80,40) << std::endl;
    std::cout << display.substr(120,40) << std::endl;
    std::cout << display.substr(160,40) << std::endl;
    std::cout << display.substr(200,40) << std::endl;
        
}
    

    

