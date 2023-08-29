#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <list>
#include <vector>
#include <map>
#include <regex>
#include <deque>

struct face
{
    int id;
    int size;
    std::pair<int,int> topLeft;
    std::map<std::string, std::pair<std::string,int>> ngbrs;
};

/*

        U
    L       R
        D
*/




std::vector<std::string> directions = {"U","D","L","R"};
std::map<std::string, std::vector<std::string>> connectedEdges = {{"U",{"L","R"}}, {"D",{"R","L"}}, {"L",{"D","U"}}, {"R",{"U","D"}}};
std::map<std::string, std::string> opposite = {{"U","D"}, {"D","U"}, {"L", "R"}, {"R","L"}};
std::map<std::string, std::pair<int,int>> move = {{"R",{0,1}}, {"L",{0,-1}}, {"U",{-1,0}}, {"D",{1,0}}};
std::map<std::string, std::string> turnL = {{"R","U"},{"U","L"},{"L","D"},{"D","R"}};
std::map<std::string, std::string> turnR = {{"R","D"},{"D","L"},{"L","U"},{"U","R"}};
std::map<std::string, int> valFromDir = {{"R",0},{"D",1},{"L",2},{"U",3}};
//acing is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^)

bool onFace(std::pair<int,int> pos, face *f) {
    //std::cout << "Checking " << pos.first << "," << pos.second << " on face " << f->id << " with topLeft " << f->topLeft.first << "," << f->topLeft.second << std::endl;
    if ( pos.first >= f->topLeft.first &&  pos.first <= f->topLeft.first + f->size && pos.second >= f->topLeft.second &&  pos.second <= f->topLeft.second + f->size ) {
        return true;
    } else {
        return false;
    }
}

std::pair<int,int> newPoint (int left, face *newF, std::string side) {
    int row = newF->topLeft.first;
    int col = newF->topLeft.second;
    if (side == "U") {
        return std::make_pair(row, col + newF->size -1 - left);
    } else if (side == "R") {
        return {row+newF->size-1 -left, col+newF->size - 1};
    } else if (side == "D") {
        return {row+newF->size-1, col + left };
    } else if (side == "L") {
        return {row+left, col};
    }
}

int distFromLeft(std::pair<int,int> pos, std::string dir, face* f) {
    std::string leftEdge = connectedEdges[dir][0];
    if (leftEdge == "L") {
        return pos.second - f->topLeft.second;
    } else if (leftEdge == "U") {
        return pos.first - f->topLeft.first;
    } else if (leftEdge == "R") {
        return f->topLeft.second + f->size-1 - pos.second;
    } else if (leftEdge == "D") {
        return f->topLeft.first + f->size-1 - pos.first;
    } else {
        std::cout << "ERROR! " << leftEdge << std::endl;
        return -1;
    }
}


