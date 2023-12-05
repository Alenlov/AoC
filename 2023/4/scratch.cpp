#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

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
    long sumA{0};
    std::unordered_map<int,int> scratchcards;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> cardSplit = splitLine(line, ": ");
            std::vector<std::string> card = splitLine(cardSplit[0], " ");
            int cardId = std::stoi(card[1]);
            ++scratchcards[cardId];
            std::vector<std::string> numSplit = splitLine(cardSplit[1], " | ");
            std::vector<std::string> winning = splitLine(numSplit[0], " ");
            std::vector<std::string> numbers = splitLine(numSplit[1], " ");
            std::unordered_set<int> winningNumbers;
            for(std::string s : winning)
            {
                winningNumbers.insert(std::stoi(s));
            }
            long val{0};
            int numMatch{0};
            for (std::string s : numbers)
            {
                int n = std::stoi(s);
                if (winningNumbers.contains(n))
                {  
                    ++numMatch;
                    if (val == 0)
                    {
                        val = 1;
                    }
                    else
                    {
                        val *= 2;
                    }
                }
            }
            sumA += val;
            for (int i{1}; i <= numMatch; i++)
            {
                scratchcards[cardId+i] += scratchcards[cardId];
            }
        }
    }
    myfile.close();
    long sumB{0};
    for (auto const [k,v] : scratchcards)
    {
        sumB += v;
    }
    std::cout << "Answer part A: " << sumA << std::endl;
    std::cout << "Answer part B: " << sumB << std::endl;
}