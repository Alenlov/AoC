#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

/*




*/

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

std::string processOperation(std::vector<std::string> operation, std::string current) 
{
    std::string newString;
    if(operation.at(0) == "swap") 
    {   
        int pos1,pos2;
        if(operation.at(1) == "position")
        {
            pos1 = std::stoi(operation.at(2));
            pos2 = std::stoi(operation.at(5));
        }
        else
        {
            std::string letter1{operation.at(2)}, letter2{operation.at(5)};
            pos1 = current.find(letter1, 0);
            pos2 = current.find(letter2, 0);
        }
        int minPos{std::min(pos1, pos2)};
        int maxPos{std::max(pos1, pos2)};
        newString = current.substr(0,minPos) + current.substr(maxPos,1) + current.substr(minPos+1,maxPos - minPos - 1) + current.substr(minPos,1) + current.substr(maxPos + 1,current.length() - maxPos - 1 );
        
    } 
    else if (operation.at(0) == "rotate")
    {
        int stepsRight;
        if (operation.at(1) == "left") {
            stepsRight = current.length() - std::stoi(operation.at(2));            
        }
        else if (operation.at(1) == "right")
        {
            stepsRight = std::stoi(operation.at(2));
        }
        else if (operation.at(1) == "based")
        {
            int pos = current.find(operation.at(6), 0);
            if (pos >= 4) {
                stepsRight = pos + 2;
            }
            else
            {
                stepsRight = pos + 1;
            }
            stepsRight %= current.length();
        }        
        newString = current.substr(current.length() - stepsRight, stepsRight) + current.substr(0, current.length() - stepsRight);
        
    }
    else if (operation.at(0) == "reverse")
    {
        int pos1{std::stoi(operation.at(2))}, pos2{std::stoi(operation.at(4))};
        newString = current.substr(0, pos1);
        for (int i = 0; i <= pos2-pos1; i++) {
            newString += current.substr(pos2 - i, 1);
        }
        newString += current.substr(pos2+1, current.length() - pos2 );

    }
    else if (operation.at(0) == "move")
    {
        int pos1{std::stoi(operation.at(2))}, pos2{std::stoi(operation.at(5))};
        if (pos1 < pos2) 
        {
            newString = current.substr(0,pos1) + current.substr(pos1+1,pos2-pos1) + current.substr(pos1,1) + current.substr(pos2+1,current.length() - pos2);
        }
        else
        {
            newString = current.substr(0,pos2) + current.substr(pos1,1) + current.substr(pos2,pos1 - pos2) + current.substr(pos1+1,current.length() - pos1);
        }
        
    }
    else
    {
        std::cout << "Unknown instruction " << operation.at(0) << std::endl;
    }
    
    return newString;
}

std::string unProcess(std::vector<std::string> operation, std::string current) 
{
    std::string newString;
    if(operation.at(0) == "swap") 
    {   
        int pos1,pos2;
        if(operation.at(1) == "position")
        {
            pos1 = std::stoi(operation.at(2));
            pos2 = std::stoi(operation.at(5));
        }
        else
        {
            std::string letter1{operation.at(2)}, letter2{operation.at(5)};
            pos1 = current.find(letter1, 0);
            pos2 = current.find(letter2, 0);
        }
        int minPos{std::min(pos1, pos2)};
        int maxPos{std::max(pos1, pos2)};
        newString = current.substr(0,minPos) + current.substr(maxPos,1) + current.substr(minPos+1,maxPos - minPos - 1) + current.substr(minPos,1) + current.substr(maxPos + 1,current.length() - maxPos - 1 );
        
    } 
    else if (operation.at(0) == "rotate")
    {
        int stepsRight;
        if (operation.at(1) == "left") {
            stepsRight = current.length() - std::stoi(operation.at(2));            
        }
        else if (operation.at(1) == "right")
        {
            stepsRight = std::stoi(operation.at(2));
        }
        else if (operation.at(1) == "based")
        {
            int pos = current.find(operation.at(6), 0);
            if (pos % 2 == 1)
            {
                stepsRight = pos/2 + 1;
            }
            else if (pos == 0)
            {
                stepsRight = 9;
            }
            else
            {
                stepsRight = pos/2 + 5;
            }
            stepsRight %= current.length();
        }
        int stepsLeft = stepsRight;
        newString = current.substr(stepsLeft, current.length() - stepsLeft) + current.substr(0, stepsLeft);
        
    }
    else if (operation.at(0) == "reverse")
    {
        int pos1{std::stoi(operation.at(2))}, pos2{std::stoi(operation.at(4))};
        newString = current.substr(0, pos1);
        for (int i = 0; i <= pos2-pos1; i++) {
            newString += current.substr(pos2 - i, 1);
        }
        newString += current.substr(pos2+1, current.length() - pos2 );

    }
    else if (operation.at(0) == "move")
    {
        int pos2{std::stoi(operation.at(2))}, pos1{std::stoi(operation.at(5))};
        if (pos1 < pos2) 
        {
            newString = current.substr(0,pos1) + current.substr(pos1+1,pos2-pos1) + current.substr(pos1,1) + current.substr(pos2+1,current.length() - pos2);
        }
        else
        {
            newString = current.substr(0,pos2) + current.substr(pos1,1) + current.substr(pos2,pos1 - pos2) + current.substr(pos1+1,current.length() - pos1);
        }
        
    }
    else
    {
        std::cout << "Unknown instruction " << operation.at(0) << std::endl;
    }
    
    return newString;
}

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line, word;
    std::list<std::vector<std::string>> allOperations;
    if (argc > 1)
    {
        myfile.open(argv[1]);
        if(std::string(argv[1]) == "test") word = "abcde";
        if(std::string(argv[1]) == "input") word = "abcdefgh";
    }
    else
    {
        return -1;
    }
    std::cout << word << std::endl;
    if (myfile.is_open())
    {
        while(getline(myfile,line)) {
            std::vector<std::string> split = splitLine(line);
            allOperations.emplace_front(split);
            word = processOperation(split, word);
            //std::cout << word << std::endl;
        }
    }

    std::cout << "Answer part A: " << word << std::endl;

    word = "fbgdceah";

    for(std::vector<std::string> op : allOperations) {
        word = unProcess(op, word);
        //std::cout << word << std::endl;
    }

    std::cout << "Answer part B: " << word << std::endl;
    
}