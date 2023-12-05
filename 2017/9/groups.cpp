#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

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
const char groupStart{'{'}, groupEnd{'}'}, garbageStart{'<'}, garbageEnd{'>'}, cancel{'!'};
const std::set<char> specialChars{groupStart, groupEnd, garbageStart, garbageEnd, cancel};
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
    myfile.close();
    int groupLevel{0}, score{0}, garbageChars{0};
    bool containedGarbage{false}, canceled{false};

    for (char c : line) 
    {
        if (canceled) 
        {
            canceled = false;
        }
        else if (specialChars.contains(c)) 
        {
            if (containedGarbage) 
            {
                containedGarbage = !(c == garbageEnd);
                canceled = c == cancel;
                if (! (canceled || !containedGarbage)) garbageChars += 1;
            } 
            else
            {
                if (c == groupStart) 
                {
                    groupLevel += 1;
                }
                else if (c == groupEnd)
                {
                    score += groupLevel;
                    groupLevel -= 1;
                }
                else if (c == garbageStart)
                {
                    containedGarbage = true;
                }
                else if (c == cancel)
                {
                    canceled = true;
                }
            
            }
        }
        else if (containedGarbage)
        {
            garbageChars += 1;
        }
        //std::cout << c << " groupLevel " << groupLevel << " cg " << containedGarbage << " c " << canceled << std::endl;
    }

    std::cout << "Answer part A: " << score << std::endl;
    std::cout << "Answer part B: " << garbageChars << std::endl;
    
}