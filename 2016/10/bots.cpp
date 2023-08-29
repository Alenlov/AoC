#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Bot 
{
    public:

    int val1 = 0;
    int val2 = 0;
    Bot* highBot = nullptr;
    Bot* lowBot = nullptr;
    int numSet = 0;
    bool done = false;

    Bot() = default;

    void setBots(Bot* high, Bot* low)
    {
        setHighBot(high);
        setLowBot(low);
    }

    void setLowBot(Bot* low)
    {
        lowBot = low;
        numSet += 1;
        if(allValues())
        {
            giveVals();
        }
        return;
    }

    void setHighBot(Bot* high)
    {
        highBot = high;
        numSet += 1;
        if(allValues())
        {
            giveVals();
        }
        return;
    }

    void setVal(int val)
    {
        if(val1 == 0)
        {
            val1 = val;
        } 
        else if (val2 == 0) 
        {
            val2 = val;
        } 
        else 
        {
            std::cout << "ERROR! (setVal)" << std::endl;
            return;
        }
        numSet += 1;
        if(allValues())
        {
            giveVals();
        }
        return;
    }

    bool allValues()
    {
        return numSet == 4;
    }

    bool hasValues(int v1, int v2){
        return (val1 == v1 && val2 == v2) || (val1 == v2 && val2 == v1);
    }

    void giveVals()
    {
        if(allValues())
        {
            if(val1 < val2)
            {
                lowBot->setVal(val1);
                highBot->setVal(val2);
            }
            else
            {
                lowBot->setVal(val2);
                highBot->setVal(val1);
            }
        }
    }


};

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

    std::map<int,Bot*> bots;
    std::map<int,Bot*> outputs;

    // Bot* bot1 = new Bot();
    // Bot* bot2 = new Bot();
    // Bot* bot3 = new Bot();

    // bot1->setVal(1);
    // bot1->setVal(2);
    // bot2->setBots(bot1, bot3);
    // bot2->setVal(3);
    // bot1->setBots(bot2, bot3);
    
    // std::cout << bot2->val1 << " " << bot2->val2 << " " << bot3->val1 << " " << bot3->val2 << std::endl;

    myfile.open(argv[1]);
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> lineVec = splitLine(line);
            if(lineVec.at(0) == "value")
            {
                int val = std::stoi(lineVec.at(1));
                int botNum = std::stoi(lineVec.at(5));
                if(bots.find(botNum) == bots.end())
                {
                    bots[botNum] = new Bot();
                }
                bots[botNum]->setVal(val);
            }
            else
            {
                int botNum = std::stoi(lineVec.at(1));
                if(bots.find(botNum) == bots.end())
                {
                    bots[botNum] = new Bot();
                }
                int lowNum = std::stoi(lineVec.at(6));
                int highNum = std::stoi(lineVec.at(11));
                if(lineVec.at(5) == "bot")
                {
                    if(bots.find(lowNum) == bots.end())
                    {
                        bots[lowNum] = new Bot();
                    }
                    bots[botNum]->setLowBot(bots[lowNum]);
                }
                else
                {
                    if(outputs.find(lowNum) == outputs.end())
                    {
                        outputs[lowNum] = new Bot();
                    }
                    bots[botNum]->setLowBot(outputs[lowNum]);
                }
                if(lineVec.at(10) == "bot")
                {
                    if(bots.find(highNum) == bots.end())
                    {
                        bots[highNum] = new Bot();
                    }
                    bots[botNum]->setHighBot(bots[highNum]);
                }
                else
                {
                    if(outputs.find(highNum) == outputs.end())
                    {
                        outputs[highNum] = new Bot();
                    }
                    bots[botNum]->setHighBot(outputs[highNum]);
                }
            }
        }
    }
    for(auto const& [num, bot] : bots)
    {
        if(bot->hasValues(61,17))
        {
            std::cout << "Answer part A: bot number " << num << " compares the chips" << std::endl;
        }
    }
    std::cout << "Answer part B: the product is " << (outputs[0]->val1 * outputs[1]->val1 * outputs[2]->val1) << std::endl;
}