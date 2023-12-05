#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
/*




*/

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

std::string memString(std::vector<int> mem) {
    std::string m{""};
    for (int i : mem) m += " " + std::to_string(i);
    return m;
}
std::vector<int> redistributeMemory(std::vector<int> mem) {
    int max{0}, maxI{-1};
    for (int i = 0; i < mem.size(); i++) {
        if (mem[i] > max) {
            maxI = i;
            max = mem[i];
        }
    }

    int memSize = mem.size();

    int forAll = mem[maxI]/memSize;
    int numExtra = mem[maxI] % memSize;

    std::vector<int> newMem(memSize);

    for (int j = 0; j < memSize; j++) {
        if (j == maxI) {
            newMem[j] = forAll;
        } else {
            newMem[j] = mem[j] + forAll;
        }
    }
    for (int j = 0; j < numExtra; j++) {
        newMem[(maxI + j + 1)%memSize]++;
    }

    return newMem;

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

    if (myfile.is_open())
    {
        getline(myfile,line);
    }
    std::vector<int> memory;
    for (std::string s : splitLine(line, "\t")) memory.push_back(std::stoi(s));

    std::map<std::string,int> memConfigs;
    std::string memS = memString(memory);
    int steps{0};
    while(! memConfigs.contains(memS)) {
        memConfigs.insert({memS, steps});
        memory = redistributeMemory(memory);
        steps++;
        memS = memString(memory);
    }
    std::cout << "Answer part A: " << steps << std::endl;
    std::cout << "Answer part B: " << steps - memConfigs[memS] << std::endl;
}