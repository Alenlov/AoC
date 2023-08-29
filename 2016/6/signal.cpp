#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;

    myfile.open(argv[1]);

    std::string letterStrings[8] = {"","","","","","","",""};

    while(getline(myfile,line)) {
        for(int i = 0; i < 8; i++) {
            letterStrings[i] += line[i];
        }
    }

    std::string final = "";
    std::string finalB = "";
    for(int i = 0; i < 8; i++) {
        std::sort(letterStrings[i].begin(), letterStrings[i].end());
        char curChar = 'a';
        int curCount = 0;
        char best = 'a';
        char worst = 'a';
        int minVal = letterStrings[i].length();
        int maxVal = 0;
        for(char const& c : letterStrings[i]) {
            if(c == curChar){
                curCount += 1;
            } else {
                if (curCount > 0) {
                    if(curCount > maxVal) {
                        maxVal = curCount;
                        best = curChar;
                    }
                    if (curCount < minVal) {
                        minVal = curCount;
                        worst = curChar;
                    }
                    
                }
                curChar = c;
                curCount = 1;
            }
        }
        if (curCount > maxVal) {
            best = curChar;
        }
        if (curCount < minVal) {
            worst = curChar;
        }
        final += best;
        finalB += worst;
    }

    std::cout << "Answer part A: the message is " << final << std::endl;
    std::cout << "Answer part B: the message is " << finalB << std::endl;
    
}