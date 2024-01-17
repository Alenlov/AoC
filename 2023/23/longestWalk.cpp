#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
#include <map>

std::vector<std::vector<char>> theMap;
std::unordered_map<char,std::pair<int,int>> dirs {{'D',{1,0}},{'U',{-1,0}},{'R',{0,1}},{'L',{0,-1}}};
std::unordered_map<char, std::pair<int,int>> forced{ {'>',{0,1}}, {'<',{0,-1}}, {'v',{1,0}}, {'^',{-1,0}}  };


std::pair<int,int> operator+(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
    return {lhs.first+rhs.first,lhs.second+rhs.second};
}

struct junction
{
    int id;
    std::pair<int,int> startPoint;
    std::vector<int> from;
    std::vector<std::pair<int,int>> to, toAll;
};

std::unordered_map<int,junction> junctions;

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

bool isJunction(int row, int col)
{
    int numPaths{0};
    for (auto const [dir, diff] : dirs)
    {
        if (row+diff.first < 0 || row+diff.first >= theMap.size()) return true;
        if (theMap[row+diff.first][col+diff.second] != '#') ++numPaths;
    }
    return numPaths > 2;
}

void distToNghbrs(int id)
{
    std::pair<int,int> junctionStart = junctions[id].startPoint;
    std::map<std::pair<int,int>, int> visited{{junctionStart, 0}};
    std::queue<std::pair<int,int>> heads;
    heads.push(junctionStart);
    while(!heads.empty())
    {
        std::pair<int,int> h = heads.front();
        heads.pop();
        //std::cout << h.first << "," << h.second << std::endl;
        char cur = theMap[h.first][h.second];
        if (forced.contains(cur))
        {
            std::pair<int,int> newH = h + forced[cur];
            if (visited.contains(newH)) continue;
            if (isJunction(newH.first, newH.second))
            {
                for (auto [i, j] : junctions)
                {
                    if (j.startPoint == newH)
                    {
                        j.from.push_back(id);
                        junctions[id].to.push_back({i,visited[h]+1});
                        junctions[id].toAll.push_back({i,visited[h]+1});
                        junctions[i].toAll.push_back({id,visited[h]+1});
                    }
                }
            }
            else
            {
                visited[newH] = visited[h] + 1;
                heads.push(newH);
            }
        }
        else
        {
            for (auto const [dir, diff] : dirs)
            {
                std::pair<int,int> newH = h + diff;
                if (newH.first < 0 || newH.first >= theMap.size()) continue;
                if (visited.contains(newH))
                {
                    continue;
                }
                else if (isJunction(newH.first, newH.second))
                {
                    for (auto [i, j] : junctions)
                    {
                        if (j.startPoint == newH)
                        {
                            j.from.push_back(id);
                            junctions[id].to.push_back({i,visited[h]+1});
                            junctions[id].toAll.push_back({i,visited[h]+1});
                            junctions[i].toAll.push_back({id,visited[h]+1});
                        }
                    }
                }
                else if ( theMap[newH.first][newH.second] != '#')
                {
                    visited[newH] = visited[h] + 1;
                    heads.push(newH);
                }
            }
        }
    }
}

int longestPath(int cur, int end, std::set<int> visited, int length)
{
    
    if (cur == end) return length;
    int maxLength = length;
    for (auto p : junctions[cur].to)
    {
        int newId = p.first;
        int newLen = p.second;
        if (!visited.contains(newId))
        {
            std::set<int> newVisited = visited;
            newVisited.insert(newId);
            int testLen = longestPath(newId, end, newVisited, length+newLen);
            if (testLen > maxLength) maxLength = testLen;
        }
    }
    return maxLength;
}

struct path
{
    int cur;
    std::set<int> visited;

    std::strong_ordering operator<=>(const path& that) const
    {
        if (cur != that.cur)
        {
            return cur <=> that.cur;
        }
        else if (visited.size() != that.visited.size())
        {
            return visited.size() <=> that.visited.size();
        }
        else
        {
            auto itThis = visited.begin();
            auto itThat = that.visited.begin();
            while (itThis != visited.end() || itThat != that.visited.end())
            {
                if (*itThis != *itThat) return *itThis <=> *itThat;
                ++itThis;
                ++itThat;
            }
        }
        return cur <=> that.cur;
    }
};



