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
    
    myfile.open(argv[1]);
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            code.push_back(line);
        }
    }
    int startA = 1;
    myfile.close();
    bool aFound = false;
    while(!aFound){    
        reg["a"] = startA;
        reg["b"] = 0;
        reg["c"] = 0;
        reg["d"] = 0;
        std::string out = "";
        int head = 0;
        bool done = false;
        while(! done) {
            //std::cout << head << " : " << code[head] << std::endl;
            std::vector<std::string> instructions = splitLine(code[head]);
            if (instructions[0] == "cpy")
            {
                if(int(instructions[2][0]) >= 64){
                    if (int(instructions[1][0]) < 64 ) {
                        reg[instructions[2]] = std::stoi(instructions[1]);
                    } else {
                        reg[instructions[2]] = reg[instructions[1]];
                    }
                }
                head += 1;
            } else if (instructions[0] == "inc") {
                if (int(instructions[1][0]) >= 64){
                    reg[instructions[1]] += 1;
                }
                head += 1;
            } else if (instructions[0] == "dec"){
                if (int(instructions[1][0]) >= 64){
                    reg[instructions[1]] -= 1;
                }
                head += 1;
            } else if (instructions[0] == "jnz"){
                int valToComp;
                if(int(instructions[1][0]) < 64) {
                    valToComp = std::stoi(instructions[1]);
                } else {
                    valToComp = reg[instructions[1]];
                }
                if( valToComp != 0) {
                    if (int(instructions[2][0]) < 64){
                        head += std::stoi(instructions[2]);
                    } else {
                        head += reg[instructions[2]];
                    }
                } else {
                    head += 1;
                }
            } else if (instructions[0] == "tgl"){
                int shift;
                if(int(instructions[1][0]) < 64) {
                    shift = std::stoi(instructions[1]);
                } else {
                    shift = reg[instructions[1]];
                }
                std::vector<std::string> instToChange = splitLine(code[head+shift]);
                std::cout << "Line to change " << head+shift << " : " << code[head+shift] << std::endl;
                std::cout << reg["a"] << " " << reg["b"] << " " << reg["c"] << " " << reg["d"] << std::endl;
                if(instToChange.size() == 2) {
                    if(instToChange[0] == "inc") {
                        code[head+shift] = "dec " + instToChange[1];
                    } else {
                        code[head+shift] = "inc " + instToChange[1];
                    }
                } else if (instToChange.size() == 3) {
                    if (instToChange[0] == "jnz") {
                        code[head+shift] = "cpy " + instToChange[1] + " " + instToChange[2];
                    } else {
                        code[head+shift] = "jnz " + instToChange[1] + " " + instToChange[2];
                    }
                }
                head += 1;
                
            } else if (instructions[0] == "mul")
            {
                reg[instructions[3]] += reg[instructions[1]] * reg[instructions[2]];
                head += 1;
                reg[instructions[1]] = 0;
                reg[instructions[2]] = 0;
            } else if (instructions[0] == "out")
            {
                //std::cout << reg[instructions[1]] << " " << "a" << reg["a"] << " b" << reg["b"] << " c" << reg["c"] << " d" << reg["d"] << std::endl;
                out += std::to_string(reg[instructions[1]]);
                if (out.length() == 20) done = true;
                head += 1;

            }
            
            
            
            if(head >= code.size()) {
                done = true;
            }
        }
        std::cout << startA << " " << out << std::endl;
        if (out == "01010101010101010101") {
            aFound = true;
        } else {
            startA += 1;
        }
    }

    std::cout << "Answer part A: " << startA << std::endl;
}