#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <list>
#include <vector>
#include <map>
#include <set>

std::map<char, std::pair<int,int>> dirs = {{'^',{-1,0}}, {'v',{1,0}}, {'>',{0,1}}, {'<',{0,-1}}};
std::vector<std::pair<int,int>> moves = {{0,0},{1,0},{-1,0},{0,1},{0,-1}};

std::map<std::pair<int,int>,std::vector<char>> moveBlizzards (std::map<std::pair<int,int>,std::vector<char>> blizzards, int rows, int cols) {
    std::map<std::pair<int,int>,std::vector<char>> newBlizzards;
    for (auto const& [pos, types] : blizzards) {
        
        for (auto t : types) {
            int r = pos.first;
            int c = pos.second;
            r += dirs[t].first;
            c += dirs[t].second;
            if (r == 0) {
                r = rows - 2;
            } else if (r == rows - 1) {
                r = 1;
            }
            if (c == 0) {
                c = cols - 2;
            } else if (c == cols - 1) {
                c = 1;
            }
            newBlizzards[{r,c}].push_back(t);
        }
    } 
    return newBlizzards;
}

void printBlizzards(std::map<std::pair<int,int>,std::vector<char>> blizzards,std::set<std::pair<int,int>> walls, int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (blizzards.contains({r,c})) {
                if (blizzards[{r,c}].size()>1) std::cout << blizzards[{r,c}].size();
                else std::cout << blizzards[{r,c}][0];
            } else if (walls.contains({r,c})) {
                std::cout << '#';
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}

void printDetailed (std::map<std::pair<int,int>,std::vector<char>> blizzards) {
    for (auto const& [pos, types] : blizzards) {
        std::cout << "On pos " << pos.first << "," << pos.second << " we have ";
        for (auto t : types) {
            std::cout << t << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return -1;
    }
    int rows = 0;
    int cols = 0;
    std::map<std::pair<int,int>,std::vector<char>> blizzards;
    std::set<std::pair<int,int>> walls;
    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            if (cols == 0)
            {
                cols = line.length();
            }
            for (int c = 0 ; c < line.length(); c++) {
                if (int(line[c]) > 50) {
                    blizzards[{rows,c}].push_back(line[c]);
                } else if (line[c] == '#') {
                    walls.insert({rows,c});
                }
            }
            rows++;
        }
        
    }
    myfile.close();
    std::pair<int,int> entrance = {0,1};
    std::pair<int,int> exit = {rows-1, cols-2};
    std::cout << rows << "," << cols << std::endl;
    std::cout << entrance.first << "," << entrance.second << " " << exit.first << "," << exit.second << std::endl;
    std::cout << blizzards.size() << std::endl;
    int steps = 0;
    bool done = false;
    std::set<std::pair<int,int>> heads;
    heads.insert(entrance);
    while (!done)
    {
        steps++;
        //std::cout << "Minute " << steps << std::endl;
        blizzards = moveBlizzards(blizzards, rows, cols);
        //printBlizzards(blizzards, walls, rows, cols);
        //printDetailed(blizzards);
        std::set<std::pair<int,int>> newHeads;
        for (std::pair<int,int> h : heads) {
            for (std::pair<int,int> m : moves) {
                std::pair<int,int> newH = {h.first + m.first, h.second + m.second};
                if (!blizzards.contains(newH) && !walls.contains(newH) && newH.first > -1 && newH.first < rows && newH.second > -1 && newH.second < cols) {
                    //std::cout << newH.first << "," << newH.second << " ";
                    newHeads.insert(newH);
                }
                
                if (newH == exit) {
                    done = true;
                }
            }
            //std::cout << std::endl;
        }
        heads = newHeads;
    }
    std::cout << "Answer part A Steps = " << steps << std::endl;

    heads.clear();
    heads.insert(exit);
    done = false;

    while (!done)
    {
        steps++;
        //std::cout << "Minute " << steps << std::endl;
        blizzards = moveBlizzards(blizzards, rows, cols);
        //printBlizzards(blizzards, walls, rows, cols);
        //printDetailed(blizzards);
        std::set<std::pair<int,int>> newHeads;
        for (std::pair<int,int> h : heads) {
            for (std::pair<int,int> m : moves) {
                std::pair<int,int> newH = {h.first + m.first, h.second + m.second};
                if (!blizzards.contains(newH) && !walls.contains(newH) && newH.first > -1 && newH.first < rows && newH.second > -1 && newH.second < cols) {
                    //std::cout << newH.first << "," << newH.second << " ";
                    newHeads.insert(newH);
                }
                
                if (newH == entrance) {
                    done = true;
                }
            }
            //std::cout << std::endl;
        }
        heads = newHeads;
    }
    std::cout << "Back at entrance after Steps = " << steps << std::endl;

    heads.clear();
    heads.insert(entrance);
    done = false;

    while (!done)
    {
        steps++;
        //std::cout << "Minute " << steps << std::endl;
        blizzards = moveBlizzards(blizzards, rows, cols);
        //printBlizzards(blizzards, walls, rows, cols);
        //printDetailed(blizzards);
        std::set<std::pair<int,int>> newHeads;
        for (std::pair<int,int> h : heads) {
            for (std::pair<int,int> m : moves) {
                std::pair<int,int> newH = {h.first + m.first, h.second + m.second};
                if (!blizzards.contains(newH) && !walls.contains(newH) && newH.first > -1 && newH.first < rows && newH.second > -1 && newH.second < cols) {
                    //std::cout << newH.first << "," << newH.second << " ";
                    newHeads.insert(newH);
                }
                
                if (newH == exit) {
                    done = true;
                }
            }
            //std::cout << std::endl;
        }
        heads = newHeads;
    }
    std::cout << "Answer part B Steps = " << steps << std::endl;
    return 0;
}
