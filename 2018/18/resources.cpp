#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

std::vector<int> diffs {-1,0,1};

std::vector<std::vector<char>> updateArea(std::vector<std::vector<char>> cur)
{
    std::vector<std::vector<char>> next = cur;
    for (int y{0}; y < cur.size(); y++)
    {
        for (int x{0}; x < cur[y].size(); x++)
        {
            char c{cur[y][x]};
            if (c == '.')
            {
                int numTree{0};
                for (int dy : diffs)
                {
                    for (int dx : diffs)
                    {
                        if (dy != 0 || dx != 0)
                        {
                            int newY = y + dy;
                            int newX = x + dx;
                            if (newY >= 0 && newY < cur.size() && newX >= 0 && newX < cur[y].size())
                            {
                                if (cur[newY][newX] == '|') ++numTree;
                            }
                        }
                    }
                }
                if (numTree >= 3) next[y][x] = '|';
            }
            else if (c =='|')
            {
                int numLumber{0};
                for (int dy : diffs)
                {
                    for (int dx : diffs)
                    {
                        if (dy != 0 || dx != 0)
                        {
                            int newY = y + dy;
                            int newX = x + dx;
                            if (newY >= 0 && newY < cur.size() && newX >= 0 && newX < cur[y].size())
                            {
                                if (cur[newY][newX] == '#') ++numLumber;
                            }
                        }
                    }
                }
                if (numLumber >= 3) next[y][x] = '#';
            }
            else if (c == '#')
            {
                int numLumber{0}, numTree{0};
                for (int dy : diffs)
                {
                    for (int dx : diffs)
                    {
                        if (dy != 0 || dx != 0)
                        {
                            int newY = y + dy;
                            int newX = x + dx;
                            if (newY >= 0 && newY < cur.size() && newX >= 0 && newX < cur[y].size())
                            {
                                if (cur[newY][newX] == '#') ++numLumber;
                                if (cur[newY][newX] == '|') ++numTree;
                            }
                        }
                    }
                }
                if (numLumber == 0 || numTree == 0) next[y][x] = '.';
            }
            
            
        }
    }
    return next;
}

void printMap(std::vector<std::vector<char>> mapOfArea)
{
    for (auto row : mapOfArea)
    {
        for (auto c : row)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

int calcScore(std::vector<std::vector<char>> mapOfArea)
{
    int numTree{0}, numLumb{0};
    for (auto row : mapOfArea)
    {
        for (auto c : row)
        {
            if (c == '#') ++numLumb;
            if (c == '|') ++numTree;
        }
    }
    return numLumb*numTree;
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
    std::vector<std::vector<char>> mapOfArea;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<char> row;
            for (char c : line) row.push_back(c);
            mapOfArea.push_back(row);
        }
    }
    myfile.close();
    int ansA{0};
    std::map<int,std::vector<int>> scorePerTime;
    int time{0};
    scorePerTime[calcScore(mapOfArea)].push_back(time);
    while(true)
    {
        ++time;
        mapOfArea = updateArea(mapOfArea);
        //std::cout << "After " << time << "min" << std::endl;
        //printMap(mapOfArea);
        //std::cout << std::endl;
        if (time == 10) ansA = calcScore(mapOfArea);
        scorePerTime[calcScore(mapOfArea)].push_back(time);
        if (scorePerTime[calcScore(mapOfArea)].size()>3) break;
    }
    int timeB{1000000000};
    int ansB{0};
    std::cout << "Answer part A " << ansA << std::endl;
    for (auto const [k,v] : scorePerTime)
    {
        if (v.size() > 2)
        {
            int lastTime{v[v.size()-1]};
            int diff{lastTime - v[v.size()-2]};
            if ( (timeB - lastTime) % diff == 0)
            {
                ansB = k;
                break;
            }
        }
    }
    std::cout << "Answer part B " << ansB << std::endl;
}