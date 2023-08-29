#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <tuple>
#include <set>
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

int minX=100,maxX=0,minY=100,maxY=0,minZ=100,maxZ=0;
std::set<std::tuple<int,int,int>> interior;
std::set<std::tuple<int,int,int>> exterior;

bool isExterior(std::set<std::tuple<int,int,int>> cubes, std::tuple<int,int,int> toCheck) {
    if (interior.contains(toCheck)) return false;
    if (exterior.contains(toCheck)) return true;
    std::deque<std::tuple<int,int,int>> nextCheck;
    std::set<std::tuple<int,int,int>> ngbr;
    nextCheck.push_back(toCheck);
    ngbr.insert(toCheck);
    std::vector<int> diffs = {-1,1};
    while(!nextCheck.empty()) {
        std::tuple<int,int,int> head = nextCheck.front();
        nextCheck.pop_front();
        if (interior.contains(head)) {
            for (auto c : ngbr) {
                interior.insert(c);
            }
            return false;
        } else if (exterior.contains(head)) {
            for (auto c : ngbr) {
                exterior.insert(c);
            }
            return true;
        }
        int x = std::get<0>(head), y = std::get<1>(head), z = std::get<2>(head);
        if (x < minX || x > maxX || y < minY || y > maxY || z < minZ || z > maxZ ) {
            for (auto c : ngbr) {
                exterior.insert(c);
            }
            return true;
        }
        for (int d : diffs) {
            std::tuple<int,int,int> s1 = {x+d,y,z},s2 = {x,y+d,z},s3 ={x,y,z+d};
            if (!cubes.contains(s1) && !ngbr.contains(s1)) {
                nextCheck.push_back(s1);
                ngbr.insert(s1);
            }
            if (!cubes.contains(s2) && !ngbr.contains(s2)) {
                nextCheck.push_back(s2);
                ngbr.insert(s2);
            }
            if (!cubes.contains(s3) && !ngbr.contains(s3)) {
                nextCheck.push_back(s3);
                ngbr.insert(s3);
            }
        }

    }
    for (auto c : ngbr) {
        interior.insert(c);
    }
    return false;
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

    std::set<std::tuple<int,int,int>> cubes, edges;
    if(myfile.is_open()) {
        while(getline(myfile,line)){
            std::vector<std::string> coords = splitLine(line,",");
            int x = std::stoi(coords[0]), y = std::stoi(coords[1]), z = std::stoi(coords[2]);
            if (x < minX) minX = x;
            if (x > maxX) maxX = x;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
            if (z < minZ) minZ = z;
            if (z > maxZ) maxZ = z;
            cubes.insert(std::make_tuple(x,y,z));
        }
    }
    int numEdges = 0, numExtEdges = 0;
    std::vector<int> diffs = {-1,1};
    for (auto c : cubes) {
        for (int d : diffs) {
            int x = std::get<0>(c), y = std::get<1>(c), z = std::get<2>(c);
            std::tuple<int,int,int> s1 = {x+d,y,z},s2 = {x,y+d,z},s3 ={x,y,z+d};
            if (!cubes.contains(s1)) {
                if (isExterior(cubes, s1)) numExtEdges += 1;
                numEdges += 1;
            }
            if (!cubes.contains(s2)) {
                if (isExterior(cubes, s2)) numExtEdges += 1;
                numEdges += 1;
            }
            if (!cubes.contains(s3)) {
                if (isExterior(cubes, s3)) numExtEdges += 1;
                numEdges += 1;
            }
        }
    }
    std::cout << "Number of edges is " << numEdges << std::endl;
    std::cout << "Number of exterior edges is " << numExtEdges << std::endl;
}