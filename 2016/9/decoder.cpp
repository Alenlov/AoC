#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> splitLine(std::string line, std::string split = " "){
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos){
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0){
            vectorOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }
    return vectorOfStrings;
}

long long lengthDecoded(std::string input, bool partA = false){
    long long decodedLength = 0;
    std::size_t indx = 0;

    while(indx < input.length()){
        if(input[indx] == '(')
        {
            std::size_t closeIndx = input.find(')',indx);
            std::string copyInfo = input.substr(indx+1, closeIndx - indx - 1);
            std::vector<std::string> copyContent = splitLine(copyInfo,"x");
            int lengthToCopy = std::stoi(copyContent.at(0));
            int numCopies = std::stoi(copyContent.at(1));

            std::string insidePart = input.substr(closeIndx+1,lengthToCopy);
            if(partA)
            {
                decodedLength += lengthToCopy * numCopies;
            }
            else
            {
                decodedLength += numCopies * lengthDecoded(insidePart);
            }
            indx = closeIndx + lengthToCopy + 1;
            
        }
        else
        {
            decodedLength += 1;
            indx += 1;
        }
        
    }
    return decodedLength;
}

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        getline(myfile,line);
    } else {
        return 0;
    }

    
    

    std::cout << "Answer part A : the length is " << lengthDecoded(line, true) << std::endl;
    std::cout << "Answer part B : the length is " << lengthDecoded(line) << std::endl;
}