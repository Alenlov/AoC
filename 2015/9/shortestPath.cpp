#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <limits>

struct journey {
        std::vector<std::string> visited;
        int distance = 0; 
        int maxDist = 0;
        int minDist = std::numeric_limits<int>::max();
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

std::map<std::string, std::map<std::string, int>> distMap;
std::set<std::string> cities;

int shortestPath(journey J) {
    //std::cout << J.distance << std::endl;
    if(J.visited.size() == 0) {
        std::string startCity = *(cities.begin());
        J.visited.push_back(startCity);
        std::cout << "Starting city = " << startCity << std::endl;
    } if(J.visited.size() == cities.size()) {
        std::string startCity = J.visited.front();
        std::string endCity = J.visited.back();
        std::cout << "At the end, started in " << startCity << " ended in " << endCity << std::endl;
        int newDist = distMap[startCity].at(endCity);
        if(newDist > J.maxDist){
            J.maxDist = newDist;
        }
        J.distance += newDist;
        return (J.distance - J.maxDist);
    }
    std::string currentCity = J.visited.back();
    std::map<std::string, int> distFromCurr = distMap[currentCity];
    std::vector<int> distances;
    for(std::string const& city : cities) {
        if(! std::count(J.visited.begin(), J.visited.end(), city) ){
            journey K = J;
            K.visited.push_back(city);
            int newDist = distFromCurr[city];
            if(newDist > K.maxDist){
                K.maxDist = newDist;
            }
            K.distance += newDist;
            distances.push_back(shortestPath(K));
        }
    }
    int minDist = std::numeric_limits<int>::max();
    for(int const& dist : distances){
        if(dist < minDist){
            minDist = dist;
        }
    }
    return minDist;
}

int longestPath(journey J) {
    if(J.visited.size() == 0) {
        std::string startCity = *(cities.begin());
        J.visited.push_back(startCity);
        std::cout << "Starting city = " << startCity << std::endl;
    } if(J.visited.size() == cities.size()) {
        std::string startCity = J.visited.front();
        std::string endCity = J.visited.back();
        std::cout << "At the end, started in " << startCity << " ended in " << endCity << std::endl;
        int newDist = distMap[startCity].at(endCity);
        if(newDist < J.minDist){
            J.minDist = newDist;
        }
        J.distance += newDist;
        return (J.distance - J.minDist);
    }
    std::string currentCity = J.visited.back();
    std::map<std::string, int> distFromCurr = distMap[currentCity];
    std::vector<int> distances;
    for(std::string const& city : cities) {
        if(! std::count(J.visited.begin(), J.visited.end(), city) ){
            journey K = J;
            K.visited.push_back(city);
            int newDist = distFromCurr[city];
            if(newDist < K.minDist){
                K.minDist = newDist;
            }
            K.distance += newDist;
            distances.push_back(longestPath(K));
        }
    }
    int maxDist = 0;
    for(int const& dist : distances){
        if(dist > maxDist){
            maxDist = dist;
        }
    }
    return maxDist;
}


// Triangle inequality is not satisfied.


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

    // Pick a starting point. For each city not in visited create a journey. Keep going until all cities visited. If two journeys have visited the same number of cities save the one with shortest path. Once all cities are visited add the journey back home. Remove the longest trip and return the total distance.
    journey J, K;
    int shortestRoute = shortestPath(J);

    int longestRoute = longestPath(K);
    std::cout << "Answer part A: The shortest path through all cities is " << shortestRoute << std::endl;
    std::cout << "Answer part B: The longest path through all cities is " << longestRoute << std::endl;
    return 0;
}