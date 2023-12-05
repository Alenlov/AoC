#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
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
std::map<std::string,bool> rules;
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
    std::unordered_set<int64_t> plants;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, " => ");
            if (split.size() > 1)
            {
    
                if (split[1][0] == '#')
                {
                    rules.insert({split[0],true});
                }
                

            }
            else if (line.length() > 0)
            {
                split = splitLine(line, ": ");
                for (int64_t i = 0; i < split[1].size(); i++)
                {
                    char c = split[1][i];
                    if (c == '#')
                    {
                        plants.insert(i);
                    }
                }
            }
        }
    }
    myfile.close();
    
    /* for (int64_t x = minX; x <= maxX; x++)
    {
        if(plants.contains(x))
        {
            std::cout << '#';
        }
        else
        {
            std::cout << '.';
        }
    }
    std::cout << std::endl; */

    int64_t maxIter{50000000000};
    int64_t ansA{0};
    int64_t sumPrev{0};
    int64_t diff{0};
    int64_t iter{0};
    int64_t sumNow{0};
    for (iter = 0; iter < maxIter; iter++)
    {   
        //if (iter % 100 == 0) std::cout << iter << std::endl;
        if (iter == 20)
        {
            for (int64_t p : plants)
            {
                ansA += p;
            }
        }
        sumNow = 0;
        for (int64_t p : plants)
        {
            sumNow += p;
        }
        //std::cout << sumNow << " diff  " << sumNow - sumPrev << " " << iter << std::endl;
        //std::cout << diff << std::endl;
        if (diff == sumNow - sumPrev) break;
        diff = sumNow - sumPrev;
        sumPrev = sumNow;
        std::unordered_set<int64_t> newPlants{};
        std::unordered_set<int64_t> tested{};
        for (int64_t sx : plants)
        {
            for (int x = sx - 2; x <= sx + 2; x++)    
            {    
                if (tested.contains(x)) continue;
                else tested.insert(x);
                for (auto [r, p] : rules)
                {
                    bool match{true};
                    for (int64_t i = 0; i < r.size(); i++)
                    {
                        if (!(plants.contains(x+i-2) == (r[i] == '#')))
                        {
                            match = false;
                            break;
                        }
                    }
                    if (match)
                    {
                        if (p)
                        {
                            newPlants.insert(x);
                        }
                        break;
                    }
                }   
            }
        }
        plants = newPlants;

    }
    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << sumNow + (maxIter-iter)*diff << std::endl;
}