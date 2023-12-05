#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <unordered_set>
#include <unordered_map>

struct steps
{
    char name;
    std::unordered_set<char> nextSteps;
    std::unordered_set<char> prevSteps;
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
    std::unordered_map<char, steps> allSteps, allStepsB;
    const std::regex reFull("Step ([A-Z]) must be finished before step ([A-Z]) can begin.");
    std::smatch m;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            if (std::regex_match(line, m, reFull))
            {
                std::string lhs = m[1];
                std::string rhs = m[2];
                if (allSteps.contains( lhs[0]))
                {
                    allSteps[lhs[0]].nextSteps.insert(rhs[0]);
                    allStepsB[lhs[0]].nextSteps.insert(rhs[0]);
                    
                }
                else
                {
                    steps s;
                    s.name = lhs[0];
                    s.nextSteps = {rhs[0]};
                    allSteps[lhs[0]] = s;
                    steps sB;
                    sB.name = lhs[0];
                    sB.nextSteps = {rhs[0]};
                    allStepsB[lhs[0]] = sB;
                }

            }
            
        }
    }
    myfile.close();
    
    for (auto [c,s] : allSteps)
    {
        for (auto o : s.nextSteps)
        {
            allSteps[o].prevSteps.insert(c);
        }
    }
    for (auto [c,s] : allStepsB)
    {
        for (auto o : s.nextSteps)
        {
            allStepsB[o].prevSteps.insert(c);
        }
    }
    
    std::string output{""};
    while(allSteps.size() > 0)
    {
        std::vector<char> candidates;
        for (auto [c,s] : allSteps)
        {
            if (s.prevSteps.empty())
            {
                candidates.push_back(c);
            }
        }
        if (candidates.size() > 1)
        {
            std::sort(candidates.begin(), candidates.end());
        }
        char c = candidates[0];
        output += c;
        for (char o : allSteps[c].nextSteps)
        {
            allSteps[o].prevSteps.erase(c);
        }
        allSteps.erase(c);
        
        
    }
    std::cout << "Answer part A: " << output << std::endl;

    int totTime{0};
    int numFreeWorkers{5};
    int timePerTask{61 - int('A')};
    std::unordered_map<char,int> workers;
    while(allStepsB.size() > 0)
    {
        std::vector<char> candidates;
        for (auto [c,s] : allStepsB)
        {
            if (s.prevSteps.empty())
            {
                candidates.push_back(c);
            }
        }
        if (candidates.size() > 1)
        {
            std::sort(candidates.begin(), candidates.end());
        }
        
        for (char c : candidates)
        {
            if (numFreeWorkers == 0) break;
            if (!workers.contains(c))
            {
                workers[c] = totTime + timePerTask + int(c);
                --numFreeWorkers;
            }
        }
        
        int minTime{1<<30};
        std::vector<char> toEnd{};
        for (auto [c,t] : workers)
        {
            if (t < minTime)
            {
                minTime = t;
                toEnd = {c};
            }
            else if (t == minTime)
            {
                toEnd.push_back(c);
            }
        }
        totTime = minTime;
        for (char e : toEnd)
        {
            for (char o : allStepsB[e].nextSteps)
            {
                allStepsB[o].prevSteps.erase(e);
            }
            allStepsB.erase(e);
            ++numFreeWorkers;
            workers.erase(e);
        }
    }

    std::cout << "Answer part B: " << totTime << std::endl;
}