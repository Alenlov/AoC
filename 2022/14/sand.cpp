#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <tuple>
#include <deque>

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

bool canMove(std::tuple<int,int> s, std::set<std::tuple<int,int>> rocks, std::set<std::tuple<int,int>> sand, int maxDepth) {
    return rocks.find(s) == rocks.end() && sand.find(s) == sand.end() && std::get<1>(s) < maxDepth+2;
}

bool canMoveB(std::tuple<int,int> s, std::set<std::tuple<int,int>> rocks, int maxDepth) {
    return rocks.find(s) == rocks.end() && std::get<1>(s) < maxDepth+2;
}

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    std::set<std::tuple<int,int>> rocks, sand;
    std::deque<std::tuple<int,int>> history;
    int sum = 0;
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            std::vector<std::string> paths = splitLine(line, " -> ");
            std::tuple<int,int> start, end;
            std::vector<std::string> points = splitLine(paths[0],",");
            start = std::make_tuple(std::stoi(points[0]),std::stoi(points[1]));
            for( int i = 1; i < paths.size(); i ++) {
                points = splitLine(paths[i],",");
                end = std::make_tuple(std::stoi(points[0]),std::stoi(points[1]));
                if (std::get<0>(start) == std::get<0>(end)) {
                    for (int j = 0; j <= abs(std::get<1>(end) - std::get<1>(start)); j++) {
                        rocks.insert(std::make_tuple(std::get<0>(start), std::min(std::get<1>(start),std::get<1>(end)) + j));
                    }
                } else {
                    for (int j = 0; j <= abs(std::get<0>(end) - std::get<0>(start)); j++) {
                        rocks.insert(std::make_tuple( std::min(std::get<0>(start),std::get<0>(end))+j, std::get<1>(start)));
                    }

                }
                start = end;
            }
        }
    }
    int maxDepth = 0;
    for(std::tuple<int,int> t : rocks) {
        if(std::get<1>(t) > maxDepth) maxDepth = std::get<1>(t);
    }

    std::tuple<int,int> sandStart = std::make_tuple(500,0);
    bool fallDown = false;
    bool aDone = false;
    history.push_front(sandStart);
    while(!history.empty()) {
        // Simualte a new sand
        
        bool falling = true;
        int x = std::get<0>(history.front());
        int y = std::get<1>(history.front());
        while(falling) {
            // check below
            if (canMove(std::make_tuple(x,y+1), sand, rocks, maxDepth)) {
                y = y+1;
            } else if (canMove(std::make_tuple(x-1,y+1), sand, rocks, maxDepth)) {
                y = y+1;
                x = x-1;
            } else if (canMove(std::make_tuple(x+1,y+1), sand, rocks, maxDepth)) {
                y = y+1;
                x = x+1;
            } else {
                sand.insert(std::make_tuple(x,y));
                history.pop_front();
                //std::cout << "Inserted " << x << "," << y << " now have " << sand.size() << " queue " << history.size() << std::endl;

                falling = false;
            }
            if(falling) {
                history.push_front(std::make_tuple(x,y));
            }
            if (y > maxDepth && !aDone)
            {
                std::cout << "Anser to a is " << sand.size() << std::endl;
                aDone = true;
                history.clear();
                break;
            }
            
        }
    }
    std::set<std::tuple<int,int>> sandB;
    std::deque<std::tuple<int,int>> historyB;
    historyB.push_front(sandStart);
    while(!historyB.empty()) {
        std::tuple<int,int> cur = historyB.front();
        historyB.pop_front();
        if (sandB.find(cur) == sandB.end()) {
            sandB.insert(cur);
            int x = std::get<0>(cur);
            int y = std::get<1>(cur);
            std::tuple<int,int> d, dl, dr;
            d = std::make_tuple(x,y+1);
            dl = std::make_tuple(x-1,y+1);
            dr = std::make_tuple(x+1,y+1);
            if (canMoveB(d, rocks, maxDepth)) {
                historyB.push_back(d);
            }
            if (canMoveB(dl, rocks, maxDepth)) {
                historyB.push_back(dl);
            }
            if (canMoveB(dr, rocks, maxDepth)) {
                historyB.push_back(dr);
            } 
        }
        
        
            
            
        
    }
    std::cout << "Anser to b is " << sandB.size() << std::endl;

}