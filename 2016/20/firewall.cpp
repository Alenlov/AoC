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
    std::vector<std::pair<unsigned long, unsigned long>> blockRanges;
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
        while(getline(myfile,line)) {
            std::vector<std::string> split = splitLine(line, "-");
            //std::cout << split.at(0) << " " << split.at(1) << std::endl;
            unsigned long lhs{std::stoul(split.at(0))};
            unsigned long rhs{std::stoul(split.at(1))};
            blockRanges.emplace_back(std::make_pair(lhs,rhs));
        }
    }

    bool changed{true};
    while(changed) {
        changed = false;
        std::vector<std::pair<unsigned long, unsigned long>> newBlockRanges;
        for(std::pair<unsigned long, unsigned long> rule : blockRanges) {
            if(newBlockRanges.size() == 0) {
                newBlockRanges.emplace_back(rule);
            } else {
                bool overlap{false};
                for(int i = 0; i < newBlockRanges.size(); i++) {
                    std::pair<unsigned long, unsigned long> r = newBlockRanges.at(i);
                    if(rule.second + 1 < r.first || rule.first > r.second + 1) continue;
                    //std::cout << "Overlap" << std::endl;
                    unsigned long newLhs{std::min(rule.first, r.first)};
                    unsigned long newRhs{std::max(rule.second, r.second)};
                    //std::cout << rule.first << " " << r.first << " min " << newLhs << std::endl;
                    //std::cout << rule.second << " " << r.second << " max " << newRhs << std::endl;
                    newBlockRanges.at(i).first = newLhs;
                    newBlockRanges.at(i).second = newRhs;
                    //std::cout << r.first << "-" << r.second << std::endl;
                    overlap = true;
                    changed = true;
                    break;
                }
                if (! overlap) newBlockRanges.emplace_back(rule);
            }
        }
        blockRanges = newBlockRanges;
   
    }
    unsigned long maxIps{4294967296};
    for(std::pair<unsigned long, unsigned long> r : blockRanges) {
        if(r.first == 0) std::cout << "Answer part A: " << r.second+1 << std::endl;
        unsigned long len{r.second - r.first + 1};
        maxIps -= len;
    }
    std::cout << "Answer part B: " << maxIps << std::endl;
}