#include <iostream>
#include <bitset>
#include <map>
#include <tuple>
#include <deque>

int in = 1350;

bool isPath(int x, int y) {
    if (x < 0 || y < 0) {
        return false;
    }
    int val = x*x + 3*x + 2*x*y + y + y*y + in;
    std::string s = std::bitset<64>(val).to_string();
    std::string::difference_type n = std::count(s.begin(), s.end(), '1');
    if(n % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char* argv[])
{
    std::map<std::tuple<int, int>, int> explored;
    //std::map<std::tuple<int, int>, bool> spaces;
    std::deque<std::tuple<int,int>> toExplore;
    std::tuple<int,int> goal = std::make_tuple(31,39);
    toExplore.push_back(std::make_tuple(1,1));
    explored[std::make_tuple(1,1)] = 0;
    bool done = false;
    while(! done) {
        std::tuple<int,int> curPos = toExplore.front();
        int x = std::get<0>(curPos);
        int y = std::get<1>(curPos);
        if(curPos == goal) {
            done = true;
            
        }
        toExplore.pop_front();
        // up
        if(! explored.contains(std::make_tuple(x,y+1)) && isPath(x,y+1)) {
            explored[std::make_tuple(x,y+1)] = explored[curPos] + 1;
            toExplore.push_back(std::make_tuple(x,y+1));
        }
        // down
        if(! explored.contains(std::make_tuple(x,y-1)) && isPath(x,y-1)) {
            explored[std::make_tuple(x,y-1)] = explored[curPos] + 1;
            toExplore.push_back(std::make_tuple(x,y-1));
        }
        // right
        if(! explored.contains(std::make_tuple(x+1,y)) && isPath(x+1,y)) {
            explored[std::make_tuple(x+1,y)] = explored[curPos] + 1;
            toExplore.push_back(std::make_tuple(x+1,y));
        }
        // left
        if(! explored.contains(std::make_tuple(x-1,y)) && isPath(x-1,y)) {
            explored[std::make_tuple(x-1,y)] = explored[curPos] + 1;
            toExplore.push_back(std::make_tuple(x-1,y));
        }
    }
    std::cout << "Number of steps is " << explored[goal] << std::endl;
    int numToReach = 0;
    for (auto const& [key, val] : explored)
    {
        if(val <= 50) {
            numToReach += 1;
        }
    }
    std::cout << "Number of spaces in 50 steps is " << numToReach << std::endl;
}