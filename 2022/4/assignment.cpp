#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>

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
    int totOverlap = 0, anyOverlap = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            std::vector<std::string> lineVector = splitLine(line, ",");
            std::vector<std::string> first = splitLine(lineVector[0],"-");
            std::vector<std::string> second = splitLine(lineVector[1],"-");
            int fl = std::stoi(first[0]);
            int fr = std::stoi(first[1]);
            int sl = std::stoi(second[0]);
            int sr = std::stoi(second[1]);
            if ((fl >= sl && fr <= sr) || (sl >= fl && sr <= fr )) {
                totOverlap += 1;
                anyOverlap += 1;
            } else if (( fl >= sl && fl <= sr) || ( fr >= sl && fr <= sr))
            {
                anyOverlap += 1;
            }
            
        }
    }
    myfile.close();
    std::cout << "Totall overllap " << totOverlap << std::endl;
    std::cout << "Any overllap " << anyOverlap << std::endl;
    
}