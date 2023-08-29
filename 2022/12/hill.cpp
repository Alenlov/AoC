#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <tuple>
#include <map>
#include <deque>

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    int rowNum = 0;
    std::tuple<int,int> start, end;
    std::vector<std::vector<char>> hillMap;
    std::map<std::tuple<int,int>, int> visited;
    std::deque<std::tuple<int,int>> toExplore;
    std::set<std::tuple<int,int>> directions;
    directions.insert(std::make_tuple(1,0));
    directions.insert(std::make_tuple(-1,0));
    directions.insert(std::make_tuple(0,1));
    directions.insert(std::make_tuple(0,-1));
    if(myfile.is_open()) {
        while(getline(myfile,line)){
            std::vector<char> row;
            for (int i = 0; i < line.length(); i ++) {
                if (line[i] == 'S') {
                    row.push_back('a');
                    start = std::make_tuple(rowNum,i);
                } else if (line[i] == 'E') {
                    row.push_back('z');
                    end = std::make_tuple(rowNum,i);
                } else {
                    row.push_back(line[i]);
                }
            }
            //std::cout << row.size() << std::endl;
            hillMap.push_back(row);
            rowNum += 1;
        }

    }
    myfile.close();
    visited[start] = 0;
    toExplore.push_back(start);

    while(! toExplore.empty()) {
        std::tuple<int,int> curHead = toExplore.front();
        toExplore.pop_front();
        //std::cout << "Checking: " << std::get<0>(curHead) << "," << std::get<1>(curHead) << " with val " << hillMap[std::get<0>(curHead)][std::get<1>(curHead)] << std::endl;
        for (std::tuple<int,int> d : directions) {
            int newRow = std::get<0>(curHead) + std::get<0>(d);
            int newCol = std::get<1>(curHead) + std::get<1>(d);
            if(newRow <rowNum && newRow >= 0 && newCol < hillMap[0].size() && newCol >= 0 ){
                std::tuple<int,int> newHead = std::make_tuple( newRow , newCol );
                if (visited.find(newHead)== visited.end()) {
                    // Can visit?
                    if(int(hillMap[newRow][newCol] <= hillMap[std::get<0>(curHead)][std::get<1>(curHead)]+1)){
                        toExplore.push_back(newHead);
                        visited[newHead] = visited[curHead] + 1;
                    }
                }
            }
        }

    }
    std::cout << "Shortest path from S to E is " <<  visited[end] << " steps." << std::endl;


    std::map<std::tuple<int,int>, int> scenic;
    std::deque<std::tuple<int,int>> scenicEx;
    scenic[end] = 0;
    scenicEx.push_back(end);
    int stepsToA = 0;
    while(! scenicEx.empty()) {
        std::tuple<int,int> curHead = scenicEx.front();
        scenicEx.pop_front();
        if (hillMap[std::get<0>(curHead)][std::get<1>(curHead)] == 'a') {
            stepsToA = scenic[curHead];
            break;
        }
        //std::cout << "Checking: " << std::get<0>(curHead) << "," << std::get<1>(curHead) << " with val " << hillMap[std::get<0>(curHead)][std::get<1>(curHead)] << std::endl;
        for (std::tuple<int,int> d : directions) {
            int newRow = std::get<0>(curHead) + std::get<0>(d);
            int newCol = std::get<1>(curHead) + std::get<1>(d);
            if(newRow <rowNum && newRow >= 0 && newCol < hillMap[0].size() && newCol >= 0 ){
                std::tuple<int,int> newHead = std::make_tuple( newRow , newCol );
                if (scenic.find(newHead)== scenic.end()) {
                    // Can visit?
                    if(int(hillMap[newRow][newCol] >= hillMap[std::get<0>(curHead)][std::get<1>(curHead)]-1)){
                        scenicEx.push_back(newHead);
                        scenic[newHead] = scenic[curHead] + 1;
                    }
                }
            }
        }
    }
    std::cout << "Shortest scenic route is " << stepsToA << " steps." << std::endl;
}