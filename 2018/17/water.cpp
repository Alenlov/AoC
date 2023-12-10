#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <set>
#include <queue>

int main(int argc, char const *argv[])
{
    const std::regex clayMatch("([xy])=(\\d+), ([xy])=(\\d+)..(\\d+)");
    std::smatch m;
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
    int minX{500}, maxX{500};

    int minY{1<<30}, maxY{0};
    std::set<std::pair<int,int>> clay;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            if (std::regex_match(line, m, clayMatch))
            {
                int ymin, ymax, xmin, xmax;
                if (m[1] == 'x')
                {
                    int x = std::stoi(m[2]);
                    ymin = std::stoi(m[4]);
                    ymax = std::stoi(m[5]);
                    for (int y = ymin; y <= ymax; y++)
                    {
                        clay.insert({x,y});
                    }
                    xmin = x;
                    xmax = x;
                }
                else if (m[1] == 'y')
                {
                    int y = std::stoi(m[2]);
                    xmin = std::stoi(m[4]);
                    xmax = std::stoi(m[5]);
                    for (int x = xmin; x <= xmax; x++)
                    {
                        clay.insert({x,y});
                    }
                    ymin = y;
                    ymax = y;
                }
                if (ymin < minY) minY = ymin;
                if (ymax > maxY) maxY = ymax;
                if (xmin < minX) minX = xmin;
                if (xmax > maxX) maxX = xmax;
                
            }
        }
    }
    myfile.close();
    std::cout << clay.size() << " " << minY << " - " << maxY << std::endl;

    std::set<std::pair<int,int>> waterResting, waterReachable;
    waterReachable.insert({500,0});
    std::queue<std::pair<int,int>> heads;
    heads.push({500,0});
    while(heads.size() > 0)
    {
        std::pair<int,int> h = heads.front();
        heads.pop();
        if (h.second >= maxY) continue;
        std::pair<int,int> oneDown = {h.first, h.second+1};
        if (!(clay.contains(oneDown) || waterResting.contains(oneDown)))
        {
            if (!waterReachable.contains(oneDown))
            {
                heads.push(oneDown);
                waterReachable.insert(oneDown);
            }
        }
        else
        {
            bool couldFill{false};
            std::pair<int,int> oneRight{h.first+1,h.second}, oneLeft{h.first-1, h.second};
            if (!(clay.contains(oneRight) || waterReachable.contains(oneRight) || waterResting.contains(oneRight)))
            {
                heads.push(oneRight);
                waterReachable.insert(oneRight);
                couldFill = true;
            }
            if (!(clay.contains(oneLeft) || waterReachable.contains(oneLeft) || waterResting.contains(oneLeft)))
            {
                heads.push(oneLeft);
                waterReachable.insert(oneLeft);
                couldFill = true;
            }
            if (!couldFill)
            {
                // Check if we have a filled row between two clay!
                std::set<std::pair<int,int>> possible;
                possible.insert(h);
                std::pair<int,int> clayLeft = {h.first-1, h.second};
                while( waterReachable.contains(clayLeft) )
                {
                    possible.insert(clayLeft);    
                    clayLeft.first -= 1;
                }
                std::pair<int,int> clayRight = {h.first+1, h.second};
                while( waterReachable.contains(clayRight) )
                {
                    possible.insert(clayRight);
                    clayRight.first += 1;
                }
                if (clay.contains(clayLeft) && clay.contains(clayRight))
                {
                    //std::cout << "Found clay between " << clayLeft.first << " " << clayRight.first << std::endl;
                    for (auto p : possible)
                    {
                        //std::cout << "Resting " << p.first << "," << p.second << std::endl;
                        waterReachable.erase(p);
                        waterResting.insert(p);
                        if (waterReachable.contains({p.first,p.second-1})) heads.push({p.first,p.second-1});
                    }
                }
                
            }
        }
    }
    int ansA{0};
    for (auto p : waterReachable)
    {
        if (p.second <= maxY && p.second >= minY) ++ansA;
        if (p.first > maxX) maxX = p.first;
        if (p.first < minX) minX = p.first;
    }
    for (auto p : waterResting)
    {
        if (p.second <= maxY && p.second >= minY) ++ansA;
        if (p.first > maxX) maxX = p.first;
        if (p.first < minX) minX = p.first;
    }

    /*for (int y{0}; y <= maxY; y++)
    {
        for (int x{minX}; x<=maxX; x++)
        {
            if (clay.contains({x,y})) std::cout << "#";
            else if (waterReachable.contains({x,y})) std::cout << "|";
            else if (waterResting.contains({x,y})) std::cout << "~";
            else std::cout << " ";
            
        }
        std::cout << std::endl;
    }*/

    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << waterResting.size() << std::endl;
}