#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

std::set<std::pair<int,int>> dirs{{0,-1},{-1,0},{1,0},{0,1}};
std::map<char,char> enemy{{'E','G'},{'G','E'}};

struct unit
{
    int x,y;
    int hp{200};
    int attack{3};
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

struct path
{
    int startX, startY;
    int x,y,length;
    bool operator<(const path& rhs) const
    {
        if (length != rhs.length)
        {
            return length < rhs.length;
        }
        else
        {
            if (y != rhs.y)
            {
                return y < rhs.y;
            }
            else if (x != rhs.x)
            {
                return x < rhs.x;
            }
            else if (startY != rhs.startY)
            {
                return startY < rhs.startY;
            }
            else
            {
                return startX < rhs.startX;
            }
        }
    }

    bool operator>(const path& rhs) const
    {
        if (length != rhs.length)
        {
            return length > rhs.length;
        }
        else
        {
            if (y != rhs.y)
            {
                return y > rhs.y;
            }
            else if (x != rhs.x)
            {
                return x > rhs.x;
            }
            else if (startY != rhs.startY)
            {
                return startY > rhs.startY;
            }
            else
            {
                return startX > rhs.startX;
            }
        }
    }
};


std::vector<std::vector<char>> map;
std::vector<unit> units;


void printMap()
{
    std::cout << "Map:" <<std::endl;
    for (int y{0}; y < map.size(); y++)
    {
        for (int x{0}; x < map[y].size(); x++)
        {
            std::cout << map[y][x];
        }
        for (unit u : units)
        {
            if (u.y == y)
            {
                std::cout << "\t " << u.type << "(" << u.hp << ")";
            }
        }
        std::cout << std::endl;
    }
}
// pair är (x,y)

void printUnits()
{
    for (unit u : units)
    {
        if (u.hp > 0)
        {
            std::cout << u.type << " (" << u.hp << ") pos " << u.x << "," << u.y << std::endl;
        }
    }
}

bool nextToEnemy(char type, std::pair<int,int> pos)
{
    for (unit u : units)
    {
        if (u.type == enemy[type])
        {
            for (std::pair<int,int> d : dirs)
            {
                if (pos.first + d.first == u.x && pos.second + d.second == u.y)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void makeMove(int id)
{
    //std::cout << id << " " << units[id].type << " " << units[id].x << "," << units[id].y << std::endl;
    if (units[id].hp <= 0) return;
    bool fightTime{false};
    if (nextToEnemy(units[id].type, {units[id].x, units[id].y}))
    {
        fightTime = true;
    }
    else
    {
        // Possible locations
        // Reachable
        // BFS search!
        std::set<std::pair<int,int>> visited;
        std::priority_queue<path, std::vector<path>, std::greater<path>> heads;
        for (auto d : dirs)
        {
            int x{units[id].x + d.first}, y{units[id].y + d.second};
            //std::cout << x << "," << y << " m " << map[y][x] << std::endl;
            if (map[y][x] == '.')
            {
                path p;
                p.length = 1;
                p.startX = x;
                p.startY = y;
                p.x = x;
                p.y = y;
                heads.push(p);
                visited.insert({x,y});
            }
        }
        //std::cout << heads.size() << std::endl;
        std::priority_queue<path, std::vector<path>, std::greater<path>> paths;
        bool foundPath{false};
        int foundLength{-1};
        while(!heads.empty())
        {
            std::set<std::pair<int,int>> newVisited;
            path h = heads.top();
            heads.pop();
            //std::cout << heads.size() << " " << h.x << "," << h.y << " " << h.length << " start " << h.startX << "," << h.startY << std::endl;
            //std::cout << foundLength << std::endl;
            if (nextToEnemy(units[id].type, {h.x,h.y}))
            {
                foundPath = true;
                if (foundLength == -1) foundLength = h.length;
                paths.push(h);
            }
            else if (((h.length < foundLength) || (foundLength == -1)))
            {
                for (auto d : dirs)
                {
                    int x{h.x+d.first}, y{h.y+d.second};
                    if (map[y][x] == '.' && (!visited.contains({x,y})))
                    {
                        path p;
                        p.startX = h.startX;
                        p.startY = h.startY;
                        p.x = x;
                        p.y = y;
                        p.length = h.length+1;
                        heads.push(p);
                        visited.insert({x,y});
                    }
                }
            }
        }
        //std::cout << paths.size() << std::endl;
        if (!paths.empty())
        {

            path p = paths.top();
            //std::cout << p.length << " target " << p.x << "," << p.y << " start " << p.startX << "," << p.startY << std::endl;
            map[units[id].y][units[id].x] = '.';
            map[p.startY][p.startX] = units[id].type;
            units[id].x = p.startX;
            units[id].y = p.startY;
            if (p.length == 1) fightTime = true;
        }
    }
    if (fightTime)
    {
        int enemyId{-1};
        int enemyHp{201};
        for (auto d : dirs)
        {
            
            int x{units[id].x + d.first}, y{units[id].y + d.second};
            //std::cout << "Checking " << x << "," << y << ":";
            if (map[y][x] == enemy[units[id].type])
            {
                //std::cout << " found enemy ";
                for (int i{0}; i < units.size(); i++)
                {
                    if (units[i].x==x && units[i].y==y )
                    {
                        //std::cout << " enemy hp is " << units[i].hp << " current smallest is " << enemyHp << " with id " << enemyId;
                        if (units[i].hp < enemyHp)
                        {
                            //std::cout << " updating enemyHp and id ";
                            enemyHp = units[i].hp;
                            enemyId = i;
                            //std::cout << enemyHp << " " << enemyId;
                        }
                        else if (units[i].hp == enemyHp)
                        {
                            if (units[i].y < units[enemyId].y)
                            {
                                enemyId = i;
                            }
                            else if (units[i].y == units[enemyId].y)
                            {
                                if (units[i].x < units[enemyId].x)
                                {
                                    enemyId = i;
                                }
                            }
                            
                        }
                        
                    }
                }
            }
            //std::cout << std::endl;
        }
        //std::cout << units[id].x << "," << units[id].y << " fights " << units[enemyId].x << "," << units[enemyId].y << " with hp " << units[enemyId].hp << std::endl;
        units[enemyId].hp -= units[id].attack;
        if (units[enemyId].hp <= 0)
        {
            map[units[enemyId].y][units[enemyId].x] = '.';
            units[enemyId].x = -1;
            units[enemyId].y = -1;
        }

    }
}

bool battle(std::vector<std::vector<char>> startMap, std::vector<unit> startUnits, int elfAttack, bool partB)
{
    //std::cout << elfAttack << std::endl;
    map = startMap;
    units = startUnits;
    for (int i{0}; i < units.size(); i++)
    {
        if (units[i].type == 'E') units[i].attack = elfAttack;
    }
    bool won{false};
    int round{0};
    while(!won)
    {
        //std::cout << "Round " << round << std::endl;
        //printMap();
        int hpE{0}, hpG{0};
        std::sort(units.begin(), units.end());
        for (int i{0}; i < units.size(); i++)
        {
            //std::cout << i << " " << units[i].type << "(" << units[i].hp << ")" << " pos " << units[i].x << "," << units[i].y << std::endl;
            hpE = 0;
            hpG = 0;
            for (unit u : units)
            {
                if (u.hp > 0)
                {
                    if (u.type == 'E')
                    {
                        hpE += u.hp;
                    }
                    else
                    {
                        hpG += u.hp;
                    }
                }
                else if (u.hp <= 0 && u.type == 'E')
                {
                    //std::cout << "Fail after t=" << round << std::endl;
                    //printMap();
                    return false;
                }
                
            }
            makeMove(i);
        }
        
        if (hpG ==0)
        { 
            //std::cout << "Attack " << elfAttack << " rounds " << round << " hp left " << hpE << std::endl;
            //printMap();
            won = true;
            long ansB = round * hpE;
            std::cout << "Answer part B: " << ansB << std::endl;
            return true;
        }
        else
        {
            ++round;
        }

    }
    std::cout << "End of loop!" << std::endl;
    return true;

}

int main(int argc, char const *argv[])
{
    std::vector<std::vector<char>> startMap;
    std::vector<unit> startUnits;
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
            x = 0;
            for (char c : line)
            {
                if (c == 'G' || c == 'E')
                {
                    unit u;
                    u.x = x;
                    u.y = y;
                    u.type = c;
                    startUnits.push_back(u);
                    
                }
                row.push_back(c);
                ++x;
            }
            startMap.push_back(row);
            ++y;
        }
    }
    myfile.close();
    map = startMap;
    units = startUnits;
    bool combat{true};
    int round{0};
    int ansA{0};
    while(combat)
    {
        //std::cout << "Round " << round << std::endl;
        //printMap();
        int hpE{0}, hpG{0};
        std::sort(units.begin(), units.end());
        for (int i{0}; i < units.size(); i++)
        {
            //std::cout << i << " " << units[i].type << "(" << units[i].hp << ")" << " pos " << units[i].x << "," << units[i].y << std::endl;
            hpE = 0;
            hpG = 0;
            for (unit u : units)
            {
                if (u.hp > 0)
                {
                    if (u.type == 'E')
                    {
                        hpE += u.hp;
                    }
                    else
                    {
                        hpG += u.hp;
                    }
                }
            }
            makeMove(i);
        }
        
        if (hpE == 0 || hpG ==0)
        { 
            combat = false;
            std::cout << hpE << " " << hpG << std::endl;
            ansA = round * (hpE + hpG);
        }
        else
        {
            ++round;
        }

    }
    //printMap();
    std::cout << "Answer part A: " << ansA << std::endl;

    int elfAttack{4};
    //battle(startMap, startUnits, 9, true);
    while(!battle(startMap, startUnits, elfAttack, true)) ++elfAttack;
}