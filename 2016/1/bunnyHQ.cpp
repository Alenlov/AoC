#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <set>
#include <utility>

std::list<std::string> splitLine(std::string line){
    std::list<std::string> listOfStrings;
    std::string split = ", ";
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos){
        newIndx = line.find(split, indx);
        // std::cout << line.substr(indx, newIndx - indx) << std::endl;
        listOfStrings.push_back(line.substr(indx, newIndx - indx));
        indx = newIndx + split.size();
        // std::cout << "Index " << indx << std::endl;
    }

    return listOfStrings;

}


int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if(argc > 1){
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
    }
    if (myfile.is_open()){
        getline(myfile,line);
    }
    myfile.close();

    std::list<std::string> commands = splitLine(line);
    int pos = 0;
    int x = 0, y = 0;
    for(std::string const& cmd : commands){
        std::string turn = cmd.substr(0,1);
        int len = std::stoi(cmd.substr(1,-1));
        if(turn == "R"){
            pos += 1;
            pos %= 4;
        } else {
            pos -= 1;
            pos %= 4;
        }
        if (pos < 0){
            pos += 4;
        }
        std::cout << pos << std::endl;
        if (len > 10){
            std::cout << len << std::endl;
        }
        switch (pos)
        {
        case 0:
            y += len;
            break;
        case 1:
            x += len;
            break;
        case 2:
            y -= len;
            break;
        case 3:
            x -= len;
            break;
        }
    }
    std::cout << "Answer part A: We are " << abs(x)+abs(y) << " blocks away!" << std::endl;
    std::set<std::pair<int,int>> visited = {{0,0}};
    x = 0;
    y = 0;
    pos = 0;
    for(std::string const& cmd : commands){
        std::string turn = cmd.substr(0,1);
        int len = std::stoi(cmd.substr(1,-1));
        if(turn == "R"){
            pos += 1;
            pos %= 4;
        } else {
            pos -= 1;
            pos %= 4;
        }
        if (pos < 0){
            pos += 4;
        }
        std::cout << pos << std::endl;
        if (len > 10){
            std::cout << len << std::endl;
        }
        for(int l = 0 ; l < len ; l ++){
            switch (pos)
            {
            case 0:
                y += 1;
                break;
            case 1:
                x += 1;
                break;
            case 2:
                y -= 1;
                break;
            case 3:
                x -= 1;
                break;
            }
            std::pair<int, int> newPlace = {x,y};
            if(visited.find(newPlace) == visited.end()){
                visited.insert(newPlace);
            } else {
                goto found;
            }
        }
    }

    found:
    std::cout << "Answer part B: The first place visited twice is " << abs(x) + abs(y) << " blocks away!" << std::endl;
}