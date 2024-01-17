#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <set>

std::map<char,std::pair<int,int>> dirs{{'E',{1,0}},{'S',{0,-1}},{'W',{-1,0}},{'N',{0,1}}};
std::map<char,char> opo{{'E','W'},{'W','E'},{'N','S'},{'S','N'}};
struct room
{
    std::map<char,bool> doors{{'E',false},{'S',false},{'W',false},{'N',false}};
};

std::pair<int,int> operator+(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
    return {lhs.first+rhs.first,lhs.second+rhs.second};
}

std::map<std::pair<int,int>,room> rooms;
std::set<std::pair<std::pair<int,int>,std::string>> seen;

void buildMap(std::string regString, std::pair<int,int> curPos)
{
    if (seen.contains({curPos,regString}))
    {
        std::cout << "PRUNE!" << std::endl;
        return;
    }
    seen.insert({curPos,regString});
    //std::cout << regString.size() << " " << rooms.size() << std::endl;
    int i = 0;
    while(i < regString.size())
    {
        
        char c = regString[i];
        //std::cout << c;
        if (c == '(')
        {
            // split into multiple and relaunch!
            int lvl{0};
            ++i;
            std::vector<std::string> newStrings;
            std::string s;
            while (regString[i] != ')' || lvl != 0)
            {
                //std::cout << regString[i] << " " << lvl << " " << s << std::endl;
                if (regString[i] == '|' && lvl == 0)
                {
                    newStrings.push_back(s);
                    s = "";
                }
                else
                {
                    s += regString[i];
                    if (regString[i] == '(') ++lvl;
                    else if (regString[i] == ')') --lvl; 
                    
                }
                ++i;
            }
            newStrings.push_back(s);
            for (std::string s : newStrings)
            {
                //std::cout << s << " + " << regString.substr(i+1,-1) << std::endl;
                buildMap(s + regString.substr(i+1,regString.size()), curPos);
            }
            return;
        }
        else
        {
            rooms[curPos].doors[c] = true;
            curPos = curPos + dirs[c];
            rooms[curPos].doors[opo[c]] = true;
        }
        ++i;
        
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
    if (myfile.is_open())
    {
        getline(myfile,line);
        line = line.substr(1,line.size()-2);
    }
    
    myfile.close();
    //std::cout << line << std::endl;
    buildMap(line, {0,0});
    
    std::map<std::pair<int,int>,int> dists;
    std::queue<std::pair<int,int>> heads;
    heads.push({0,0});
    dists[{0,0}] = 0;
    while(! heads.empty())
    {
        std::pair<int,int> h = heads.front();
        heads.pop();
        room r = rooms[h];
        for (auto const[f,d] : dirs)
        {
            if (r.doors[f])
            {
                std::pair<int,int> newH = h + d;
                if (dists.contains(newH))
                {
                    if (dists[newH] > dists[h] + 1)
                    {
                        dists[newH] = dists[h]+1;
                        heads.push(newH);
                    }
                }
                else
                {
                    dists[newH] = dists[h] + 1;
                    heads.push(newH);
                }
            }
        }
    }
    long ansA{0}, ansB{0};
    for (auto const [c,l] : dists)
    {
        if (ansA < l) ansA = l;
        if (l >= 1000) ++ansB;
    }
    std::cout << "Answer part A: " << ansA << std::endl; 
    std::cout << "Answer part B: " << ansB << std::endl;

}