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
#include <list>

struct valve
{
    std::string name;
    int flowRate;
    std::vector<std::string> nghbr;
    std::map<std::string,int> timeToDest;
};


std::vector<std::string> names;
std::vector<int> flowRates;
std::vector<std::vector<int>> travelTimes;

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

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    
    std::map<std::string, valve> valves;

    std::regex legit_command("Valve ([A-Z]{2}) has flow rate=(\\d+); [\\w ]+ ([A-Z, ]+)+");
    
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            std::smatch matches;
            if(std::regex_match(line, matches, legit_command)) {
                std::vector<std::string> toValves = splitLine(matches[3],", ");
                valve newValve;
                newValve.name = matches[1];
                newValve.flowRate = std::stoi(matches[2]);
                for (std::string s : toValves) {
                    newValve.nghbr.push_back(s);
                }
                
                valves[matches[1]] = newValve;
                names.push_back(matches[1]);
                flowRates.push_back(std::stoi(matches[2]));
            }
        }
    }
    int numValves = valves.size();
    for (auto & [k, v] : valves) {
        std::deque<std::tuple<std::string,int>> toVisit;
        toVisit.push_back(std::make_tuple(k,0));
        while (! toVisit.empty() ){
            std::string cur = std::get<0>(toVisit.front());
            int d = std::get<1>(toVisit.front());
            toVisit.pop_front();
            for(std::string n : valves[cur].nghbr) {
                if (n != k) {
                    if (v.timeToDest.find(n) == v.timeToDest.end()) {
                        v.timeToDest[n] = d + 1;
                        toVisit.push_back(std::make_tuple(n,d+1));
                    } else {
                        if (d + 1 < v.timeToDest[n]) {
                            v.timeToDest[n] = d+1;
                            toVisit.push_back(std::make_tuple(n,d+1));
                        }
                    }
                }
            } 
        }
    }

    
    std::string start = "AA";
    std::string history = "";
    // Current, history, totFlowrate, totFlow, timeLeft
    int maxFlow = 0;
    std::deque<std::tuple<std::string, std::string, int, int, int>> toDo;
    toDo.push_back(std::make_tuple(start, history, 0, 0, 30));
    while(! toDo.empty()) {
        std::string cur = std::get<0>(toDo.front());
        std::string his = std::get<1>(toDo.front());
        int curFR = std::get<2>(toDo.front());
        int totFlow = std::get<3>(toDo.front());
        int timeLeft = std::get<4>(toDo.front());
        toDo.pop_front();
        std::vector<std::string> visited = splitLine(his," ");
        for(auto const& [k, v] : valves[cur].timeToDest) {
            bool foundOne = false;
            if (std::find(visited.begin(), visited.end(), k) == visited.end() && valves[k].flowRate > 0 && timeLeft > v + 1) {
                int newFR = curFR + valves[k].flowRate;
                int newTotFlow = totFlow + (v+1)*curFR;
                int newTimeLeft = timeLeft - (v+1);
                std::string newHis = his + " " + k;
                toDo.push_back(std::make_tuple(k, newHis, newFR, newTotFlow, newTimeLeft));
                foundOne = true;
            }
            if (! foundOne) {
                int newTotFlow = totFlow + curFR * timeLeft;
                if (newTotFlow > maxFlow) {
                    maxFlow = newTotFlow;
                }
            }
        }
    }

    std::cout << "Answer part A: " << maxFlow << std::endl;


    // att modellera en elefant
    std::deque<std::tuple<std::string, std::string, int, int>> toDoB;
    std::vector<std::tuple<std::string, int>> solutions;
    toDoB.push_back(std::make_tuple("AA", "", 0, 26));
    while(! toDoB.empty()) {
        std::string me = std::get<0>(toDoB.front());
        std::string ope = std::get<1>(toDoB.front());
        int totFlow = std::get<2>(toDoB.front());
        int timeLeftMe = std::get<3>(toDoB.front());
        toDoB.pop_front();
        solutions.push_back(std::make_tuple(ope, totFlow));
        std::vector<std::string> visited = splitLine(ope," ");
        for(auto const& [k, v] : valves[me].timeToDest) {
            if (std::find(visited.begin(), visited.end(), k) == visited.end() && valves[k].flowRate > 0 && timeLeftMe > v + 1) {
                int newTimeLeft = timeLeftMe - (v+1);
                int newTotFlow = totFlow + newTimeLeft * valves[k].flowRate;
                std::string newHis;
                if (ope == "") {
                    newHis = k;
                } else {
                    newHis = ope + " " + k;
                }
                toDoB.push_back(std::make_tuple(k, newHis, newTotFlow, newTimeLeft));
            }
        }
        
        

    }

    std::sort(solutions.begin(), solutions.end(),[](auto const &t1, auto const &t2) {
        return std::get<1>(t1) > std::get<1>(t2); // or use a custom compare function
    });
    std::cout << std::get<1>(solutions[0]) << " " << std::get<1>(solutions[1]) << " " << std::get<1>(solutions[2]) << " " << solutions.size() << std::endl;
    int maxFlowB = 0;
    for (int i = 0;  i < solutions.size()/100 ; i ++) {
        std::vector<std::string> visitedValves = splitLine(std::get<0>(solutions[i]));
        for (int j = i + 1; j < solutions.size()/100 ; j++) {
            std::string otherHis = std::get<0>(solutions[j]);
            bool foundAny = false;
            for (std::string s : visitedValves) {
                if (otherHis.find(s) != std::string::npos) {
                    foundAny = true;
                    break;
                }
            }
            if (!foundAny) {
                int cand = std::get<1>(solutions[i]) + std::get<1>(solutions[j]);
                if (cand > maxFlowB) {
                    maxFlowB = cand;
                }
            }
        }
    }
    std::cout << maxFlowB << std::endl;

}