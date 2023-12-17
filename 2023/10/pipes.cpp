#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <queue>
#include <map>

std::map<char, std::set<std::pair<int,int>>> dirs{ {'S',{{1,0}, {-1,0}, {0,1}, {0,-1}}}, {'-', {{1,0},{-1,0}}}, {'|', {{0,1},{0,-1}}}, {'L',{{1,0},{0,-1}}}, {'F',{{1,0},{0,1}}}, {'J',{{-1,0},{0,-1}}}, {'7',{{-1,0},{0,1}}} };



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
    std::vector<std::vector<char>> mapOfPipes;
    int y{0}, x{0}; 
    std::pair<int,int> startPos;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<char> row;
            x = 0;
            for (char c : line) 
            {
                row.push_back(c);
                if (c == 'S')
                {
                    startPos = {x,y};
                }
                x++;
            }
            mapOfPipes.push_back(row);
            y++;
        }
    }
    myfile.close();
    //std::cout << startPos.first << "," << startPos.second << std::endl;

    std::set<std::pair<int,int>> visited;
    std::queue<std::pair<int,int>> heads;
    heads.push(startPos);
    while(!heads.empty())
    {
        std::pair<int,int> h = heads.front();
        heads.pop();
        visited.insert(h);
        char curPos = mapOfPipes[h.second][h.first];
        std::set<char> startDirs;
        for (auto d : dirs[curPos])
        {
            if ((h.first+d.first >= 0) && (h.first + d.first < mapOfPipes[0].size()) && (h.second + d.second >= 0) && (h.second + d.second < mapOfPipes.size()) )
            {
                if (!visited.contains({h.first+d.first,h.second+d.second}))
                {
                    char dest = mapOfPipes[h.second+d.second][h.first+d.first];
                    if (dest == '-')
                    {
                        if (d.first != 0)
                        {
                            heads.push({h.first+d.first, h.second+d.second});
                            if (curPos == 'S')
                            {
                                if (d.first == 1)
                                {
                                    startDirs.insert('R');
                                }
                                else
                                {
                                    startDirs.insert('L');
                                }
                            }
                        }
                    }
                    else if (dest == '|')
                    {
                        if (d.second != 0)
                        {
                            heads.push({h.first+d.first, h.second+d.second});
                            if (curPos == 'S')
                            {
                                if (d.second == 1)
                                {
                                    startDirs.insert('D');
                                }
                                else
                                {
                                    startDirs.insert('U');
                                }
                            }
                        }
                    }
                    else if (dest == 'L')
                    {
                        if (d.first == -1 || d.second == 1)
                        {
                            heads.push({h.first+d.first, h.second+d.second});
                            if (curPos == 'S')
                            {
                                if (d.first == -1)
                                {
                                    startDirs.insert('L');
                                }
                                else
                                {
                                    startDirs.insert('D');
                                }
                            }
                        }
                    }
                    else if (dest == 'F')
                    {
                        if (d.first == -1 || d.second == -1)
                        {
                            heads.push({h.first+d.first, h.second+d.second});
                            if (curPos == 'S')
                            {
                                if (d.first == -1)
                                {
                                    startDirs.insert('L');
                                }
                                else
                                {
                                    startDirs.insert('U');
                                }
                            }
                        }
                    }
                    else if (dest == 'J')
                    {
                        if (d.first == 1 || d.second == 1)
                        {
                            heads.push({h.first+d.first, h.second+d.second});
                            if (curPos == 'S')
                            {
                                if (d.first == 1)
                                {
                                    startDirs.insert('R');
                                }
                                else
                                {
                                    startDirs.insert('D');
                                }
                            }
                        }
                    }
                    else if (dest == '7')
                    {
                        if (d.first == 1 || d.second == -1)
                        {
                            heads.push({h.first+d.first, h.second+d.second});
                            if (curPos == 'S')
                            {
                                if (d.first == 1)
                                {
                                    startDirs.insert('R');
                                }
                                else
                                {
                                    startDirs.insert('U');
                                }
                            }
                        }
                    }
                }
            }
        }
        if (curPos == 'S')
        {
            if(startDirs.size() == 2)
            {
                if (startDirs.contains('U'))
                {
                    if (startDirs.contains('L'))
                    {
                        mapOfPipes[h.second][h.first] = 'J';
                    }
                    else if (startDirs.contains('D'))
                    {
                        mapOfPipes[h.second][h.first] = '|';
                    }
                    else if (startDirs.contains('R'))
                    {
                        mapOfPipes[h.second][h.first] = 'L';
                    }
                }
                else if (startDirs.contains('R'))
                {
                    if (startDirs.contains('L'))
                    {
                        mapOfPipes[h.second][h.first] = '-';
                    }
                    else if (startDirs.contains('D'))
                    {
                        mapOfPipes[h.second][h.first] = 'F';
                    }
                }
                else if (startDirs.contains('D'))
                {
                    if (startDirs.contains('L'))
                    {
                        mapOfPipes[h.second][h.first] = '7';
                    }
                }
                
                
            }
            else
            {
                std::cout << "Big big tankevurpa!" << std::endl;
            }
        }
    }
    std::cout << "Answer part A " << visited.size()/2 << std::endl;
    int ansB{0};
    for (int y{0}; y < mapOfPipes.size(); y++)
    {
        bool inside{false};
        bool onPipes{false};
        char pipeStart;
        for (int x{0}; x < mapOfPipes[y].size(); x++)
        {
            if (visited.contains({x,y}))
            {
                char c = mapOfPipes[y][x];
                if (c == '|')
                {
                    inside = !inside;
                }
                else if (c == 'L' || c == 'F')
                {
                    if (!onPipes)
                    {
                        onPipes = true;
                        pipeStart = c;
                    }
                    else
                    {
                        std::cout << "Tankevurpa1 " << x << "," << y << std::endl;
                    }
                }
                else if (c == 'J' || c == '7')
                {
                    if (onPipes)
                    {
                        if ((c == 'J' && pipeStart == 'F') || (c == '7' && pipeStart == 'L') )
                        {
                            onPipes = false;
                            inside = !inside;
                        }
                        else
                        {
                            onPipes = false;
                        }
                    }
                    else
                    {
                        std::cout << "Tankevurpa2 " << x << "," << y << std::endl;
                    }
                }
                
                
                
            }
            else if (inside)
            {
                //std::cout << x << "," << y << std::endl;
                ++ansB;
            }
            
            
        }
    }
    std::cout << "Answer part B " << ansB << std::endl;
}