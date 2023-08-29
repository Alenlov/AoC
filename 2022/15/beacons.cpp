#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <regex>
#include <set>

struct sensor
{
    int x;
    int y;
    int dist;
};

bool isInside(std::tuple<int,int> c,sensor s) {
    int x = std::get<0>(c);
    int y = std::get<1>(c);
    return abs(x - s.x) + abs(y - s.y) <= s.dist;
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
    int yRow = 2000000;
    int maxRow = 4000000;
    if (std::string(argv[1]) == "test") {
        yRow = 10;
        maxRow = 20;
    }
    int bOnRow = 0;
    std::regex legit_command("Sensor at x=(-?[0-9]+), y=(-?[0-9]+): closest beacon is at x=(-?[0-9]+), y=(-?[0-9]+)");
    int sum = 0;
    std::vector<std::tuple<int,int>> intervals;
    std::vector<sensor> sensors;
    std::set<std::tuple<int,int>> candidates;
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            std::cout << line << std::endl;
            std::smatch matches;
            if(std::regex_match(line, matches, legit_command)) {
                std::cout << "We extracted  " << matches[1] << " " << matches[2] << " " << matches[3] << " " << matches[4] << std::endl;
                int sx = std::stoi(matches[1]),sy = std::stoi(matches[2]),bx = std::stoi(matches[3]),by = std::stoi(matches[4]);
                int distance = abs(sx-bx) + abs(sy-by);
                int diff = distance - abs(sy-yRow);
                sensor s;
                s.x = sx;
                s.y = sy;
                s.dist = distance;
                sensors.push_back(s);
                if (diff > 0) {
                    int l = sx-diff, r = sx+diff;
                    if (by == yRow) {
                        if (bx == l) {
                            l += 1;
                        } else if (bx == r) {
                            r -= 1;
                        } else {
                            std::cout << "How!!!!!" << std::endl;
                        }
                    }
                    intervals.push_back(std::make_tuple(l,r));
                    //std::cout << l << "-" << r << " diff " << diff << std::endl;
                }
                for (int i = -distance-1; i <= distance + 1 ; i ++) {
                    int y = sy+i;
                    int diffN = distance+1 - abs(sy-y);
                    int lx = sx - diffN;
                    int rx = sx + diffN;
                    if (y <= maxRow && y >= 0) {
                        if (lx <= maxRow && lx >= 0) {
                            candidates.insert(std::make_tuple(lx,y));
                        }
                        if (rx <= maxRow && rx >= 0) {
                            candidates.insert(std::make_tuple(rx,y));
                        }
                    }
                }
            }
        }
    }
    std::set<int> searched;
    for (std::tuple<int,int> t : intervals) {
        for (int i = std::get<0>(t) ; i <= std::get<1>(t) ; i++) {
            searched.insert(i);
            //std::cout << i << " ";
        }
    }
    //std::cout << std::endl;
    std::cout << searched.size() << std::endl;
    
    for (auto c : candidates) {
        bool inside = false;
        for (auto s : sensors) {
            if (isInside(c,s)) {
                inside = true;
                break;
            }
        }
        if (!inside) {
            long long ans = std::get<0>(c)*4000000 + std::get<1>(c);
            std::cout << "Found it " << std::get<0>(c) << " " << std::get<1>(c) << " with sensor value " << ans << std::endl;
        }
    }
}