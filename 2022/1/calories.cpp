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
        return 0;
    }
    int max = 0;
    int second = 0;
    int third = 0;
    if (myfile.is_open()){
        int elf = 0;
        while( getline(myfile,line) ) {
            
            if( line == "") {
                //std::cout << "Vi har " << elf << " max ar " << max << std::endl;
                if( elf > max) {
                    third = second;
                    second = max;
                    max = elf;
                } else if ( elf > second)
                {
                    third = second;
                    second = elf;
                } else if (elf > third)
                {
                    third = elf;
                }
                
                
                elf = 0;
            } else {
                elf += std::stoi(line);
                //std::cout << line << " " << std::stoi(line) << " tot " << elf << std::endl;
            }
        }
        if( elf > max) {
                    third = second;
                    second = max;
                    max = elf;
                } else if ( elf > second)
                {
                    third = second;
                    second = elf;
                } else if (elf > third)
                {
                    third = elf;
                }
    }
    myfile.close();
    std::cout << "The maximum carrying is " << max << std::endl;
    std::cout << "The top three carry " << max + second + third << std::endl;
    return 1;
}