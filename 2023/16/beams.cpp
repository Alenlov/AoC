#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

std::map<char,std::pair<int,int>> dirs{{'U',{-1,0}}, {'D',{1,0}}, {'L',{0,-1}}, {'R',{0,1}}};

std::map<char,char> changeDirF{{'U','R'},{'R','U'},{'D','L'},{'L','D'}};
std::map<char,char> changeDirB{{'U','L'},{'L','U'},{'D','R'},{'R','D'}};
std::map<char,std::map<char,char>> changeDir{{'/',changeDirF},{'\\',changeDirB}};
struct beam
{
    std::pair<int,int> pos{0,-1};
    char d{'R'};
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

int numEnergized(std::vector<std::vector<char>> grid, beam startPos)
{
    int maxRow = grid.size(), maxCol = grid[0].size();
    std::map<char,std::set<std::pair<int,int>>> visited;
    std::queue<beam> heads;
    heads.push(startPos);
    while (!heads.empty())
    {
        // Make a move
        beam h = heads.front();
        heads.pop();
        h.pos.first += dirs[h.d].first;
        h.pos.second += dirs[h.d].second;
        // Valid pos?
        if (0 > h.pos.first || h.pos.first >= maxRow || 0 > h.pos.second || h.pos.second >= maxCol )
        {
            continue;
        }
        else
        {
            char c = grid[h.pos.first][h.pos.second];
            if (c == '|')
            {
                if (h.d == 'L' || h.d == 'R')
                {
                    beam h2{h};
                    h.d = 'U';
                    h2.d = 'D';
                    heads.push(h);
                    heads.push(h2);
                }
                else
                {
                    heads.push(h);
                }
            }
            else if (c == '-')
            {
                if (h.d == 'U' || h.d == 'D')
                {
                    beam h2{h};
                    h.d = 'L';
                    h2.d = 'R';
                    heads.push(h);
                    heads.push(h2);
                }
                else
                {
                    heads.push(h);
                }
            }
            else if (c == '/' || c == '\\')
            {
                h.d = changeDir[c][h.d];
                heads.push(h);
            }
            else
            {
                if (!visited[h.d].contains(h.pos))
                {
                    heads.push(h);
                }
            }
            //std::cout << h.pos.first << "," << h.pos.second << " " << h.d << std::endl;
            visited[h.d].insert(h.pos);
        }
    }
    std::set<std::pair<int,int>> combine;
    for (auto [d, s] : visited)
    {
        for (auto p : s)
        {
            combine.insert(p);
        }
    }
    /* for (int row{0}; row < maxRow ; row++)
    {
        for (int col{0}; col < maxCol ; col++)
        {
            if (combine.contains({row,col}))
            {
                std::cout << '#';
            }
            else
            {
                std::cout << grid[row][col];
            }
        }
        std::cout << std::endl;
    } */

    return combine.size();
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
    int maxRow{0}, maxCol{0};
    std::vector<std::vector<char>> grid;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<char> row;
            for (auto c : line) row.push_back(c);
            grid.push_back(row);
        }
    }
    myfile.close();
    maxRow = grid.size();
    maxCol = grid[0].size();
    beam start;

    int ansA = numEnergized(grid, start);

    std::cout << "Answer part A: " << ansA << std::endl;
    int numE{0};
    int ansB{0};
    for (int row{0}; row < maxRow; row++)
    {
        beam s1;
        s1.pos.first = row;
        s1.pos.second = -1;
        s1.d = 'R';
        numE = numEnergized(grid, s1);
        if (numE > ansB) ansB = numE;
        beam s2;
        s2.pos.first = row;
        s2.pos.second = maxCol;
        s2.d = 'L';
        numE = numEnergized(grid, s2);
        if (numE > ansB) ansB = numE;
    }
    for (int col{0}; col < maxCol ; col++)
    {
        beam s1;
        s1.pos.first = -1;
        s1.pos.second = col;
        s1.d = 'D';
        numE = numEnergized(grid, s1);
        if (numE > ansB) ansB = numE;
        beam s2;
        s2.pos.first = maxCol;
        s2.pos.second = col;
        s2.d = 'U';
        numE = numEnergized(grid, s2);
        if (numE > ansB) ansB = numE;
    }

    std::cout << "Answer part B: " << ansB << std::endl;
}