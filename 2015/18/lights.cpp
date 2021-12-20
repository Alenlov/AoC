#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>

int maxY;
int maxX;

std::set<std::pair<int, int>> setCorners(std::set<std::pair<int, int>> lights){
    lights.insert(std::make_pair(0,0));
    lights.insert(std::make_pair(0,maxY-1));
    lights.insert(std::make_pair(maxX-1,0));
    lights.insert(std::make_pair(maxX-1,maxY-1));
    return lights;
}

std::set<std::pair<int, int>> neighboors(std::pair<int, int> point){
    int x = point.first;
    int y = point.second;
    std::set<std::pair<int, int>> neighboorSet;
    std::set<int> dNbr = {-1,0,1};
    for(int const& dx : dNbr){
        for(int const& dy : dNbr){
            if(!((dx == 0)&&(dy == 0))){
                int newX = x + dx;
                int newY = y + dy;
                if( !((newX >= maxX) || (newX < 0) || (newY >= maxY) || (newY < 0))){
                    neighboorSet.insert(std::make_pair(newX,newY));
                }
            }
        }
    }
    return neighboorSet;
}

std::set<std::pair<int, int>> newLights(std::set<std::pair<int, int>> lightsOn, bool cornersOn = false){
    std::map<std::pair<int, int>, int> numNeighboors;
    for(std::pair<int, int> const& p: lightsOn){
        // std::cout << "(" << p.first << "," << p.second << ")" << std::endl;
        std::set<std::pair<int, int>> neighboorSet = neighboors(p);
        for(std::pair<int, int> const& nbr : neighboorSet){
            if(numNeighboors.find(nbr) == numNeighboors.end()){
                numNeighboors[nbr] = 1;
            } else{
                numNeighboors[nbr] += 1;
            }
        }
    }

    std::set<std::pair<int, int>> lights;
    for(auto const& [point, numNbr] : numNeighboors){
        if(lightsOn.find(point) != lightsOn.end()){
            if( (numNbr == 2) || (numNbr == 3) ){
                lights.insert(point);
            }
        } else {
            if( numNbr == 3) {
                lights.insert(point);
            }
        }
    }
    if(cornersOn){
        lights = setCorners(lights);
    }
    return lights;
}

void printLights(std::set<std::pair<int, int>> lights){
    for(int y = 0; y < maxY; y++){
        std::string line = "";
        for(int x = 0; x < maxX; x++){
            
            if(lights.find(std::make_pair(x,y)) == lights.end() ){
                line += ".";
            } else {
                line += "#";
            }
        }
        std::cout << line << std::endl;
    }
}

int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;
    std::set<std::pair<int, int>> lightsOn;
    int y = 0;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            maxX = line.size();
            for(int x = 0; x < line.size(); x++){
                if(line[x] == '#'){
                    lightsOn.insert(std::make_pair(x,y));
                }
            }
            y++;
        }
    }
    maxY = y;
    myfile.close();

    std::cout << maxX << " " << maxY << std::endl;
    int numItr = 100;
    for(int i = 0; i < numItr; i++){
        lightsOn = newLights(lightsOn);
    }
    std::cout << "Answer part A: After " << numItr << " iterations there are " << lightsOn.size() << " lights on!" << std::endl;

    std::set<std::pair<int, int>> lightsOnB;
    y = 0;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            maxX = line.size();
            for(int x = 0; x < line.size(); x++){
                if(line[x] == '#'){
                    lightsOnB.insert(std::make_pair(x,y));
                }
            }
            y++;
        }
    }
    maxY = y;
    // printLights(lightsOnB);
    // std::cout << std::endl;
    lightsOnB = setCorners(lightsOnB);
    // printLights(lightsOnB);
    // std::cout << std::endl;
    myfile.close();
    
    for(int i = 0; i < numItr; i++){
        lightsOnB = newLights(lightsOnB, true);
        // printLights(lightsOnB);
        // std::cout << std::endl;
    }
    std::cout << "Answer part B: After " << numItr << " iterations there are " << lightsOnB.size() << " lights on!" << std::endl;
}