#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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
    std::vector<std::vector<char>> mapOfGalaxies;
    std::vector<std::pair<int,int>> galaxies;
    
    if (myfile.is_open())
    {
        int y{0};
        while(getline(myfile,line))
        {
            int x{0};
            std::vector<char> row;
            for (char c : line)
            {
                row.push_back(c);
                if (c == '#')
                {
                    galaxies.push_back({x,y});
                }
                ++x;
            }
            mapOfGalaxies.push_back(row);
            ++y;
        }
    }
    myfile.close();
    
    int maxY = mapOfGalaxies.size();
    int maxX = mapOfGalaxies[0].size();
    std::vector<int> emptyRows, emptyCols;
    for (int y{0}; y < maxY; y++)
    {
        bool anyGalaxy{false};
        for (int x{0}; x < maxX; x++)
        {
            if (mapOfGalaxies[y][x] == '#') anyGalaxy = true;
        }
        if (!anyGalaxy)
        { 
            emptyRows.push_back(y);
            //std::cout << "Row " << y << " empty!" << std::endl;
        }
    }
    for (int x{0}; x < maxX; x++)
    {
        bool anyGalaxy{false};
        for (int y{0}; y < maxY; y++)
        {
            if (mapOfGalaxies[y][x] == '#') anyGalaxy = true;
        }
        if (!anyGalaxy) 
        {
            emptyCols.push_back(x);
            //std::cout << "Col " << x << " empty!" << std::endl;
        }
    }

    //std::cout << galaxies.size() << std::endl;
    //std::cout << emptyRows.size() << " " << emptyCols.size() << std::endl;
    long ansA{0}, ansB{0};
    int expansion{1000000};
    for (int i{0}; i < galaxies.size(); i++)
    {
        auto g = galaxies[i];
        for (int j{i+1}; j < galaxies.size(); j++)
        {
            auto g2 = galaxies[j];
        
            int extraRows{0}, extraCols{0};
            for (int r : emptyCols)
            {
                if ((g.first < r && r < g2.first) || (g2.first < r && r < g.first))
                {
                    ++extraCols;
                }
            }
            for (int c : emptyRows)
            {
                if ((g.second < c && c < g2.second) || (g2.second < c && c < g.second))
                {
                    ++extraRows;
                }
            }
            int colDiff{0}, rowDiff{0};
            rowDiff = abs(g.second - g2.second);// + extraRows;
            colDiff = abs(g.first - g2.first);// + extraCols;
            /*std::cout << "From " << g.first << "," << g.second << " to " << g2.first << "," << g2.second << std::endl;
            std::cout << "Extra rows " << extraRows << " extra cols " << extraCols  << std::endl;
            std::cout << "Coldiff " << colDiff << " rowDiff " << rowDiff << " distance " << colDiff+rowDiff << std::endl;
            std::cout << std::endl;*/
            ansA += colDiff + rowDiff + extraCols + extraRows;
            ansB += colDiff + rowDiff + (expansion-1)*(extraCols + extraRows); 
            
        }
    }
    std::cout << "Answer part A " << ansA << std::endl;
    std::cout << "Answer part B " << ansB << std::endl;
}