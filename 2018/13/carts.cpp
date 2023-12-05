#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <list>

std::map<char, std::pair<int,int>> dirs{ {'v',{0,1}},{'^',{0,-1}},{'<',{-1,0}},{'>',{1,0}}};
std::map<int, char> turnOrder {{0,'l'},{1,'s'},{2,'r'}};
std::map<char,char> turnLeft{ {'>','^'},{'^','<'},{'<','v'},{'v','>'}};
std::map<char,char> turnRight{ {'>','v'},{'v','<'},{'<','^'},{'^','>'}};


struct cart
{
    int x,y;
    char dir;
    int turn{0};
    bool operator<(const cart& rhs) const
    {
        if (y != rhs.y)
        {
            return rhs.y < y;
        }
        else
        {
            return rhs.x < x;
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
    std::vector<std::vector<char>> trackLayout;
    std::priority_queue<cart> carts;
    int x{0},y{0};
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            x = 0;
            std::vector<char> row{};
            for (char c : line)
            {
                if (c == '\\') std::cout << c << std::endl;
                if (dirs.contains(c))
                {
                    if (c == '<' || c == '>') row.push_back('-');
                    if (c == 'v' || c == '^') row.push_back('|');
                    cart mc;
                    mc.x = x;
                    mc.y = y;
                    mc.dir = c;
                    carts.push(mc);
                }
                else
                {
                    row.push_back(c);
                }
                x++;
            }
            trackLayout.push_back(row);
            y++;
        }
    }
    myfile.close();
    bool noCrash{true};
    std::pair<int,int> firstCrash;
    while(carts.size() > 1)
    {
        std::cout << "Size = " << carts.size() << std::endl;
        std::list<cart> newCarts;
        std::set<std::pair<int,int>> cartPos;
        while(!carts.empty())
        {
            cart c = carts.top();
            carts.pop();
            if (cartPos.contains({c.x,c.y}))
            {
                std::cout << "Crash! " << newCarts.size() << " at " << c.x << "," << c.y << std::endl;
                    if (noCrash)
                    {
                        noCrash = false;
                        firstCrash = {c.x,c.y};
                    }
                    std::list<cart>::iterator i = newCarts.begin();
                    while (i != newCarts.end())
                    {
                        if ((*i).x == c.x && (*i).y == c.y)
                        {
                            i = newCarts.erase(i);
                        }
                        else
                        {
                            ++i;
                        }
                    }
                    std::cout << "Crash! " << newCarts.size() << " at " << c.x << "," << c.y << std::endl;
            }
            else
            {
                c.x += dirs[c.dir].first;
                c.y += dirs[c.dir].second;

                if (cartPos.contains({c.x,c.y}))
                {
                    std::cout << "Crash! " << newCarts.size() << " at " << c.x << "," << c.y << std::endl;
                    if (noCrash)
                    {
                        noCrash = false;
                        firstCrash = {c.x,c.y};
                    }
                    std::list<cart>::iterator i = newCarts.begin();
                    while (i != newCarts.end())
                    {
                        if ((*i).x == c.x && (*i).y == c.y)
                        {
                            i = newCarts.erase(i);
                        }
                        else
                        {
                            ++i;
                        }
                    }
                    std::cout << "Crash! " << newCarts.size() << " at " << c.x << "," << c.y << std::endl;

                }
                else
                {
                    cartPos.insert({c.x,c.y});
                    if ((trackLayout[c.y][c.x] != '|') && (trackLayout[c.y][c.x] != '-') )
                    {
                        if (trackLayout[c.y][c.x] == '/') {
                            if (c.dir == '^' || c.dir == 'v')
                            {
                                c.dir = turnRight[c.dir];
                            }
                            else if (c.dir == '<' || c.dir == '>')
                            {
                                c.dir = turnLeft[c.dir];
                            }
                        }
                        else if (trackLayout[c.y][c.x] == '\\')
                        {
                            if (c.dir == '^' || c.dir == 'v')
                            {
                                c.dir = turnLeft[c.dir];
                            }
                            else if (c.dir == '<' || c.dir == '>')
                            {
                                c.dir = turnRight[c.dir];
                            }
                        }
                        else if (trackLayout[c.y][c.x] == '+')
                        {
                            if (turnOrder[c.turn] == 'l')
                            {
                                c.dir = turnLeft[c.dir];
                            }
                            else if (turnOrder[c.turn] == 'r')
                            {
                                c.dir = turnRight[c.dir];
                            }
                            ++c.turn;
                            c.turn %= 3;
                            
                        }
                        
                        
                    }
                    newCarts.push_back(c);
                }
            }
            
        }
        for (cart c : newCarts) carts.push(c);
    }
    std::cout << "Answer part A: " << firstCrash.first << "," << firstCrash.second <<std::endl;
    std::cout << "Answer Part B: " << carts.top().x << "," << carts.top().y << std::endl;
}