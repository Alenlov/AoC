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

bool sameLetters(std::string lhs, std::string rhs) {
    std::sort(lhs.begin(),lhs.end());
    std::sort(rhs.begin(), rhs.end());
    return (lhs == rhs);
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
    int numRulesA{0}, numRulesB{0};
    if (myfile.is_open())
    {
        while(getline(myfile,line)) {
            bool sameA{false}, sameB{false};
            std::vector<std::string> split = splitLine(line);
            std::cout << "Hej!" << std::endl;
            for (int i = 0; i < split.size()-1; i++) {
                for (int j = i+1; j < split.size(); j ++) {
                    std::cout << i << " " << split[i] << " " << j << " " << split[j] << std::endl;
                    if (split[i] == split[j]) {
                        sameA = true;
                    }
                    if (sameLetters(split[i], split[j])) {
                        sameB = true;
                    }
                }
            }
            if (!sameA) numRulesA++;
            if (!sameB) numRulesB++;
            
            
        }
    }
    std::cout << "Answer part A: " << numRulesA << std::endl;
    std::cout << "Answer part B: " << numRulesB << std::endl;
    

}