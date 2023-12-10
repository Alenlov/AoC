#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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
    std::vector<int> times, dists;
    long timeB, distB;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line);
            std::string partB{""};
            for(int i{1}; i < split.size(); i++)
            {
                if (split[0] == "Time:")
                {
                    times.push_back(std::stoi(split[i]));
                }
                else if (split[0] == "Distance:")
                {
                    dists.push_back(std::stoi(split[i]));
                }
                partB += split[i];
                
            }
            if (split[0] == "Time:")
            {
                timeB = std::stol(partB);
            }
            else if (split[0] == "Distance:")
            {
                distB = std::stol(partB);
            }
            
        }
    }
    myfile.close();
    long ansA{1};
    for (int i{0}; i < times.size(); i++)
    {
        int numOver{0};
        for (int t{0}; t<=times[i]; t++)
        {
            if (t*(times[i]-t) > dists[i]) ++numOver;
        }
        ansA *= numOver;
    }
    std::cout << "Answer part A: " << ansA << std::endl;

    long lowerT{0};
    while( lowerT*(timeB-lowerT) < distB) ++lowerT;

    long upperT{timeB};
    while (upperT*(timeB - upperT) < distB) --upperT;

    long ansB{upperT - lowerT + 1};

    std::cout << "Answer part B: " << ansB << std::endl;
    
}