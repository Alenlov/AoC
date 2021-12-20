#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct reindeer {
    int speed;
    int duration;
    int rest;
    int totalDist=0;
    int score=0;
    std::string name;
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



int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;
    std::map<std::string, reindeer> reindeers;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            std::vector<std::string> information = splitTask(line);
            reindeer R;
            R.name = information[0];
            R.speed = std::stoi(information[3]);
            R.duration = std::stoi(information[6]);
            R.rest = std::stoi(information[13]);
            reindeers[R.name] = R;
        }
    }
    myfile.close();
    int maxTime = 2503; // From puzzle
    int maxLength = 0;
    for(auto const& [name,R] : reindeers){
        std::cout << R.name << " has speed " << R.speed << std::endl;
        int oneCycle = R.duration + R.rest;
        int numCycle = maxTime / oneCycle;
        int distOneCycle = R.duration * R.speed;
        int totalDistance = numCycle * distOneCycle; // + R.speed * ( R.duration % (maxTime % oneCycle) );
        if ( R.duration > (maxTime % oneCycle) ){
            totalDistance += (maxTime % oneCycle) * R.speed;
        } else {
            totalDistance += R.duration * R.speed;
        }
        if(totalDistance > maxLength) {
            maxLength = totalDistance;
        }
    }
    std::cout << "Answer part A: the winning reindeer traveled " << maxLength << " km." << std::endl;
    int currentLeadDistance = 0;
    std::vector<std::string> leadNames;
    for(int seconds = 0; seconds < maxTime; seconds++){
        leadNames.clear();
        for(auto const& [name, R] : reindeers){
            // Moving or not
            if( (seconds % (R.duration + R.rest )) < R.duration ){
                reindeers[name].totalDist += R.speed;
            }
            if(reindeers[name].totalDist > currentLeadDistance){
                leadNames.clear();
                leadNames.push_back(name);
                currentLeadDistance = reindeers[name].totalDist;
            }else if (reindeers[name].totalDist == currentLeadDistance) {
                leadNames.push_back(name);
                currentLeadDistance = reindeers[name].totalDist;
            }

        }
        for(std::string const& name : leadNames){
            reindeers[name].score += 1;
        }
        if(leadNames.size() > 1){
            std::cout << "Tied lead after " << seconds << "s" << std::endl;
        }
    }
    int maxScore = 0;
    for(auto const& [name, R] : reindeers){
        if(R.score > maxScore){
            maxScore = R.score;
        }
    }
    std::cout << "Answer part B: The winning reindeer has a score of " << maxScore << std::endl;
    return 1;
}