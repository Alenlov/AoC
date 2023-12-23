#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <set>

struct brick;

std::vector<char> coords{'x','y','z'};

std::map<std::pair<int,int>,std::pair<int,int>> coordToHeightId;
std::map<int,brick> movedBricks;

struct brick
{
    int id;
    std::set<int> supports, supportedBy;
    std::map<char,int> from, to;

    std::vector<std::pair<int,int>> pointsUnder()
    {
        std::vector<std::pair<int,int>> points;
        int numPointsX = (to['x']-from['x']+1);
        int numPointsY = (to['y']-from['y']+1);
        if (numPointsX > 1)
        {
            for (int i{0}; i < numPointsX; i++)
            {
                points.push_back({from['x']+i,from['y']});
            }
        }
        else
        {
            for (int i{0}; i < numPointsY; i++)
            {
                points.push_back({from['x'],from['y']+i});
            }
        }
        return points;
    }

    void moveDown(int dz)
    {
        from['z'] -= dz;
        to['z'] -= dz;
    }

    bool canRemove()
    {
        if (supports.empty()) return true;
        else
        {
            for (int oth : supports)
            {
                if (movedBricks[oth].supportedBy.size() == 1 )
                {
                    return false;
                }
            }
            return true;
        }
    }

    std::string toString()
    {
        std::string f{""}, s{""};
        for (char c : coords)
        {
            f += std::to_string(from[c]);
            s += std::to_string(to[c]);
            if (c != 'z')
            {
                f += ",";
                s += ",";
            }
        }
        return f + "~" + s + " id " + std::to_string(id);
    }

    std::strong_ordering operator<=>(const brick& that) const
    {
        if (from.at('z') != that.from.at('z'))
        {
            return from.at('z') <=> that.from.at('z');
        }
        else if (from.at('y') != that.from.at('y'))
        {
            return from.at('y') <=> that.from.at('y');
        }
        else
        {
            return from.at('x') <=> that.from.at('x');
        }
        
    }
};


std::pair<int,int> operator+(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
    return {lhs.first+rhs.first,lhs.second+rhs.second};
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
    std::priority_queue<brick, std::vector<brick>, std::greater<brick>> bricks;
    int id{0};
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, "~"), from, to;
            from = splitLine(split[0],",");
            to = splitLine(split[1],",");
            brick b;
            b.id = id;
            for (int i{0}; i < coords.size(); i++)
            {
                b.from[coords[i]] = std::stoi(from[i]);
                b.to[coords[i]] = std::stoi(to[i]);
            }
            bricks.push(b);
            ++id;
        }
    }
    myfile.close();
    //std::cout << bricks.size() << std::endl;
    
    while(!bricks.empty())
    {
        brick h = bricks.top();
        bricks.pop();
        //std::cout << h.toString() << std::endl;
        std::vector<std::pair<int,int>> pointsInXY = h.pointsUnder();
        int minHeight{0};
        std::set<int> minIds;
        for (auto p : pointsInXY)
        {
            if (coordToHeightId.contains(p))
            {
                int height = coordToHeightId[p].first;
                int id = coordToHeightId[p].second;
                if (height > minHeight)
                {
                    minHeight = height;
                    minIds = {id};
                }
                else if (height == minHeight)
                {
                    minIds.insert(id);
                }
                
            }
        }
        // How much to move down!
        //std::cout << minHeight;
        int dz = h.from['z'] - minHeight - 1;
        //std::cout << " Moving down " << h.from['z'] << " " << dz << " steps " << std::endl;
        h.moveDown(dz);
        
        h.supportedBy = minIds;

        for (auto p : pointsInXY)
        {
            coordToHeightId[p] = {h.to['z'],h.id};
        }

        movedBricks[h.id]=h;

    }
    
    for (auto [id, b] : movedBricks)
    {
        for (int i : b.supportedBy)
        {
            movedBricks[i].supports.insert(id);
        }
    }

    long ansA{0};

    for (auto [id, b] : movedBricks)
    {
        /* std::cout << b.toString() << " supported by = ";
        for (int i : b.supportedBy)
        {
            std::cout << i << " ";
        }
        std::cout << " supports = ";
        for (int i : b.supports)
        {
            std::cout << i << " ";
        }
        std::cout << " can be removed? ";
        std::cout << b.canRemove() << std::endl; */
        if (b.canRemove()) ++ansA;
    }

    std::cout << "Answer part A: " << ansA << std::endl;

    long ansB{0};

    for (auto [id, b] : movedBricks)
    {
        if (!b.canRemove())
        {
            std::set<int> fallingBricks;
            fallingBricks.insert(id);
            std::queue<int> toRemove;
            toRemove.push(id);
            while (!toRemove.empty())
            {
                int head = toRemove.front();
                toRemove.pop();
                brick h = movedBricks[head];
                for (int oth : h.supports)
                {
                    if (fallingBricks.contains(oth)) continue;
                    bool canRemove{true};
                    for (int othSup : movedBricks[oth].supportedBy)
                    {
                        if (!fallingBricks.contains(othSup))
                        {
                            canRemove = false;
                            break;
                        }
                    }
                    if (canRemove)
                    {
                        fallingBricks.insert(oth);
                        toRemove.push(oth);    
                    }
                }
            }
            ansB += fallingBricks.size() - 1;
        }
    }
    std::cout << "Answer part B: " << ansB << std::endl;
}