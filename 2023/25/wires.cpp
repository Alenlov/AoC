#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <set>

struct wire
{
    int id;
    std::string lhs, rhs;
    bool active{true};

    std::string otherCon(std::string in)
    {
        if (in == lhs) return rhs;
        else if (in == rhs) return lhs;
        
        return "";
        
    }
};

std::map<int, wire> allWires;
std::map<std::string,std::vector<int>> nodes;

std::map<std::pair<std::string,std::string>,int> minLength;

void calcMinLengths(std::string from)
{
    std::queue<std::pair<std::string,int>> head;
    head.push({from,0});
    std::set<std::string> visited;
    visited.insert(from);
    while(!head.empty())
    {
        auto [h, l] = head.front();
        head.pop();
        minLength[{from,h}] = l;
        for (auto id : nodes[h])
        {
            std::string newH = allWires[id].otherCon(h);
            if (newH == "")
            {
                // std::cout << "Found nothin!" << std::endl;
                // std::cout << h << " " << id << std::endl;
                // std::cout << allWires[id].lhs << " " << allWires[id].rhs << std::endl;
            }
            if (!visited.contains(newH))
            {
                visited.insert(newH);
                head.push({newH,l+1});
            }
        }
    }

}



void allPossiblePaths(std::string from, std::string to, std::map<std::string, bool>& visitedNodes, std::map<int, bool>& visitedEdges, std::set<std::set<int>>& paths)
{
    if (visitedNodes[from]) return;
    visitedNodes[from] = true;

    if (from == to)
    {
        std::set<int> path;
        for (auto const [id, b] : visitedEdges)
        {
            if (b) path.insert(id);
        }
        paths.insert(path);
        visitedNodes[from] = false;
    }

    for (int id : nodes[from])
    {
        if (!visitedEdges[id])
        {
            visitedEdges[id] = true;
            allPossiblePaths( allWires[id].otherCon(from) , to, visitedNodes, visitedEdges, paths );
            visitedEdges[id] = false;
        }
    }

    visitedNodes[from] = false;
}

int calcNumCon(std::set<std::string> setF, std::set<std::string> setL)
{
    int numCon{0};
    for (std::string s : setF)
    {
        for (int id : nodes[s])
        {
            std::string oth = allWires[id].otherCon(s);
            if (setL.contains(oth))
            {
                ++numCon;
            }
        }
    }
    return numCon;
}

std::string bestSwap(std::set<std::string> setF, std::set<std::string> setL)
{
    std::set<std::string> posF, posL;

    for (std::string s : setF)
    {
        for (int id : nodes[s])
        {
            std::string oth = allWires[id].otherCon(s);
            if (setL.contains(oth))
            {
                posF.insert(s);
                posL.insert(oth);
            }
        }
    }

    std::string best;
    int minNumCon = calcNumCon(setF, setL);
    if (setF.size() > 1)
    {
        for (std::string s : posF)
        {
            setF.erase(s);
            setL.insert(s);
            int newNumCon = calcNumCon(setF,setL);
            if (newNumCon < minNumCon)
            {
                minNumCon = newNumCon;
                best = s;
            }
            setL.erase(s);
            setF.insert(s);
        }
    }
    if (setL.size() > 1)
    {
        for (std::string s : posL)
        {
            setL.erase(s);
            setF.insert(s);
            int newNumCon = calcNumCon(setF,setL);
            if (newNumCon < minNumCon)
            {
                minNumCon = newNumCon;
                best = s;
            }
            setF.erase(s);
            setL.insert(s);
        }
    }

    return best;
}

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
    int id{0};
    
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, ": ");
            std::string lhs = split[0];
            for (std::string rhs : splitLine(split[1], " "))
            {
                wire w;
                w.id = id;
                w.lhs = lhs;
                w.rhs = rhs;
                allWires[id] = w;
                nodes[lhs].push_back(id);
                nodes[rhs].push_back(id);
                ++id;
            }
        }
    }
    myfile.close();
    std::pair<std::string,std::string> longPair;
    // std::cout << allWires.size() << std::endl;

    /* for (auto const [name, ids] : nodes)
    {
        //std::cout << name << " " << ids.size() << std::endl;
        calcMinLengths(name);
    }*/
    calcMinLengths(allWires[0].rhs);

    int maxMin{0};
    //std::pair<std::string,std::string> longPair;
    for (auto [k,v] : minLength)
    {
        if (v > maxMin)
        {
            maxMin = v;
            longPair = k;
        }
    }

    //calcMinLengths(allWires[0].lhs);
    

    std::set<std::string> setF, setL;// setF{"cmg", "frs", "lhk", "lsr", "nvd", "pzl", "qnr", "rsh", "rzs"}, setL{"bvb", "hfx", "jqt", "ntq", "rhn", "xhk"};
    setF.insert(longPair.first);
    setL.insert(longPair.second);
    // Give all nodes a home:
    while(setF.size() + setL.size() < nodes.size())
    {
        for (std::string n : setF)
        {
            for (int id : nodes[n])
            {
                std::string oth = allWires[id].otherCon(n);
                if (!setL.contains(oth))
                {
                    setF.insert(oth);
                }
            }
        }
        for (std::string n : setL)
        {
            for (int id : nodes[n])
            {
                std::string oth = allWires[id].otherCon(n);
                if (!setF.contains(oth))
                {
                    setL.insert(oth);
                }
            }
        }
    }
    /* for (std::string s : setF)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    for (std::string s : setL)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl; */
    int numCon = calcNumCon(setF,setL);
    //std::cout << numCon << std::endl;
    while (numCon > 3)
    {
        std::string bestToMove = bestSwap(setF,setL);
        if (setF.contains(bestToMove))
        {
            setF.erase(bestToMove);
            setL.insert(bestToMove);
        }
        else
        {
            setL.erase(bestToMove);
            setF.insert(bestToMove);
        }
        numCon = calcNumCon(setF,setL);
        /* std::cout << "======" << std::endl;
        for (std::string s : setF)
        {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        for (std::string s : setL)
        {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        std::cout << numCon << std::endl; */
    }

    long ansA = setF.size() * setL.size();
    std::cout << "Answer part A: " << ansA << std::endl;
    //std::cout << nodes.size() << " : " << setF.size() << " " << setL.size() << " " << (setF.size() + setL.size()) << std::endl;
}