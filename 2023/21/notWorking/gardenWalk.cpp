#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

std::map<std::pair<int,int>,std::map<std::string,int>> distToEdges;
std::map<std::pair<int,int>,std::map<std::string,std::vector<std::pair<int,int>>>> closestPointEdge;
std::map<std::pair<int,int>,std::map<int,int>> possEven, possOdd;

std::set<std::pair<int,int>> dirs{ {1,0},{-1,0},{0,1},{0,-1} };
std::vector<std::vector<char>> garden;
std::map<std::string, std::vector<std::string>> startToCheck{{"N",{"N", "NW", "NE"}} , {"S",{"S", "SW", "SE"}} , {"E",{"E", "SE", "NE"}} , {"W",{"W", "NW", "SW"}}, {"NW",{"NW"}}, {"NE",{"NE"}}, {"SW",{"SW"}}, {"SE",{"SE"}} };

std::vector<std::string> edges{"S","E","N","W","SE","SW","NE","NW" };

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

void updateFromPos(std::pair<int,int> pos)
{
    int maxRow = garden.size(), maxCol = garden[0].size();
    std::queue<std::pair<std::pair<int,int>,int>> heads;
    heads.push({pos,0});
    std::map<std::pair<int,int>,int> visited;
    visited[pos] = 0;
    while(!heads.empty())
    {
        std::pair<int,int> p = heads.front().first;
        int steps = heads.front().second;
        heads.pop();
        for (auto d : dirs)
        {
            std::pair<int,int> newP{p.first+d.first,p.second+d.second};
            if (newP.first >= 0 && newP.first < maxRow && newP.second >= 0 && newP.second < maxCol)
            {
                if (garden[newP.first][newP.second] == '.')
                {    
                    if (!visited.contains(newP))
                    {
                        visited[newP] = steps + 1;
                        heads.push({newP,steps+1});
                    }
                    else
                    {
                        if (visited[newP] > steps + 1)
                        {
                            visited[newP] = steps + 1;
                            heads.push({newP,steps+1});
                        }
                    }
                }
            }

        }
    }
    for (auto [p, l] : visited)
    {
        //std::cout << p.first << "," << p.second << " " << l << std::endl;
        if ((p.first + p.second)%2 == 0)
        {
            ++possEven[pos][l];
        }
        else
        {
            ++possOdd[pos][l];
        }
        if (p.first == 0)
        {
            if (distToEdges[pos].contains("N"))
            {
                if (distToEdges[pos]["N"] > l)
                {
                    distToEdges[pos]["N"] = l;
                    closestPointEdge[pos]["N"] = {p};
                }
                else if (distToEdges[pos]["N"] == l)
                {
                    closestPointEdge[pos]["N"].push_back(p);
                }
            }
            else
            {
                distToEdges[pos]["N"] = l;
                closestPointEdge[pos]["N"] = {p};
            }
        }
        else if (p.first == maxRow - 1)
        {
            if (distToEdges[pos].contains("S"))
            {
                if (distToEdges[pos]["S"] > l)
                {
                    distToEdges[pos]["S"] = l;
                    closestPointEdge[pos]["S"] = {p};
                }
                else if (distToEdges[pos]["S"] == l)
                {
                    closestPointEdge[pos]["S"].push_back(p);
                }
            }
            else
            {
                distToEdges[pos]["S"] = l;
                closestPointEdge[pos]["S"] = {p};
            }
        }
        if (p.second == 0)
        {
            if (distToEdges[pos].contains("W"))
            {
                if (distToEdges[pos]["W"] > l)
                {
                    distToEdges[pos]["W"] = l;
                    closestPointEdge[pos]["W"] = {p};
                }
                else if (distToEdges[pos]["W"] == l)
                {
                    closestPointEdge[pos]["W"].push_back(p);
                }
            }
            else
            {
                distToEdges[pos]["W"] = l;
                closestPointEdge[pos]["W"] = {p};
            }
        }
        else if (p.second == maxCol - 1)
        {
            if (distToEdges[pos].contains("E"))
            {
                if (distToEdges[pos]["E"] > l)
                {
                    distToEdges[pos]["E"] = l;
                    closestPointEdge[pos]["E"] = {p};
                }
                else if (distToEdges[pos]["E"] == l)
                {
                    closestPointEdge[pos]["E"].push_back(p);
                }
                
            }
            else
            {
                distToEdges[pos]["E"] = l;
                closestPointEdge[pos]["E"] = {p};
            }
        }
    }
    distToEdges[pos]["NW"] = visited[{0,0}];
    closestPointEdge[pos]["NW"] = {{0,0}};
    distToEdges[pos]["NE"] = visited[{0,maxCol-1}];
    closestPointEdge[pos]["NE"] = {{0,maxCol-1}};
    distToEdges[pos]["SW"] = visited[{maxRow-1,0}];
    closestPointEdge[pos]["SW"] = {{maxRow-1,0}};
    distToEdges[pos]["SE"] = visited[{maxRow-1,maxCol-1}];
    closestPointEdge[pos]["SE"] = {{maxRow-1,maxCol-1}};
}

std::pair<int,int> otherEdge(std::pair<int,int> pos, std::string edge)
{
    int row = garden.size();
    int col = garden[0].size();
    std::pair<int,int> newStart;
    if (edge == "S")
    {
        newStart = {0,pos.second};
    }
    else if (edge == "N")
    {
        newStart = {row-1,pos.second};
    }
    else if (edge == "E")
    {
        newStart = {pos.first,0};
    }
    else if (edge == "W")
    {
        newStart = {pos.first,col-1};
    }
    else if (edge == "NW")
    {
        newStart = {row-1,col-1};
    }
    else if (edge == "NE")
    {
        newStart = {row-1,0};
    }
    else if (edge == "SW")
    {
        newStart = {0,col-1};
    }
    else if (edge == "SE")
    {
        newStart = {0,0};
    }
    return newStart;
}

