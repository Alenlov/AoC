#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <tuple>
#include <map>

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

int distance(std::tuple<int,int> head, std::tuple<int,int> tail) {
    int dx = abs(std::get<0>(head) - std::get<0>(tail));
    int dy = abs(std::get<1>(head) - std::get<1>(tail));
    /* std::cout << std::get<0>(head) << " " << std::get<1>(head) << std::endl;
    std::cout << std::get<0>(tail) << " " << std::get<1>(tail) << std::endl;
    std::cout << dx << " " << dy << " " << std::max(dx,dy) << std::endl; */
    return dx + dy;
}

bool adjacent(std::tuple<int,int> head, std::tuple<int,int> tail) {
    int dx = abs(std::get<0>(head) - std::get<0>(tail));
    int dy = abs(std::get<1>(head) - std::get<1>(tail));
    if (dx + dy <= 1) return true;
    if (dx == 1 & dy == 1) return true;
    return false;

}

std::string direction(std::tuple<int,int> head, std::tuple<int,int> tail) {
    std::string v = "";
    std::string h = "";
    if (std::get<0>(head) > std::get<0>(tail)) {
        h = "R";
    } else if (std::get<0>(head) < std::get<0>(tail)) {
        h = "L";
    }
    if (std::get<1>(head) > std::get<1>(tail)) {
        v = "U";
    } else if (std::get<1>(head) < std::get<1>(tail)) {
        v = "D";
    }
    return v + h;
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
    std::set<std::tuple<int,int>> tailSpotsA, tailSpotsB;
    //std::tuple<int,int> head, tail;
    std::vector<std::tuple<int,int>> rope(10, std::make_tuple(0,0));
    std::map<std::string, std::tuple<int,int>> dir;
    dir["U"] = std::make_tuple(0,1);
    dir["D"] = std::make_tuple(0,-1);
    dir["R"] = std::make_tuple(1,0);
    dir["L"] = std::make_tuple(-1,0);
    dir["UR"] = std::make_tuple(1,1);
    dir["UL"] = std::make_tuple(-1,1);
    dir["DR"] = std::make_tuple(1,-1);
    dir["DL"] = std::make_tuple(-1,-1);
    dir[""] = std::make_tuple(0,0);
    
    tailSpotsA.insert(rope[1]);
    tailSpotsB.insert(rope[9]);
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            std::vector<std::string> lineSplit = splitLine(line);
            for (int i = 0; i < std::stoi(lineSplit[1]); i ++) {
                std::tuple<int,int> move = dir[lineSplit[0]];
                rope[0] = std::make_tuple( std::get<0>(rope[0]) + std::get<0>(move), std::get<1>(rope[0]) + std::get<1>(move) );
                for (int j = 1; j < rope.size(); j ++ ){
                    if(! adjacent(rope[j-1],rope[j])) {
                        move = dir[direction(rope[j-1],rope[j])];
                        rope[j] = std::make_tuple(std::get<0>(rope[j]) + std::get<0>(move), std::get<1>(rope[j]) + std::get<1>(move));
                        //std::cout << std::get<0>(newTail) << " " << std::get<1>(newTail) << std::endl;
    
                        if (j == 1) tailSpotsA.insert(rope[j]);
                        if (j == 9) tailSpotsB.insert(rope[j]);
                    }
                    //ope[j] = newHead;
                    
                }
            }
            std::cout << "After " << line << std::endl;
            for(auto t : rope) {
                std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
            }
        }
    }

    myfile.close();

    std::cout << "Number of tail spots A " << tailSpotsA.size() << std::endl;
    std::cout << "Number of tail spots B " << tailSpotsB.size() << std::endl;

    /* for(auto t : tailSpots) {
        std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    } */

}
