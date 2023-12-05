#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fmt/format.h>

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
    long startA{0}, startB{0}, genA{0}, genB{0}, facA{16807}, facB{48271}, divider{2147483647}, numLoopsA{40000000}, check{1<<16}, numLoopsB{5000000}, checkA{4}, checkB{8};
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line);
            if (split[1] == "A") startA = std::stol(split[4]);
            if (split[1] == "B") startB = std::stol(split[4]);
        }
    }
    int pairs{0};
    genA = startA;
    genB = startB;
    for(long i = 0; i < numLoopsA; i++)
    {
        genA = (genA * facA) % divider;
        genB = (genB * facB) % divider;
        /* std::string bitsA = fmt::format("{:B}", genA % check);
        std::string bitsB = fmt::format("{:B}", genB % check);
        if (bitsA == bitsB)
        {
            pairs++;
        } */
        if ( (genA - genB)% check == 0 )
        {
            pairs++;
        }
    }
    myfile.close();
    std::cout << "Answer part A: " << pairs << std::endl;

    genA = startA;
    genB = startB;
    int pairsB{0};
    for(long i = 0; i < numLoopsB; i++)
    {
        do
        {
            genA = (genA*facA) % divider;
        } while (genA%checkA != 0);

        do
        {
            genB = (genB*facB) % divider;
        } while (genB%checkB != 0);
        if ((genA - genB) % check == 0)
        {
            pairsB++;
        }
    }
    std::cout << "Answer part B: " << pairsB << std::endl;
}