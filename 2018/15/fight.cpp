#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

std::set<std::pair<int,int>> dirs{{1,0},{-1,0},{0,1},{0,-1}};
std::map<char,char> enemy{{'E','G'},{'G','E'}};

struct unit
{
    int x,y;
    int hp{200};
    char type;

    bool operator<(const unit& rhs) const
    {
        if (y != rhs.y)
        {
            return rhs.y > y;
        }
        else
        {
            return rhs.x > x;
        }
    }
};

std::vector<std::vector<char>> map;
std::vector<unit> units;

void makeMove(int id)
{
    char type = units[id].type;
    char otherType = enemy[type];
    std::queue<std::pair<int,int>> heads{};
    std::map<std::pair<int,int>,std::pair<std::pair<int,int>,int>> paths;

    bool move{true};

    for (auto d : dirs)
    {
        char c = map[units[id].y+d.second][units[id].x+d.first];
        if (c == '.')
        {
            heads.push({units[id].y+d.second,units[id].x+d.first});
            paths[{units[id].y+d.second,units[id].x+d.first}] = {{units[id].y+d.second,units[id].x+d.first},1};
        }
        else if (c == otherType)
        {
            move = false;
        }
    }
    
    if (move)
    {
        
    }
    else
    {

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
    
    int y{0},x{0};
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            std::vector<char> row;
            for (char c : line)
            {
                if (c == 'G' || c == 'E')
                {
                    unit u;
                    u.x = x;
                    u.y = y;
                    u.type = c;
                    units.push_back(u);
                    
                }
                row.push_back(c);
                ++x;
            }
            map.push_back(row);
            ++y;
        }
    }
    myfile.close();
    
}