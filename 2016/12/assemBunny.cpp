#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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


int main(int argc, char* argv[])
{
    std::ifstream myfile;
    std::string line;

    std::vector<std::string> code;
    std::map<std::string, int> reg;
    int head = 0;
    myfile.open(argv[1]);
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            code.push_back(line);
        }
    }
    myfile.close();
    reg["c"] = 1;
    bool done = false;
    while(! done) {
        std::vector<std::string> instructions = splitLine(code[head]);
        if (instructions[0] == "cpy")
        {
            if (int(instructions[1][0]) < 64 ) {
                reg[instructions[2]] = std::stoi(instructions[1]);
            } else {
                reg[instructions[2]] = reg[instructions[1]];
            }
            head += 1;
        } else if (instructions[0] =="inc") {
            reg[instructions[1]] += 1;
            head += 1;
        } else if (instructions[0] == "dec"){
            reg[instructions[1]] -= 1;
            head += 1;
        } else if (instructions[0] == "jnz"){
            int valToComp;
            if(int(instructions[1][0]) < 64) {
                valToComp = std::stoi(instructions[1]);
            } else {
                valToComp = reg[instructions[1]];
            }
            if( valToComp != 0) {
                head += std::stoi(instructions[2]);
            } else {
                head += 1;
            }
        }
        if(head >= code.size()) {
            done = true;
        }
    }

    std::cout << "Value in a is " << reg["a"] << std::endl;
}