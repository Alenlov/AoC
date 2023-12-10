#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>

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

struct sequence
{
    std::vector<long> seq;
    
    std::pair<long,long> calcNextVal()
    {
        std::unordered_set<long> vals;
        for (long l : seq)
        {
            vals.insert(l);
        }
        long lastVal = seq[seq.size() - 1];
        long firstVal = seq[0];
        if (vals.size() == 1)
        {
            return {firstVal,lastVal};
        }
        else
        {
            std::vector<long> diff(seq.size()-1);
            for (int i{0}; i < seq.size()-1; i++)
            {
                diff[i] = seq[i+1] - seq[i];
            }
            seq = diff;

            std::pair<long,long> nextVals = this->calcNextVal();
            return {firstVal-nextVals.first, lastVal+nextVals.second};
        }
    }
};


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
    std::vector<sequence> sequences;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            sequence seq;
            for (std::string s : splitLine(line, " "))
            {
                seq.seq.push_back(std::stol(s));
            }
            sequences.push_back(seq);
        }
    }
    myfile.close();
    long ansA{0};
    long ansB{0};
    for (sequence s : sequences)
    {
        std::pair<long, long> nextValS = s.calcNextVal();
        /* std::cout << nextValS.first << " ";
        for (long l : s.seq)
        {
            std::cout << l << " ";
        }
        std::cout << nextValS.second;
        std::cout << std::endl;*/
        
        ansA += nextValS.second;
        ansB += nextValS.first;
    }
    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << ansB << std::endl;
}