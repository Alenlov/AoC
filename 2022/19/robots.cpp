#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <regex>
#include <map>
#include <deque>
#include <tuple>
#include <algorithm>

struct blueprint
{
    std::map<std::string,std::vector<int>> robots;
    std::vector<int> maxRate;
};

struct state
{
    std::vector<int> rates;
    std::vector<int> resources;
    int time;
};

std::map<std::string,int> robToI = {{"ore",0}, {"clay",1}, {"obsidian",2}, {"geode",3}};
std::map<int, std::string> iToRob = {{0,"ore"}, {1,"clay"}, {2,"obsidian"}, {3,"geode"}};

std::vector<int> timeToBuild(blueprint bp, state s) {
    std::vector<int> times(4);
    for(auto const& [v,k] : iToRob) {
        bool possible = true;
        int timeNeeded = 0;
        for (int i = 0; i < 4; i++) {
            //std::cout << "To build " << k << " we need " << bp.robots[k][i] << " " << iToRob[i] << " we have " << s.resources[i] << " with rate " << s.rates[i] << std::endl;
            int needed = bp.robots[k][i];
            if (needed > 0) {
                if (s.rates[i] == 0) {
                    possible = false;
                    break;
                } else {
                    int x = needed - s.resources[i];
                    int timeForThis = 0;
                    if (x > 0) {
                        int y = s.rates[i];
                        timeForThis = x/y + (x % y != 0);
                    }
                    // q = x/y + (x % y != 0);
                    if (timeForThis > timeNeeded) {
                        timeNeeded = timeForThis;
                    }
                }
            }
        }
        
        if (possible) {
            times[v] = timeNeeded;
            //std::cout << "We need " << timeNeeded << " minutes!" << std::endl;
        } else {
            times[v] = -1;
            //std::cout << "Not possiblle!" << std::endl;
        }
    }
    return times;
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
    bool print = false;
    std::map<int, blueprint> blueprints;

    std::regex legit_command("Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian.");
    
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            std::smatch matches;
            if(std::regex_match(line, matches, legit_command)) {
                blueprint bp;
                bp.robots["ore"] = {std::stoi(matches[2]),0,0,0};
                bp.robots["clay"] = {std::stoi(matches[3]),0,0,0};
                bp.robots["obsidian"] = {std::stoi(matches[4]),std::stoi(matches[5]),0,0};
                bp.robots["geode"] = {std::stoi(matches[6]),0,std::stoi(matches[7]),0};
                
                bp.maxRate = {0,0,0,0};
                bp.maxRate[0] = std::max({std::stoi(matches[2]),std::stoi(matches[3]),std::stoi(matches[4]),std::stoi(matches[6])});
                bp.maxRate[1] = std::stoi(matches[5]);
                bp.maxRate[2] = std::stoi(matches[7]);
                bp.maxRate[3] = std::numeric_limits<int>::max();

                blueprints[std::stoi(matches[1])] = bp;
            }
        }
    }
    std::vector<int> startRates = {1, 0, 0, 0};
    std::vector<int> startResources = {0, 0, 0, 0};


    int tot = 0;
    for (auto const& [k, v] : blueprints){
        //int k = 2;
        //blueprint v = blueprints[k];
        state start;
        start.rates = startRates;
        start.resources = startResources;
        start.time = 24;
        
        std::deque<state> toCheck;
        toCheck.push_back(start);

        blueprint bpToUse = v;
        int curMax = 0;
        while(! toCheck.empty()) {
            state s = toCheck.front();
            toCheck.pop_front();
            /* int statusQuo = s.resources[3] + s.time*s.rates[3];
            if (statusQuo > curMax) {
                std::cout << s.resources[3] << " " << s.rates[3] << " " << s.time << std::endl;
                curMax = statusQuo;
                std::cout << curMax << std::endl;
            } */
            int theoreticalMax = s.resources[3] + s.time*s.rates[3] + s.time*(s.time-1)/2;
            if (theoreticalMax <= curMax) {
                //std::cout << "Hej!" << toCheck.size() << std::endl;
                continue;
            }
            std::vector<int> times = timeToBuild(bpToUse, s);
            for (auto const& [indx, type] : iToRob) {
                bool buildAny = false;
                if (times[indx] >= 0 && times[indx] + 1 < s.time && s.rates[indx] < bpToUse.maxRate[indx]) {
                    buildAny = true;
                    state newS;
                    newS.resources = {0,0,0,0};//s.resources;
                    for (int i = 0; i < 4; i++) {
                        newS.resources[i] = s.resources[i] + (times[indx]+1)*s.rates[i];
                    }
                    //std::cout << "After gathering we have " << newS.resources[0] << " " << newS.resources[1] << " " << newS.resources[2] << " " << newS.resources[3] << std::endl;
                    newS.rates = {s.rates[0],s.rates[1],s.rates[2],s.rates[3]};
                    //newS.rates = s.rates;
                    newS.time = s.time - (times[indx] + 1);
                    newS.rates[indx] += 1;
                    for(int i = 0; i < 4 ; i ++) {
                        newS.resources[i] -= bpToUse.robots[type][i];
                    }
                    if (print) {
                        std::cout << "Building a " << type << " robot. It takes " << times[indx] << " minutes. We have " << s.time << " minutes left." << std::endl;
                        std::cout << "Pre robots " << s.rates[0] << " " << s.rates[1] << " " << s.rates[2] << " " << s.rates[3] << " robots" << std::endl;
                        std::cout << "Pre resources " << s.resources[0] << " " << s.resources[1] << " " << s.resources[2] << " " << s.resources[3] << " resources" << std::endl;
                        std::cout << "After resources " << newS.resources[0] << " " << newS.resources[1] << " " << newS.resources[2] << " " << newS.resources[3] << " resources" << std::endl;
                        std::cout << "After robots " << newS.rates[0] << " " << newS.rates[1] << " " << newS.rates[2] << " " << newS.rates[3] << " robots" << std::endl;
                        std::cout << "We have " << newS.time << " minutes left." << std::endl;
                    
                    }
                    //std::cout << "Built " << type << "We now have " << newS.resources[0] << ","<< newS.resources[1] << ","<< newS.resources[2] << ","<< newS.resources[3] << " ore. After time " << times[indx]+1 << " time left is " << newS.time << std::endl;
                    //std::cout << "We have " << newS.rates[0] << ","<< newS.rates[1] << ","<< newS.rates[2] << ","<< newS.rates[3] << " ore. After time " << times[indx]+1 << " time left is " << newS.time << std::endl;
                    toCheck.push_back(newS);
                }
                if (!buildAny) {
                    // Klara
                    int geodeCount = s.resources[3] + s.rates[3]*s.time;
                    if (geodeCount > curMax) {
                        curMax = geodeCount;
                    }
                    //std::cout << "Times out, we got " << geodeCount << " geodes!" << std::endl;
                }
            }
        }
        std::cout << "Using BP " << k << " we got " << curMax << std::endl;
        tot += k*curMax;
    }
    std::cout << "Answer part A:" << tot << std::endl;
    /* state s1;
    s1.rates = {3,6,1,0};
    s1.resources = {3,13,0,0};
    std::vector<int> test1 = timeToBuild(blueprints[2], s1);
    for (auto const& [v,k] : iToRob) {
        std::cout << "To build " << k << " we need " << test1[v] << " minutes." << std::endl;
    }
    for (auto const& [v,k] : iToRob){
        std::cout << k << " " << blueprints[2].robots[k][0] << blueprints[2].robots[k][1] <<blueprints[2].robots[k][2] <<blueprints[2].robots[k][3] << std::endl;
    } */
    int c = 0;
    int ansB = 1;
    for (auto const& [k, v] : blueprints){
        if (c >= 3) break;
        //int k = 2;
        //blueprint v = blueprints[k];
        state start;
        start.rates = startRates;
        start.resources = startResources;
        start.time = 32;
        
        std::deque<state> toCheck;
        toCheck.push_back(start);

        blueprint bpToUse = v;
        int curMax = 0;
        while(! toCheck.empty()) {
            state s = toCheck.front();
            toCheck.pop_front();
            /* int statusQuo = s.resources[3] + s.time*s.rates[3];
            if (statusQuo > curMax) {
                std::cout << s.resources[3] << " " << s.rates[3] << " " << s.time << std::endl;
                curMax = statusQuo;
                std::cout << curMax << std::endl;
            } */
            int theoreticalMax = s.resources[3] + s.time*s.rates[3] + s.time*(s.time-1)/2;
            if (theoreticalMax < curMax) {
                //std::cout << "Hej!" << toCheck.size() << std::endl;
                continue;
            }
            std::vector<int> times = timeToBuild(bpToUse, s);
            for (auto const& [indx, type] : iToRob) {
                bool buildAny = false;
                if (times[indx] >= 0 && times[indx] + 1 < s.time && s.rates[indx] < bpToUse.maxRate[indx]) {
                    buildAny = true;
                    state newS;
                    newS.resources = {0,0,0,0};//s.resources;
                    for (int i = 0; i < 4; i++) {
                        newS.resources[i] = s.resources[i] + (times[indx]+1)*s.rates[i];
                    }
                    //std::cout << "After gathering we have " << newS.resources[0] << " " << newS.resources[1] << " " << newS.resources[2] << " " << newS.resources[3] << std::endl;
                    newS.rates = {s.rates[0],s.rates[1],s.rates[2],s.rates[3]};
                    //newS.rates = s.rates;
                    newS.time = s.time - (times[indx] + 1);
                    newS.rates[indx] += 1;
                    for(int i = 0; i < 4 ; i ++) {
                        newS.resources[i] -= bpToUse.robots[type][i];
                    }
                    if (print) {
                        std::cout << "Building a " << type << " robot. It takes " << times[indx] << " minutes. We have " << s.time << " minutes left." << std::endl;
                        std::cout << "Pre robots " << s.rates[0] << " " << s.rates[1] << " " << s.rates[2] << " " << s.rates[3] << " robots" << std::endl;
                        std::cout << "Pre resources " << s.resources[0] << " " << s.resources[1] << " " << s.resources[2] << " " << s.resources[3] << " resources" << std::endl;
                        std::cout << "After resources " << newS.resources[0] << " " << newS.resources[1] << " " << newS.resources[2] << " " << newS.resources[3] << " resources" << std::endl;
                        std::cout << "After robots " << newS.rates[0] << " " << newS.rates[1] << " " << newS.rates[2] << " " << newS.rates[3] << " robots" << std::endl;
                        std::cout << "We have " << newS.time << " minutes left." << std::endl;
                    
                    }
                    //std::cout << "Built " << type << "We now have " << newS.resources[0] << ","<< newS.resources[1] << ","<< newS.resources[2] << ","<< newS.resources[3] << " ore. After time " << times[indx]+1 << " time left is " << newS.time << std::endl;
                    //std::cout << "We have " << newS.rates[0] << ","<< newS.rates[1] << ","<< newS.rates[2] << ","<< newS.rates[3] << " ore. After time " << times[indx]+1 << " time left is " << newS.time << std::endl;
                    toCheck.push_back(newS);
                }
                if (!buildAny) {
                    // Klara
                    int geodeCount = s.resources[3] + s.rates[3]*s.time;
                    if (geodeCount > curMax) {
                        curMax = geodeCount;
                    }
                    //std::cout << "Times out, we got " << geodeCount << " geodes!" << std::endl;
                }
            }
        }
        std::cout << "Using BP " << k << " we got " << curMax << std::endl;
        ansB *= curMax;
        c += 1;
    }
    std::cout << "Answer part B:" << ansB << std::endl;
}