void calcDists()
{
    int maxRow = garden.size(), maxCol = garden[0].size();
    
    for (int col{0}; col < maxCol; col++)
    {
        updateFromPos({0,col});
        updateFromPos({maxRow-1,col});
    }
    for (int row{1}; row < maxRow-1; row++)
    {
        updateFromPos({row,0});
        updateFromPos({row,maxCol-1});
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
    int startCol{0}, startRow{0};
    int numEven{0}, numOdd{0};
    int row{0}, col{0};
    
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            col = 0;
            std::vector<char> rowVec;
            for (char c : line)
            {
                if (c != '#')
                {
                    if((row+col)%2 == 0) ++numEven;
                    else ++numOdd;
                }
                if (c == 'S')
                {
                    startCol = col;
                    startRow = row;
                    rowVec.push_back('.');
                }
                else
                {
                    rowVec.push_back(c);
                }
                ++col;
            }
            garden.push_back(rowVec);
            ++row;
        }
    }
    myfile.close();
    updateFromPos({startRow,startCol});
    long ansA{0}, ansAsteps{64};
    if (row < 50) ansAsteps = 6;
    for (auto [l, n] : possEven[{startRow,startCol}])
    {
        if (l <= ansAsteps) ansA += n;
    }
    std::cout << "Answer part A: " << ansA << std::endl;

    for (auto d : edges)
    {
        for (auto e : closestPointEdge[{startRow,startCol}][d])
        {
            std::pair<int,int> newStart = otherEdge(e, d);
            updateFromPos(newStart);
        }
    }

    for (auto [k,v] : distToEdges)
    {
        for (auto d : edges)
        {
            std::cout << "Distance from " <<k.first <<"," << k.second <<  " to " << d << " is " << distToEdges[k][d] << " going to ";
            for (auto e : closestPointEdge[k][d])
            {
                std::cout << e.first << "," << e.second << " ";
            }
            std::cout << std::endl;
        }
    }

    long ansB{0};
    long stepsB{10};
    std::pair<int,int> startPos{startRow,startCol};
    // Number of squares covered entierly.
    std::map<std::string,long> covered, reached;
    std::map<std::string,std::map<std::pair<int,int>,int>> entryPointsFirst, entryPointsOther;
    
    for (std::string d : edges)
    {
        int numReached{0};
        int stepsIn = d.length();
        for (std::string s : startToCheck[d])
        {
            int lenStart = distToEdges[startPos][s];
            for (auto p : closestPointEdge[startPos][s])
            {
                std::pair<int,int> firstEntry = otherEdge(p,d);
                if (!entryPointsFirst[d].contains(firstEntry))
                {
                    entryPointsFirst[d][firstEntry] = lenStart+stepsIn;
                }
                else
                {
                    if (entryPointsFirst[d][firstEntry] > lenStart+stepsIn)
                    {
                        entryPointsFirst[d][firstEntry] = lenStart+stepsIn;
                    }
                }
            }
        }
    }
    
    long numStepsB{26501365};
    long numReached = (numStepsB - 65)/131;
    long numCovered = (numStepsB - 130)/131;
    long stepsLeft = 131;
    long stepsLeftDiagFar = (stepsLeft-3)/2;
    long stepsLeftDiagClose = (3*stepsLeft-3)/2;

    ansB = (numReached-1)*(numReached-1)*numOdd + numReached * numReached * numEven;
    std::map<int,int> numToCount;
    // N
    std::pair<int,int> startPoint;
    startPoint = otherEdge(closestPointEdge[startPos]["N"][0],"N");
    if (stepsLeft%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeft) ansB += n;
    }
    
    // S
    startPoint = otherEdge(closestPointEdge[startPos]["S"][0],"S");
    if (stepsLeft%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeft) ansB += n;
    }


    // W
    startPoint = otherEdge(closestPointEdge[startPos]["W"][0],"W");
    if (stepsLeft%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeft) ansB += n;
    }
    // E
    startPoint = otherEdge(closestPointEdge[startPos]["E"][0],"E");
    if (stepsLeft%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeft) ansB += n;
    }
    // NW
    startPoint = otherEdge(closestPointEdge[startPos]["NW"][0],"NW");
    if (stepsLeftDiagClose%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagClose) ansB += n * (numReached - 1);
    }
    if (stepsLeftDiagFar%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagFar) ansB += n * (numReached);
    }
    // NE
    startPoint = otherEdge(closestPointEdge[startPos]["NE"][0],"NE");
    if (stepsLeftDiagClose%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagClose) ansB += n * (numReached - 1);
    }
    if (stepsLeftDiagFar%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagFar) ansB += n * (numReached);
    }
    // SW
    startPoint = otherEdge(closestPointEdge[startPos]["SW"][0],"SW");
    if (stepsLeftDiagClose%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagClose) ansB += n * (numReached - 1);
    }
    if (stepsLeftDiagFar%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagFar) ansB += n * (numReached);
    }
    // Se
    startPoint = otherEdge(closestPointEdge[startPos]["SE"][0],"SE");
    if (stepsLeftDiagClose%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagClose) ansB += n * (numReached - 1);
    }
    if (stepsLeftDiagFar%2 == 0)
    {
        numToCount = possEven[startPoint];
    }
    else
    {
        numToCount = possOdd[startPoint];
    }
    for (auto [l, n] : numToCount)
    {
        if (l < stepsLeftDiagFar) ansB += n * (numReached);
    }

    std::cout << "Answer part B: " << ansB << std::endl;
}