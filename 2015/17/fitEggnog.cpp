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

std::vector<int> containers;
std::map<int, int> minNumber;
int numContainers(int val, int indx, int depth){
    if(val == 150){
        if(minNumber.find(depth) == minNumber.end()){
            minNumber[depth] = 0;
        }
        minNumber[depth] += 1;
        return 1;
    } else if(val > 150){
        return 0;
    } else if( (val < 150) && (indx == (containers.size()-1))){
        return 0;
    }
    int numSucc = 0;
    indx += 1;
    while(indx < containers.size()){
        numSucc += numContainers(val+containers.at(indx), indx, depth+1);
        indx += 1;
    }
    return numSucc;
}

int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            containers.push_back(std::stoi(line));
        }
    }
    myfile.close();
    std::cout << containers.size() << std::endl;
    std::cout << "Answer part A: There are " << numContainers(0,-1,0) << " way to fill the eggnog!" << std::endl;

    for(auto const& [key, val] : minNumber){
        std::cout << "Using " << key << " containers, we found " << val << " different ways!" << std::endl;
    }
}