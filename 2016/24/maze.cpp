#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <bitset>

std::vector<std::pair<int,int>> dirs({{1,0},{0,1},{-1,0},{0,-1}});

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

bool isNumber(char c) {
    int test = int(c) - int('0');
    return (0 <= test) && (test < 10);
}

std::vector<int> findDistances(std::pair<int,int> startPos, std::map<std::pair<int,int>,char> maze, int numNumbers) {
    std::vector<int> dists(numNumbers,-1);
    int startNum = int(maze[startPos]) - int('0');
    if (startNum < 0 || startNum > numNumbers) {
        std::cout << "ERROR startPos is not a number on maze!" << std::endl;
        return dists;
    }
    int numFound = 0;
    int steps = 0;
    std::queue<std::pair<int,int>> heads;
    std::set<std::pair<int,int>> history;
    heads.push(startPos);
    history.insert(startPos);
    while(numFound < numNumbers) {
        //std::cout << numFound << " " << steps << " " << heads.size() << std::endl;
        std::queue<std::pair<int,int>> newHeads;
        while (heads.size() > 0) {
            std::pair<int,int> h = heads.front();
            //std::cout << h.first << " - " << h.second << std::endl;
            heads.pop();
            if (isNumber(maze[h])) {
                int thisNum = int(maze[h]) - int('0');
                if (dists[thisNum] == -1){
                    dists[int(maze[h]) - int('0')] = steps;
                    numFound += 1;
                }
            }
            for (std::pair<int,int> dir : dirs) {
                std::pair<int,int> newH(h.first+dir.first,h.second+dir.second);
                if ((!history.contains(newH))&&(int(maze[newH]) != 35)) {
                    newHeads.push(newH);
                    history.insert(newH);
                }
            }
        }
        steps += 1;
        heads = newHeads;
    }

    return dists;

}

int main(int argc, char const *argv[])
{
    std::map<std::pair<int,int>, char> maze;
    std::map<int, std::pair<int,int>> numMaze;
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
        int y{0};
        while(getline(myfile,line)) {
            int x{0};
            for(char c : line) {
                maze.insert({std::make_pair(x,y), c});
                if(int(c) > 47 && int(c) < 58) {
                    numMaze.insert({int(c) - int('0'), std::make_pair(x,y)});
                    std::cout << c << std::endl;
                }
                x++;
            }
            y++;
        }
    }
    std::cout << "Maze has size " << maze.size() << " numbers have size " << numMaze.size() << std::endl;

    std::vector<std::vector<int>> dToNum(numMaze.size(), std::vector<int>(numMaze.size(),0));
    
    for(int i = 0; i < numMaze.size(); i++) {
        dToNum[i] = findDistances(numMaze[i], maze, numMaze.size());
        for(int j = 0; j < numMaze.size(); j++) {
            std::cout << dToNum[i][j] << " ";
        }
        std::cout << std::endl;
    }

    auto cmp=[](const std::pair<std::pair<int,int>,std::string>& a,const std::pair<std::pair<int,int>,std::string>& b){
        return (b.first.first < a.first.first);
    };
    std::priority_queue<std::pair<std::pair<int,int>, std::string >, std::vector<std::pair<std::pair<int,int>, std::string >>, decltype(cmp)> findStepsPQ;
    std::string visited(numMaze.size(),'0');
    std::cout << visited << " visited " << numMaze.size() << std::endl;
    visited[0] = '1';
    findStepsPQ.push(std::make_pair(std::make_pair(0,0), visited));
    
    std::map<int,int> endVals;
    
    while(findStepsPQ.size() > 0) {
        std::pair<std::pair<int,int>,std::string> h = findStepsPQ.top();
        //std::cout << h.first.first << ":\t" << h.second << "\t" << h.first.second << std::endl;
        findStepsPQ.pop();
        if (h.second == std::string(numMaze.size(), '1')) {
            if (!endVals.contains(h.first.second)) {
                endVals[h.first.second] = h.first.first;
            }
        }
        for (int i = 0; i < h.second.size(); i ++) {
            if(h.second[i] == '0') {
                std::string newVisited = h.second;
                newVisited[i] = '1';
                findStepsPQ.push(std::make_pair(std::make_pair(h.first.first+ dToNum[h.first.second][i], i ), newVisited));
                //std::cout << h.first + dToNum[0][i] << " " << newVisited << std::endl;
            }
        }
    }
    int minA = maze.size();
    int minB = maze.size();

    for(auto const [k,v] : endVals) {
        if (v < minA) minA = v;
        if (v + dToNum[k][0] < minB) minB = v + dToNum[k][0];
    }

    std::cout << "Answer part A:\t" << minA << std::endl;
    std::cout << "Answer part B:\t" << minB << std::endl;
    
}