void longestPathB(int cur, int end, std::unordered_map<int, bool>& visited, std::unordered_map<int, int>& max_path, int length)
{
    if (visited[cur]) return;
    visited[cur] = true;

    max_path[cur] = std::max(max_path[cur], length );

    if (cur == end)
    {
        visited[cur] = false;
        return;
    }

    for (auto [i, l] : junctions[cur].toAll)
    {
        if (!visited[i])
        {
            longestPathB(i, end, visited, max_path, length + l);
        }
        //else std::cout << "Pruned" << std::endl;
        
    }
    visited[cur] = false;
}

/* 
int longestPathB(int cur, int end)
{
    std::unordered_map<path, int> pathLengths;
    std::queue<path> heads;
    heads.push({cur,{cur}});
    pathLengths[{cur,{cur}}] = 0;
    std::vector<int> lengthsToEnd;
    while(!heads.empty())
    {
        path h = heads.front();
        heads.pop();
        if (h.cur == end)
        {
            std::cout << "Found an end! " << pathLengths.size() << " " << heads.size() << std::endl;
            lengthsToEnd.push_back(pathLengths[h]);
            continue;
        }
        junction j = junctions[h.cur];
        for (auto d : j.toAll)
        {
            if (!h.visited.contains(d.first))
            {
                path newH = h;
                newH.cur = d.first;
                newH.visited.insert(d.first);
                if (pathLengths.contains(newH))
                {
                    if (pathLengths[newH] < pathLengths[h]+d.second)
                    {
                        pathLengths[newH] = pathLengths[h]+d.second;
                        heads.push(newH);
                    }
                    else
                    {
                        std::cout << "Pruned!" << std::endl;
                    }
                }
                else
                {
                    pathLengths[newH] = pathLengths[h]+d.second;
                    heads.push(newH);
                }
            }
        }
    }
    int maxLength{0};
    for (int l : lengthsToEnd)
    {
        if (l > maxLength) maxLength = l;
    }
    return maxLength;
}
 */
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
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<char> row;
            for (char c : line) row.push_back(c);
            theMap.push_back(row);
        }
    }
    myfile.close();
    int numRows = theMap.size();
    int numCols = theMap[0].size();

    int id{0};
    {
        junction j;
        j.id = id;
        j.startPoint = {0,1};
        junctions[id] = j;
        ++id;
    }
    for (int row = 1; row < numRows-1; row++)
    {
        for (int col = 1; col < numCols-1; col++)
        {
            if (theMap[row][col] == '.')
            {
                if (isJunction(row,col))
                {
                    junction j;
                    j.id = id;
                    j.startPoint = {row,col};
                    junctions[id] = j;
                    ++id;
                }
            }
        }
    }
    {
        junction j;
        j.id = id;
        j.startPoint = {numRows-1, numCols-2};
        junctions[id] = j;
    }
    //std::cout << junctions.size() << std::endl;

    for (int i{0}; i < junctions.size(); i++)
    {
        distToNghbrs(i);
    }

    for (auto const [id, j] : junctions)
    {
       /*  std::cout << "Id " << id << " starting at " << j.startPoint.first << "," << j.startPoint.second << " leads to id and steps: ";
        for (auto d : j.to)
        {
            std::cout << d.first << " " << d.second << " | ";
        }
        std::cout << std::endl; */
        /* std::cout << "Id " << id << " starting at " << j.startPoint.first << "," << j.startPoint.second << " leads to id and steps: ";
        for (auto d : j.toAll)
        {
            std::cout << d.first << " " << d.second << " | ";
        }
        std::cout << std::endl; */
    }

    int start = 0;
    int end = id;
    int ansA = longestPath(start, end, {start}, 0);
    std::cout << "Answer part A: " << ansA << std::endl;
    std::unordered_map<int,int> max_path;
    std::unordered_map<int,bool> visited;
    int secondLast = junctions[end].toAll[0].first;
    int secondStart = junctions[start].toAll[0].first;
    longestPathB(secondStart, secondLast, visited, max_path, 0);
    int ansB = max_path[secondLast]+junctions[end].toAll[0].second + junctions[start].toAll[0].second;
    std::cout << "Answer part B: " << ansB << std::endl; 
}