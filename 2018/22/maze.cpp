#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <set>

std::set<std::pair<int,int>> dirs{{1,0},{0,1},{-1,0},{0,-1}};
std::map<int,std::vector<int>> changeEquip{{0,{1,2}},{1,{0,2}},{2,{0,1}}};


std::map<std::pair<int,int>,long> geoLogical, eroision, risk;
long depth, eroConst{20183}, xConst{16807}, yConst{48271};
std::pair<int,int> start{0,0}, target;
std::pair<int,int> operator+(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
    return {lhs.first+rhs.first,lhs.second+rhs.second};
}

struct path
{
    int time{0}, expectedTime{0};
    std::pair<int,int> pos{0,0};
    int equip{1}; // 0 Inget, 1 Fackla, 2 Rep

    std::strong_ordering operator<=>(const path& other) const
    {
        if (expectedTime != other.expectedTime)
        {
            return expectedTime <=> other.expectedTime;
        }
        else if (time != other.time)
        {
            return time <=> other.time;
        }
        else if (pos != other.pos)
        {
            return pos <=> other.pos;
        }
        else
        {
            return equip <=> other.equip;
        }
    }
};


bool okPos(std::pair<int,int> pos)
{
    return pos.first >= 0 && pos.second >= 0;
}

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

long calcRisk(std::pair<int,int> point)
{
    if (risk.contains(point)) return risk[point];
    if (point == start || point == target)
    {
        geoLogical[point] = 0;
    }
    else if (point.first == 0)
    {
        geoLogical[point] = point.second*yConst;
    }
    else if (point.second == 0)
    {
        geoLogical[point] = point.first*xConst;
    }
    else
    {
        if (!eroision.contains(point + std::make_pair(-1,0))) calcRisk(point + std::make_pair(-1,0));
        if (!eroision.contains(point + std::make_pair(0,-1))) calcRisk(point + std::make_pair(0,-1));
        
        geoLogical[point] = eroision[point + std::make_pair(-1,0)] * eroision[point + std::make_pair(0,-1)];
    }

    eroision[point] = (geoLogical[point] + depth) % eroConst;

    risk[point] = ((eroision[point] % 3) + 3) % 3;

    return risk[point];
}

int distToTarget(std::pair<int,int> pos)
{
    return abs(target.first - pos.first) + abs(target.second - pos.second);
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
    int tarX, tarY;

    if (myfile.is_open())
    {
        getline(myfile,line);
        depth = std::stoi( splitLine(line,": ")[1] );
        getline(myfile,line);
        line = splitLine(line, ": ")[1];
        tarX = std::stoi( splitLine(line, ",")[0]);
        tarY = std::stoi( splitLine(line, ",")[1]);
        target = {tarX,tarY};
    }
    myfile.close();
    
    long ansA{0};
    for (int y{0}; y <= tarY; y++)
    {
        for (int x{0}; x <= tarX; x++)
        {
            ansA += calcRisk({x,y});
        }
    }
    std::cout << "Answer part A: " << ansA << std::endl;

    std::set<path> visited;
    std::priority_queue<path, std::vector<path>, std::greater<path>> heads;
    path h;
    heads.push(h);
    h.expectedTime = h.time + distToTarget(h.pos);
    bool foundEnd{false};
    long ansB{0}, firstWrong{0};
    while (!foundEnd)
    {
        if (heads.empty()) break;
        path h = heads.top();
        heads.pop();
        if (firstWrong != 0)
        {
            if (h.time > firstWrong + 7) continue;
            
        }
        //std::cout << heads.size() << std::endl;
        if (h.pos == target)
        {
            if (h.equip == 1)
            {
                foundEnd = true;
                ansB = h.time;
            }
            else
            {
                if (firstWrong == 0) firstWrong = h.time;
            }
        }
        for (auto d : dirs)
        {
            std::pair<int,int> newP = h.pos + d;
            if (!okPos(newP)) continue;
            int risk = calcRisk(newP);
            if (risk == h.equip)
            {
                // change To the not used one!
                for (int i : changeEquip[h.equip])
                {
                    if (i != calcRisk(h.pos))
                    {
                        path newH = h;
                        newH.pos = newP;
                        newH.time += 8; // kolla!
                        newH.equip = i;
                        newH.expectedTime = newH.time + distToTarget(newH.pos);
                        if (!visited.contains(newH)) 
                        {
                            heads.push(newH);
                            visited.insert(newH);
                        }
                    }
                }
            }
            else
            {
                // no change
                path newH = h;
                newH.pos = newP;
                newH.time += 1;
                newH.expectedTime = newH.time + distToTarget(newH.pos);
                if (!visited.contains(newH)) 
                {
                    heads.push(newH);
                    visited.insert(newH);
                }
            }
        }
    }
    if ((firstWrong > 0 && firstWrong + 7 < ansB) || ansB == 0) ansB = firstWrong + 7;
    std::cout << "Answer part B: " << ansB << std::endl;
    
}