#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

bool hasTLS(std::string line){
    bool hasABBA = false;
    bool inBrackets = false;
    for(size_t idx = 1; idx < line.length()-2; idx++) {
        if (line[idx] == line[idx+1]) {
            if ((line[idx-1] == line[idx+2]) && (line[idx-1] != line[idx])) {
                if (inBrackets) {
                    return false;
                }
                hasABBA = true;
            }
        } else if (line[idx] == '[') {
            inBrackets = true;
        } else if (line[idx] == ']') {
            inBrackets = false;
        }
    }
    return hasABBA;
}

bool hasSSL(std::string line){
    bool inBrackets = (line[0] == '[');
    std::vector<std::tuple<char,char,bool>> ABAs;
    for(size_t idx = 1; idx < line.length() - 1; idx ++) {
        if (line[idx] == '[') {
            inBrackets = true;
        } else if (line[idx] == ']') {
            inBrackets = false;
        } else if((line[idx-1] == line[idx+1])&&(line[idx-1] != line[idx])) {
            ABAs.push_back(std::make_tuple(line[idx-1],line[idx],inBrackets));
        } 
    }
    if(ABAs.size() <= 1){
        return false;
    }
    for(int i = 0; i < ABAs.size()-1; i++){
        std::tuple<char,char,bool> lhs = ABAs.at(i);
        for(int j = i + 1 ; j < ABAs.size(); j++){
            std::tuple<char,char,bool> rhs = ABAs.at(j);
            if((std::get<0>(lhs) == std::get<1>(rhs)) && (std::get<1>(lhs) == std::get<0>(rhs)) && (( std::get<2>(lhs) != std::get<2>(rhs) ) )  ){
                return true;
            }
        }
    }
    return false;

}

int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;

    myfile.open(argv[1]);
    int countA = 0;
    int countB = 0;
    while (getline(myfile,line)) {
        if(hasTLS(line)){
            countA += 1;
        }
        if (hasSSL(line)){
            countB += 1;
        }
    }
    std::cout << "Answer part A: the number of adresses with TLS is " << countA << std::endl;
    std::cout << "Answer part B: the number of adresses with SSL is " << countB << std::endl;
    myfile.close();

}