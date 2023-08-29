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
// A rock  B paper  C scissor
// X       Y        Z
// X slår C, Y slår A, Z slår B

int outcome(char they, char me){
    if( they == 'A') {
        if( me == 'X' ) 
        {
            return 3;
        } else if (me == 'Y')
        {
            return 6;
        } else
        {
            return 0;
        }
        
    } else if ( they == 'B')
    {
        if( me == 'X' ) 
        {
            return 0;
        } else if (me == 'Y')
        {
            return 3;
        } else
        {
            return 6;
        }
    } else
    {
        if( me == 'X' ) 
        {
            return 6;
        } else if (me == 'Y')
        {
            return 0;
        } else
        {
            return 3;
        }
    }
}

int myScore(char me) {
    if(me == 'X') 
    {
        return 1;
    } else if (me == 'Y')
    {
        return 2;
    } else
    {
        return 3;
    }
    
}

char myChoice(char they, char res) {
    if(res == 'Z') { // WIN
        if(they == 'A') {
            return 'Y';
        } else if (they == 'B')
        {
            return 'Z';
        } else {
            return 'X';
        }
    } else if (res == 'Y') // DRAW
    {
        if(they == 'A') {
            return 'X';
        } else if (they == 'B')
        {
            return 'Y';
        } else {
            return 'Z';
        }
    } else {
        if(they == 'A') {
            return 'Z';
        } else if (they == 'B')
        {
            return 'X';
        } else {
            return 'Y';
        }
    }
    
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
    int score1 = 0;
    int score2 = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<std::string> lineVec = splitLine(line);
            score1 += outcome(lineVec.at(0)[0], lineVec.at(1)[0]) + myScore(lineVec.at(1)[0]);
            char myPlay = myChoice(lineVec.at(0)[0], lineVec.at(1)[0]);
            score2 += outcome(lineVec.at(0)[0], myPlay) + myScore(myPlay);
        }
        
    }

    std::cout << "Before guide score is : " << score1 << std::endl;
    std::cout << "After guide score is : " << score2 << std::endl;

    return 1;
}