#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <list>
#include <unordered_map>

struct event
{
    std::string text;
    int y, mo, d, h, m;
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

std::pair<int,int> nextDay(int mon, int day)
{
    if (day < 30)
    {
        return {mon, day+1};
    }
    else if (day == 30)
    {
        if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
        {
            return {mon+1, day};
        }
        else
        {
            return {mon, day + 1};
        }
    }
    else if (day == 31)
    {
        return {mon + 1, day};
    }
    else
    {
        std::cout << "ERROR!" << mon << " " << day << std::endl;
        return {0,0};
    }
    
    
}

bool sameDay(event e1, event e2)
{
    int month = e1.mo;
    int day = e1.d;
    if (e1.h == 23)
    {
        std::pair<int,int> nD = nextDay(e1.mo, e1.d);
        month = nD.first;
        day = nD.second;
    }
    if ( (month == e2.mo) && (day == e2.d) )
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
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
    std::list<event> allEvents;
    const std::regex reFull("\\[(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2})\\] ([\\w\\d\\W]+)");
    const std::regex reGuard("Guard #(\\d+) begins shift");
    std::smatch m;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            if (std::regex_match(line, m, reFull))
            {
                for(int i = 1; i < m.size(); i ++)
                {
                    std::cout << m[i] << " ";
                }
                std::cout << std::endl;

            }
            event e;
            e.text = m[6];
            e.y = std::stoi(m[1]);
            e.mo = std::stoi(m[2]);
            e.d = std::stoi(m[3]);
            e.h = std::stoi(m[4]);
            e.m = std::stoi(m[5]);
            allEvents.push_back(e);
        }
    }
    myfile.close();
    std::unordered_map<int, std::unordered_map<int,int>> guardSleep;
    for (event e : allEvents)
    {
        if (std::regex_match(e.text, m, reGuard))
        {
            std::vector<int> times;
            int guardId = std::stoi(m[1]);
            for (event e2 : allEvents)
            {
                if (!std::regex_match(e2.text, m, reGuard))
                {
                    if (sameDay(e,e2))
                    {
                        times.push_back(e2.m);
                    }
                }
            }
            std::sort(times.begin(), times.end());
            for (int i = 0; i < times.size(); i += 2)
            {
                for(int t = times[i] ; t < times[i+1]; t++)
                {
                    ++guardSleep[guardId][t];
                }
            }            
        }
    }
    int maxTime{-1}, maxId{0}, maxIdB{0}, maxTimeB{-1}, maxHB{0};
    for (auto [id, sleep] : guardSleep)
    {
        int totSleep{0};
        for (auto [h,c] : sleep)
        {
            totSleep += c;
            if (c > maxTimeB)
            {
                maxTimeB = c;
                maxHB = h;
                maxIdB = id;
            }
        }
        if (totSleep > maxTime)
        {
            maxTime = totSleep;
            maxId = id;
        }
    }
    int maxC{-1}, maxH{0};
    for (auto [h, c] : guardSleep[maxId])
    {
        if (c > maxC)
        {
            maxC = c;
            maxH = h;
        }
    }
    std::cout << "Answer part A: " << maxH * maxId << std::endl;
    std::cout << "Answer part B: " << maxHB * maxIdB << std::endl;
}