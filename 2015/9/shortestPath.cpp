#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

struct journey {
        std::string order;
        std::set<std::string> visited;
        int distance; 
        int maxDist = 0;  
};

std::vector<std::string> splitTask(std::string line){
    std::vector<std::string> split;
    int lastIndex = 0, newIndex = 0;
    std::string sep = " ";
    newIndex = line.find(sep, lastIndex);
    while ( newIndex != std::string::npos) {
        std::string part = line.substr(lastIndex,newIndex-lastIndex);
        split.push_back(part);
        lastIndex = newIndex+1;
        newIndex = line.find(sep, lastIndex);
    }
    std::string part = line.substr(lastIndex,std::string::npos);
    split.push_back(part);
    return split;
}





// Triangle inequality is not satisfied.

std::map<std::string, std::map<std::string, int>> distMap;
std::set<std::string> cities;
int main(int argc, char *argv[]) {
    
    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    std::set<std::string> visited;
    std::map<std::set<std::string>, int> myJourney;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            std::vector<std::string> mapLine = splitTask(line);
            
            std::string origin = mapLine.at(0);
            std::string dest = mapLine.at(2);
            cities.insert(origin);
            cities.insert(dest);
            int distance = stoi(mapLine.at(4));
            if (distMap.find(origin) == distMap.end()) {
                std::map<std::string, int> destDistance;
                destDistance[dest] = distance;
                distMap[origin] = destDistance;
            } else {
                distMap[origin].insert(std::make_pair(dest, distance));
            }
            if (distMap.find(dest) == distMap.end()) {
                std::map<std::string, int> destDistance;
                destDistance[origin] = distance;
                distMap[dest] = destDistance;
            } else {
                distMap[dest].insert(std::make_pair(origin, distance));
            }
        }
    }
    std::set<std::string> test1;
    test1.insert("a");
    test1.insert("b");
    std::set<std::string> test2;
    test2 = test1;
    test1.insert("c");
    for (std::string const& person : test1)
    {
        std::cout << person << ' ';
    }
    std::cout << std::endl;
    for (std::string const& person : test2)
    {
        std::cout << person << ' ';
    }
    std::cout << std::endl;
    return 0;
}