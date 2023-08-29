#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <deque>

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

bool uniqueChars(std::string input) {
    for( int i = 0; i < input.length()-1; i ++) {
        if(input.find(input[i], i+1) != std::string::npos ) {
            return false;
        }
    }
    return true;
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
    bool moving = false;
    std::vector<std::deque<char>> stacksForA(9);
    std::vector<std::deque<char>> stacksForB(9);
    if (myfile.is_open()) {
        getline(myfile,line);
    }
    /* std::cout << line.substr(0,4) << " " << uniqueChars(line.substr(0,4)) << std::endl;
    std::cout << line.substr(4,4) << " " << uniqueChars(line.substr(4,4)) << std::endl;
    std::cout << "abcd" << " " << uniqueChars("abcd") << std::endl;    
    std::cout << "aaaa" << " " << uniqueChars("aaaa") << std::endl;
    std::cout << "aaba" << " " << uniqueChars("aaba") << std::endl;
    std::cout << "abaa" << " " << uniqueChars("abaa") << std::endl;
    std::cout << "aaab" << " " << uniqueChars("aaab") << std::endl; */
    bool startFound = false;
    int indx = 0;
    while(! startFound) {
        // Test if start begins at indx
        bool test = uniqueChars(line.substr(indx,4));
        if( test ) {
            startFound = true;
            break;
        } else {
            indx += 1;
        }
    }

    std::cout << "first marker after character " << indx + 4 << std::endl;
    //std::cout << line << std::endl;

    startFound = false;
    indx = 0;
    while(! startFound) {
        // Test if start begins at indx
        bool test = uniqueChars(line.substr(indx,14));
        if( test ) {
            startFound = true;
            break;
        } else {
            indx += 1;
        }
    }

    std::cout << "first marker after character " << indx + 14 << std::endl;

}