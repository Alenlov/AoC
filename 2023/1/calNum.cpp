#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <map>

std::map<std::string,int> stringToNumA{{"1",1},{"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},{"9",9}};
std::map<std::string,int> stringToNumB{{"one",1},{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},{"seven",7},{"eight",8},{"nine",9},{"1",1},{"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},{"9",9}};


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

int calcVal(std::string line, std::map<std::string,int> vals)
{
    std::size_t firstIndx{line.length()+1}, lastIndx{0};
    int firstVal{0}, lastVal{0};
    for (auto const [k,v] : vals)
    {
        std::size_t indx1 = line.find(k);
        if (indx1 != std::string::npos)
        {
            if (indx1 <= firstIndx)
            {
                firstIndx = indx1;
                firstVal = v;
            }
        }
        std::size_t indx2 = line.rfind(k);
        if (indx2 != std::string::npos)
        {
            if (indx2 >= lastIndx)
            {
                lastIndx = indx2;
                lastVal = v;
            }
        }
    }
    return firstVal*10 + lastVal;
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
    int sumA{0}, sumB{0};
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            
            sumA += calcVal(line, stringToNumA);
            sumB += calcVal(line, stringToNumB);
        }
        
    }
    myfile.close();
    std::cout << "Answer part A: " << sumA << std::endl;
    std::cout << "Answer part B: " << sumB << std::endl;
}