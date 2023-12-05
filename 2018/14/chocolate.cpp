#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <utility>
#include <algorithm>


int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    std::list<int> score;
    int numRecepies;
    if (argc > 1)
    {
        numRecepies = std::stoi(argv[1]);

        for (char c : std::string(argv[1]))
        {
            score.push_back(int(c)-int('0'));
        }
    }
    else
    {
        return -1;
    }
    
    long ansA{0}, pow{1}, ansB{0};
    std::list<int> recepies{3,7};
    auto first = recepies.begin();
    auto second = recepies.end();
    --second;
    while(ansA == 0 || ansB == 0)
    {
        if (recepies.size() >= numRecepies + 10 && ansA == 0)
        {
            auto it = recepies.end();
            for (int i = 0; i < 10; i++)
            {
                --it;
                ansA += pow * (*it);
                pow *= 10;
            }
        }
        int fE = *first;
        int sE = *second;
        
        
        bool addedTwo{false};
        int val = fE + sE;
        if (val >= 10)
        {
            recepies.push_back(val/10);
            recepies.push_back(val % 10);
            addedTwo = true;
        }
        else
        {
            recepies.push_back(val);
        }
        for (int i = 0; i <= fE; i++)
        {
            ++first;
            if (first == recepies.end()) first = recepies.begin();
        }
        for (int i = 0; i <= sE; i++)
        {
            ++second;
            if (second == recepies.end()) second = recepies.begin();
        }
        if (ansB == 0)
        {
            auto itR = recepies.end();
            auto itS = score.end();
            bool match{true};
            for (int i = 0; i < score.size(); i++)
            {
                --itR;
                --itS;
                if ((*itR) != (*itS))
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                ansB = recepies.size() - score.size();
            }
            if (!match && addedTwo)
            {
                match = true;
                itR = recepies.end();
                --itR;
                itS = score.end();
                for (int i = 0; i < score.size(); i++)
                {
                    --itR;
                    --itS;
                    if ((*itR) != (*itS))
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    ansB = recepies.size() - score.size() - 1;
                }
            }
        }
    }
    

    

    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << ansB << std::endl;
    
    
}