int main(int argc, char const *argv[])
{
    std::map<std::pair<int,int>, char> theMap;
    std::ifstream myfile;
    std::string line;
    std::map<int,std::map<std::string,std::pair<int,std::string>>> cubeWrap;
    std::map<int, face*> theCube;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return 0;
    }
    
    std::vector<std::string> comands;
    std::pair<int,int> pos, startPos;
    bool foundStart = false;
    std::string dir = "R";
    int row = 1;
    int maxCol = 0;
    bool makingMap = true;
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            if (line == "") {
                makingMap = false;
                continue;
            }
            if (makingMap) {
                int col = 1;
                if (line.length() > maxCol) maxCol = line.length();
                for (int i = 0; i < line.length(); i ++) {
                    if (line[i] == '.' || line[i] == '#') {
                        if (!foundStart && line[i]=='.') {
                            foundStart = true;
                            startPos = std::make_pair(row,col+i);
                        }
                        theMap[std::make_pair(row,col+i)] = line[i];
                    }
                }
                row += 1;
            } else {
                std::size_t pos = 0, lenOfCmd = 0;
                while(pos < line.length()) {
                    if(int(line[pos])<65) {
                        for (lenOfCmd = 0; pos + lenOfCmd <= line.length(); lenOfCmd++){
                            if (pos + lenOfCmd == line.length()) {
                                comands.push_back(line.substr(pos,lenOfCmd));
                                pos+=lenOfCmd;
                            } else if( int(line[pos+lenOfCmd]) > 64 ) {
                                comands.push_back(line.substr(pos,lenOfCmd));
                                pos += lenOfCmd;
                                break;
                            }
                        }
                    } else if (int(line[pos]) > 64) {
                        lenOfCmd = 1;
                        comands.push_back(line.substr(pos,lenOfCmd));
                        pos += lenOfCmd;
                    }
                }
                
            }
        }
    }
    myfile.close();
    int sizeOfSide = std::max({row/4,maxCol/4});
    std::map<int,std::pair<int,int>> sidesTopLeft;
    std::map<std::pair<int,int>,int> topLeftToSide;
    std::pair<int,int> sidesPos = {startPos.first,startPos.second};
    int sideIndx = 0;
    while( sidesPos.first < row) {
        if (theMap.find(sidesPos) != theMap.end()) {
            sidesTopLeft[sideIndx] = sidesPos;
            topLeftToSide[sidesPos] = sideIndx;
            face *f = new face;
            f->id = sideIndx;
            f->size = sizeOfSide;
            f->topLeft = sidesPos;
            theCube[sideIndx] = f;
            sideIndx += 1;
        }
        if (sidesPos.second + sizeOfSide < maxCol) {
            sidesPos = {sidesPos.first, sidesPos.second + sizeOfSide};
        } else {
            sidesPos = {sidesPos.first + sizeOfSide, 1};
        }
    }

    for (auto &[k,v] : sidesTopLeft) {
        std::cout << "Side " << k << " top left is " << v.first << "," << v.second << std::endl;
    }

    /*
    Ide, välj en sida (1) placera den på plats 1 på kuben.
    Kolla upp ner vänster höger om det är en sida där. Placera de på rätt plats.
    */
    
    for (auto &[i, f] : theCube){
        std::cout << i << std::endl;
        sidesPos = f->topLeft;
        std::cout << "testing " << sidesPos.first - sizeOfSide << " " << sidesPos.second << std::endl;
        if (topLeftToSide.contains({sidesPos.first - sizeOfSide, sidesPos.second})) {
            int indxToPlace = topLeftToSide[{sidesPos.first - sizeOfSide, sidesPos.second}];
            std::cout << "found up with indx " << indxToPlace << std::endl;
            f->ngbrs["U"] = {"D",indxToPlace};
        }
        if (topLeftToSide.contains({sidesPos.first + sizeOfSide, sidesPos.second})) {
            int indxToPlace = topLeftToSide[{sidesPos.first + sizeOfSide, sidesPos.second}];
            
            std::cout << "found down with indx " << indxToPlace << std::endl;
            f->ngbrs["D"] = {"U",indxToPlace};
        }
        if (topLeftToSide.contains({sidesPos.first, sidesPos.second - sizeOfSide})) {
            int indxToPlace = topLeftToSide[{sidesPos.first, sidesPos.second - sizeOfSide}];
            std::cout << "found left with indx " << indxToPlace << std::endl;
            f->ngbrs["L"] = {"R",indxToPlace};
        }
        if (topLeftToSide.contains({sidesPos.first, sidesPos.second + sizeOfSide})) {
            int indxToPlace = topLeftToSide[{sidesPos.first, sidesPos.second + sizeOfSide}];
            std::cout << "found right with indx " << indxToPlace << std::endl;
            f->ngbrs["R"] = {"L",indxToPlace};
        }
    }

    bool allDone = false;

    while (!allDone) {
        allDone = true;
        for (auto &[i, f] : theCube) {
            std::cout << "Checking side " << i << std::endl;
            if (f->ngbrs.size() < 4) {
                for (auto d : directions) {
                    if (f->ngbrs.contains(d)) {
                        
                        std::string otherMatch = f->ngbrs[d].first;
                        int otherIndx = f->ngbrs[d].second;
                        std::cout << "Found direction " << d << " with match " << otherMatch << " " << otherIndx << std::endl;
                        for(int i = 0; i < 2; i ++ ){
                            std::string eL = connectedEdges[d][i];
                            if (! f->ngbrs.contains(eL)) {
                                std::cout << "Trying to set " << eL << " with direction " << connectedEdges[otherMatch][1-i] << std::endl;
                                if (theCube[otherIndx]->ngbrs.contains(connectedEdges[otherMatch][1-i])) {
                                    std::string othersConnected = theCube[otherIndx]->ngbrs[connectedEdges[otherMatch][1-i]].first;
                                    std::cout << otherMatch << " | " << othersConnected << " i=" << connectedEdges[othersConnected][i] << " 1-i=" << connectedEdges[othersConnected][1-i] << std::endl;
                                    f->ngbrs[eL] = { connectedEdges[othersConnected][1-i] , theCube[otherIndx]->ngbrs[connectedEdges[otherMatch][1-i]].second};
                                    allDone = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /*
    0
    1   2   3   4
    5
    */
    for (auto &[i, f] : theCube) {
        std::cout << "Side " << i << " has ngbrs " << f->ngbrs.size() << " ";
        for (auto & [j, g] : f->ngbrs) {
            std::cout << j << " : " << g.first << " " << g.second << " | ";
        }     
        std::cout << std::endl;
    }
    pos = startPos;
    std::cout << "We have " << comands.size() << " comands!" << std::endl;
    std::cout << "Map consists of " << theMap.size() << " squares!" << std::endl;
    std::cout << pos.first << " " << pos.second << std::endl;
    for (auto s : comands) {
        //std::cout << pos.first << " " << pos.second << " " << dir << " " << s << std::endl;
        if (s == "R") {
            dir = turnR[dir];
        } else if (s == "L") {
            dir = turnL[dir];
        } else {
            int dist = std::stoi(s);
            for (int i = 0; i < dist; i++){
                std::pair<int,int> newPos = {pos.first + move[dir].first, pos.second + move[dir].second};
                if (theMap.find(newPos) == theMap.end()) {
                    if (dir == "D") {
                        newPos = {0,pos.second};
                    } else if (dir == "U") {
                        newPos = {row,pos.second};
                    } else if (dir == "L") {
                        newPos = {pos.first, maxCol};
                    } else if (dir == "R") {
                        newPos = {pos.first, 0};
                    }
                    while(theMap.find(newPos) == theMap.end()) {
                        newPos = {newPos.first + move[dir].first, newPos.second + move[dir].second};
                    }
                }
                if(theMap[newPos] == '#') {
                    break;
                } else {
                    pos = newPos;
                }
            }
        }
    }
    std::cout << pos.first << " " << pos.second << " " << dir << std::endl;
    std::cout << "Answer part A = " << 1000*pos.first + 4*pos.second + valFromDir[dir] << std::endl;

    pos = startPos;
    dir = "R";

    /* for (auto const& [p, m] : theMap) {
        for (auto const& [i, f] : theCube) {
            if (onFace(p,f)) {
                std::cout << p.first << "," << p.second << " is on face " << i << " value here is " << m << std::endl;
            }
        }
    } */

    for (auto s : comands) {
        if (s == "R") {
            dir = turnR[dir];
        } else if (s == "L") {
            dir = turnL[dir];
        } else {
            int dist = std::stoi(s);
            for (int i = 0; i < dist; i++){
                std::cout << pos.first << " " << pos.second << " " << dir << " " << s << std::endl;
        
                std::string newDir = dir;
                std::pair<int,int> newPos = {pos.first + move[dir].first, pos.second + move[dir].second};
                if (theMap.find(newPos) == theMap.end()) {
                    // what face am I on?
                    int currentFace = -1;
                    for (auto &[j,f] : theCube) {
                        if ( onFace(pos, f)) {
                            currentFace = j;
                            int left = distFromLeft(pos, dir, theCube[currentFace]);
                            int newFaceId = theCube[currentFace]->ngbrs[dir].second;
                            newDir = theCube[currentFace]->ngbrs[dir].first;
                            newPos = newPoint(left, theCube[newFaceId], newDir);
                            newDir = opposite[newDir];
                        }
                    }
                    if (currentFace == -1) break;
                    std::cout << "Old pos " << pos.first << "," << pos.second << " on face " << currentFace << std::endl;
                    std::cout << "Distance from left edge is " << distFromLeft(pos, dir, theCube[currentFace]) << std::endl;
                    std::cout << "New pos " << newPos.first << "," << newPos.second << " " << newDir << std::endl;
                    // where do I end up?
                }
                if(theMap[newPos] == '#') {
                    break;
                } else {
                    pos = newPos;
                    dir = newDir;
                }
            }
        }
    }
    std::cout << pos.first << " " << pos.second << " " << dir << std::endl;
    std::cout << "Answer part B = " << 1000*pos.first + 4*pos.second + valFromDir[dir] << std::endl;

}   