#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <map>
#include <queue>

struct test
{
    char cat{' '};
    char relation{' '};
    int value{0};
    std::string ruleIfTrue;

    bool match(std::map<char,int> part)
    {
        if (cat == ' ') return true;
        if (part.contains(cat))
        {
            if (relation == '>')
            {
                return part[cat] > value;
            }
            else if (relation == '<')
            {
                return part[cat] < value;
            }
            
        }
        return false;
    }
};

struct range
{
    long min{1}, max{4000};
};



struct rule
{
    std::string name;
    std::vector<test> tests;
};


std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos && (indx < line.length()))
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
    const std::regex ruleMatch("([a-z]+)\\{(.*)\\}");
    const std::regex testMatch("([xmas])([<>])(\\d*):([a-zAR]+)");
    const std::regex partMatch("\\{x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)\\}");
    std::smatch m, m2;
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
    std::map<std::string, rule> rules;
    std::vector<std::map<char,int>> parts;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            if (std::regex_match(line, m, ruleMatch))
            {
                rule r;
                r.name = m[1];
                std::vector<std::string> tests = splitLine(m[2],",");
                for (std::string tes : tests)
                {
                    test t;
                    if (std::regex_match(tes, m2, testMatch))
                    {
                        t.cat = std::string(m2[1])[0];
                        t.relation =  std::string(m2[2])[0];
                        t.value = std::stoi(m2[3]);
                        t.ruleIfTrue = m2[4];
                    }
                    else
                    {
                        t.ruleIfTrue = tes;
                    }
                    r.tests.push_back(t);
                }
                rules[r.name] = r;
            }
            else if (std::regex_match(line, m, partMatch))
            {
                std::map<char,int> part;
                part['x'] = std::stoi(m[1]);
                part['m'] = std::stoi(m[2]);
                part['a'] = std::stoi(m[3]);
                part['s'] = std::stoi(m[4]);
                parts.push_back(part);
            }
            
        }
    }
    myfile.close();
    //std::cout << rules.size() << " - " << parts.size() << std::endl;
    long ansA{0};
    for (auto p : parts)
    {
        std::string cur{"in"};
        bool foundEnd{false};
        while(!foundEnd)
        {
            for (test t : rules[cur].tests)
            {
                if (t.match(p))
                {
                    cur = t.ruleIfTrue;
                    break;
                }
            }
            if (cur == "A" || cur == "R")
            {
                foundEnd = true;
            }
        }
        if (cur == "A")
        {
            for (auto const [c, v] : p)
            {
                ansA += v;
            }
        }
    }
    std::cout << "Answer part A: " << ansA << std::endl;

    std::queue<std::pair<std::string, std::map<char,range>>> curToPart;
    long ansB{0};
    curToPart.push({"in", {{'x',{1,4000}},{'m',{1,4000}},{'a',{1,4000}},{'s',{1,4000}}}});
    while (!curToPart.empty())
    {
        std::string cur = curToPart.front().first;
        std::map<char,range> partRange = curToPart.front().second;
        curToPart.pop();
        //std::cout << curToPart.size() << " " << cur;
        //for (auto const [c, r] : partRange) std::cout << " " << c << ":" << r.min << "-" << r.max << std::endl;
        if(cur == "A")
        {
            long numCombs{1};
            for (auto const [t, v] : partRange)
            {
                numCombs *= (v.max - v.min + 1);
            }
            ansB += numCombs;
            continue;
        }
        else if (cur == "R")
        {
            continue;
        }
        else
        {    
            bool moreRules{true};
            for (test t : rules[cur].tests)
            {
                //std::cout << t.cat << std::endl;
                if (t.cat == ' ')
                {
                    curToPart.push({t.ruleIfTrue,partRange});
                    moreRules = false;
                }
                else
                {
                    
                    if (t.relation == '<')
                    {
                        if (partRange[t.cat].min < t.value)
                        {
                            if (partRange[t.cat].max < t.value)
                            {
                                curToPart.push({t.ruleIfTrue, partRange});
                                moreRules = false;
                            }
                            else
                            {
                                std::map<char,range> newPartRange = partRange;
                                newPartRange[t.cat].max = t.value-1;
                                curToPart.push({t.ruleIfTrue, newPartRange});
                                partRange[t.cat].min = t.value;
                            }
                        }
                    }
                    else if (t.relation == '>')
                    {
                        if (partRange[t.cat].max > t.value)
                        {
                            if (partRange[t.cat].min > t.value)
                            {
                                curToPart.push({t.ruleIfTrue, partRange});
                                moreRules = false;
                            }
                            else
                            {
                                std::map<char,range> newPartRange = partRange;
                                newPartRange[t.cat].min = t.value+1;
                                curToPart.push({t.ruleIfTrue, newPartRange});
                                partRange[t.cat].max = t.value;
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Tankevurpa" << std::endl;
                    }
                    
                    
                }
            }
        }
        
    }
    std::cout << "Answer part B: " << ansB << std::endl;
}