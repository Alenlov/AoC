#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>

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

int priority(char c) {
    int asciiVal = int(c);
    if (asciiVal > 95)
    {
        return asciiVal % 96;
    }
    else
    {
        return asciiVal % 64 + 26;
    }
    
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
    int totPrio = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            for ( int i = 0; i < line.length()/2 ; i++ ) {
                std::size_t found = line.find(line[i], line.length()/2);
                if ( found != std::string::npos ) {
                    //std::cout << "Det fanns två " << line[i] << " i " << line << " ASCII " << priority(line[i]) << std::endl;
                    totPrio += priority(line[i]);
                    break;
                }
            }
        }
    }
    myfile.close();
    std::cout << "Totall priority " << totPrio << std::endl;
    

    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    std::string line1, line2, line3;
    int totPrio2 = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line1)) {
            getline(myfile, line2);
            getline(myfile, line3);
            std::cout << line1 << std::endl << line2 << std::endl << line3 << std::endl;
            for ( int i = 0; i < line1.length() ; i++ ) {
                std::size_t found1 = line2.find(line1[i]);
                if ( found1 != std::string::npos ) {
                    std::size_t found2 = line3.find(line1[i]);
                    if (found2 != std::string::npos) {
                        totPrio2 += priority(line1[i]);
                        break;
                    }
                }
            }
        }
    }
    myfile.close();
    std::cout << "Total priority for badges " << totPrio2 << std::endl;
}