#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <map>


int findRing(int val) {
    int totNum{1};
    int ring{1};
    while(totNum < val) {
        ring += 1;
        totNum += (ring-1)*2*4;
    }
    return ring;
}

std::map<int,std::pair<int,int>> sideDir{{0,{0,1}}, {1,{-1,0}}, {2, {0,-1}}, {3, {1,0}}};

int distToCenter(int val, int ring) {
    int dist{0};
    int totNumPrevRing{1};
    for (int i = 2; i < ring; i ++) {
        totNumPrevRing += (i-1)*2*4;
    }
    int idInRing = val - totNumPrevRing;
    int sideSize = (ring-1)*2;
    int fromBottom = (idInRing % sideSize);
    //std::cout << val << " idInRing " << idInRing << " sideSize " << sideSize << " fromBottom " << fromBottom << std::endl;
    if (fromBottom > (sideSize/2)) {
        dist = fromBottom - (sideSize/2);
    } else {
        dist = (sideSize/2) - fromBottom;
    }
    return dist;
}

int firstValGreaterThan(int val) {
    int ring{1}, totNum{1}, totNumInRing{1}, lastNum{1};
    std::pair<int,int> curPos{0,0};
    std::map<std::pair<int,int>, int> gridVals{{curPos, 1}};
    int sideId{4}, fromBottom{0}, sideSize{1};
    while(lastNum <= val) {
                //std::cout << curPos.first << " : " << curPos.second << " val " << lastNum << " ring " << ring << " side " << sideId << " fromBottom " << fromBottom << std::endl;
        if (sideId == 4) {
            ring += 1;
            totNumInRing += (ring-1)*2*4;
            sideSize = (ring-1)*2;
            sideId = 0;
            fromBottom = 0;
            curPos = {curPos.first + 1, curPos.second};
        } else {
            curPos = {curPos.first + sideDir[sideId].first, curPos.second + sideDir[sideId].second};
            
        }
        int sum{0};
        for (int dx = -1; dx < 2; dx ++) {
            for (int dy = -1; dy < 2; dy++) {
                if (gridVals.contains({curPos.first+dx, curPos.second+dy})) sum += gridVals[{curPos.first+dx, curPos.second+dy}];
            }
        }
        gridVals[curPos] = sum;
        lastNum = sum;
        //std::cout << curPos.first << " : " << curPos.second << " val " << lastNum << " ring " << ring << " side " << sideId << " fromBottom " << fromBottom << std::endl;
        fromBottom += 1;
            if (fromBottom == sideSize) {
                sideId += 1;
                fromBottom = 0;
            }
    }
    return lastNum;
}

int main(int argc, char const *argv[])
{
    int val = std::stoi(argv[1]);

    // Find ring!
    std::cout << findRing(val) << std::endl;
    std::cout << distToCenter(val, findRing(val)) << std::endl;
    std::cout << "Answer part A: " << (findRing(val) - 1) + distToCenter(val, findRing(val)) << std::endl;
    std::cout << "Answer part B: " << firstValGreaterThan(val) << std::endl;
    return 0;
}
