#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
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
    int totSumA{0}, totSumB{0};
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == line[(i+1) % line.length()]) totSumA += (int(line[i]) - int('0'));
        if (line[i] == line[(i + line.length()/2) % line.length()]) totSumB += (int(line[i]) - int('0'));
    }

    std::cout << "Answer part A: " << totSumA << std::endl;
    std::cout << "Answer part B: " << totSumB << std::endl;

}