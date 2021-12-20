#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <limits>

struct seating {
        std::vector<std::string> seated;
        int seatingHappiness = 0; 
        int maxHappy = std::numeric_limits<int>::min();
        int minHappy = std::numeric_limits<int>::max();
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

std::map<std::string, std::map<std::string, int>> happiness;
std::set<std::string> people;


int maxHappiness(seating S){
    if(S.seated.size() == 0){
        std::string firstPerson = *(people.begin());
        S.seated.push_back(firstPerson);
    } else if(S.seated.size() == people.size()){
        std::string firstPeron = S.seated.front();
        std::string lastPerson = S.seated.back();
        S.seatingHappiness += happiness[firstPeron].at(lastPerson);
        S.seatingHappiness += happiness[lastPerson].at(firstPeron);
        return S.seatingHappiness;
    }
    std::string currentPerson = S.seated.back();
    std::vector<int> happinesses;
    for(std::string const& other : people){
        if(! std::count(S.seated.begin(), S.seated.end(), other)){
            seating T = S;
            T.seated.push_back(other);
            T.seatingHappiness += happiness[currentPerson].at(other);
            T.seatingHappiness += happiness[other].at(currentPerson);
            happinesses.push_back(maxHappiness(T));
        }
    }
    int maxHappy = std::numeric_limits<int>::min();
    for(int const& value : happinesses){
        if(value > maxHappy){
            maxHappy = value;
        }
    }
    return maxHappy;
}


int main(int argc, char *argv[]) {
    
    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            std::vector<std::string> happinessLine = splitTask(line);
            std::string person = happinessLine.at(0);
            std::string other = happinessLine.at(happinessLine.size() - 1);
            other.pop_back();
            int value = std::stoi(happinessLine.at(3));
            // std::cout << "From " << line << " We found " << person << " and " << other << " with value " << value << std::endl;
            if(happinessLine.at(2) == "lose"){
                value = -value;
            }
            if(happiness.find(person) != happiness.end()){
                happiness[person].insert(std::make_pair(other,value));
            } else {
                std::map<std::string, int> personHappy;
                personHappy[other] = value;
                personHappy["Me"] = 0;
                happiness[person] = personHappy;
                people.insert(person);
            }
        }
    }
    myfile.close();
    std::map<std::string, int> personHappy;
    happiness["Me"] = personHappy;
    for(std::string const& other : people){
        happiness["Me"].insert(std::make_pair(other,0));
    }
    for(auto const& person : happiness){
        for(auto const& other : person.second ){
            std::cout << person.first << " changes happiness with " << other.second << " if sitting next to " << other.first << std::endl;
        }
    }
    seating S;
    int maxHappy = maxHappiness(S);
    std::cout << "Answer part A: the max change in happiness is " << maxHappy << std::endl;

    people.insert("Me");
    maxHappy = maxHappiness(S);
    std::cout << "Answer part B: the max change in happiness is " << maxHappy << std::endl;
    return 0;
}