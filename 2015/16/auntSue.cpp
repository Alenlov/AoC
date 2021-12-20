#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

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
    std::set<std::string> greaterThan = {"cats", "trees"};
    std::set<std::string> smallerThan = {"pomeranians", "goldfish"};
    std::map<std::string, std::string> sue;

    myfile.open(argv[2]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            std::vector<std::string> splitLine = splitTask(line);
            splitLine[0].pop_back();
            sue[splitLine[0]] = splitLine[1];
            std::cout << splitLine[0] << " " << splitLine[1] << std::endl;
        }
    }
    myfile.close();

    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            std::vector<std::string> splitLine = splitTask(line);
            bool correctSue = true;
            int i = 2;
            while(i < splitLine.size()){
                splitLine[i].pop_back();
                std::string name = splitLine[i];
                std::string value = splitLine[i+1];
                std::size_t indxCom = value.find(',');
                if(indxCom != std::string::npos){
                    value.pop_back();
                }
                // std::cout << "Testing " << name << " correct has " << sue[name] << " " << splitLine[1] << " has " << value << std::endl;
                if(sue[name] != value){
                    correctSue = false;
                }

                i+=2;
            }
            if(correctSue) {
                splitLine[1].pop_back();
                std::cout << "Answer part A: Aunt Sue " << splitLine[1] << " is corect!" << std::endl;
            }
        }
    }
    myfile.close();

    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            std::vector<std::string> splitLine = splitTask(line);
            bool correctSue = true;
            int i = 2;
            while(i < splitLine.size()){
                splitLine[i].pop_back();
                std::string name = splitLine[i];
                std::string value = splitLine[i+1];
                std::size_t indxCom = value.find(',');
                if(indxCom != std::string::npos){
                    value.pop_back();
                }
                if(greaterThan.find(name) != greaterThan.end()){
                    if(std::stoi(sue[name]) >= std::stoi(value) ){
                        correctSue = false;
                    }
                } else if (smallerThan.find(name) != smallerThan.end()){
                    if(std::stoi(sue[name]) <= std::stoi(value) ){
                        correctSue = false;
                    }
                } else {
                    if(sue[name] != value){
                        correctSue = false;
                    }
                }

                i+=2;
            }
            if(correctSue) {
                splitLine[1].pop_back();
                std::cout << "Answer part B: Aunt Sue " << splitLine[1] << " is corect!" << std::endl;
            }
        }
    }
    myfile.close();
    
    return 0;
}