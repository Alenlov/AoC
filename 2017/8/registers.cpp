#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
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

std::map<std::string, int> change{{"inc", 1}, {"dec", -1}};

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
    std::map<std::string,int> registers;
    int maxB{1 << 31};
    if (myfile.is_open())
    {
        while(getline(myfile,line)) {
            std::vector<std::string> split = splitLine(line);
            if (!registers.contains(split[0])) registers[split[0]] = 0;
            if (!registers.contains(split[4])) registers[split[4]] = 0;

            bool valid = false;
            if (split[5] == ">=") {
                valid = registers[split[4]] >= std::stoi(split[6]);
            } else if (split[5] == ">") {
                valid = registers[split[4]] > std::stoi(split[6]);

            } else if (split[5] == "==") {
                valid = registers[split[4]] == std::stoi(split[6]);
                
            } else if (split[5] == "<") {
                valid = registers[split[4]] < std::stoi(split[6]);
                
            } else if (split[5] == "<=") {
                valid = registers[split[4]] <= std::stoi(split[6]);
                
            } else if (split[5] == "!=") {
                valid = registers[split[4]] != std::stoi(split[6]);
                
            }
            if (valid){ 
                registers[split[0]] += change[split[1]] * std::stoi(split[2]);
                if (registers[split[0]] > maxB) maxB = registers[split[0]];
            }
        }
    }
    int max{(1 << 31)};
    
    for (auto [reg, val] : registers) {
        if (val > max) max = val;
    }
    
    std::cout << "Answer part A: " << max << std::endl;
    std::cout << "Answer part B: " << maxB << std::endl;
    
}