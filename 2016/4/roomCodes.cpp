#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>

std::string partBcheck = "northpole object storage";

bool decending(const std::pair<int, char>& first, const std::pair<int,char>& second){
    if (first.first > second.first) {
        return true;
    } else if ((first.first == second.first) && (first.second < second.second)) {
        return true;
    }
    return false;
}

struct RoomCode{
    std::list<std::string> encryptedNames;
    int sectorID;
    std::string checkSum;
};

bool isValid(RoomCode rc){
    std::list<std::pair<int,char>> letters;
    std::string fullString = "";
    for(std::string const& part : rc.encryptedNames){
        fullString += part;
    }
    std::sort(fullString.begin(), fullString.end());
    char curChar = 'a';
    int curCount = 0;

    for(char const& c : fullString){
        if(c == curChar) {
            curCount += 1;
        } else if (curCount > 0) {
            letters.push_back(std::make_pair(curCount,curChar));
            curCount = 1;
            curChar = c;
        } else {
            curCount = 1;
            curChar = c;
        }
    }
    letters.push_back(std::make_pair(curCount,curChar));
    letters.sort(decending);
    bool valid = true;
    int i = 0;
    for(auto const& p : letters) {
        if((i < rc.checkSum.length()) && valid) {
            if(p.second == rc.checkSum[i]) {
                i += 1;
            } else {
                valid = false;
            }
        }
    }
    return valid;
}

std::list<std::string> splitLine(std::string line, std::string split = " "){
    std::list<std::string> listOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos){
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0){
            listOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }
    return listOfStrings;

}

std::string unscramble(RoomCode rc){
    std::string output = "";
    for(std::string const& part : rc.encryptedNames) {
        if(output.length() > 0){
            output += " ";
        }
        for(char const& c : part) {
            output += char( (c - 'a' + rc.sectorID) % 26 + 'a' );
        }
    }
    return output;
}

int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;
    int ansB = 0;
    myfile.open(argv[1]);
    long long sumOfSectors = 0;
    if(myfile.is_open()){
        while(getline(myfile, line)){
            std::list<std::string> listOfStrings = splitLine(line, "-");
            std::string end = listOfStrings.back();
            listOfStrings.pop_back();
            RoomCode rc;
            rc.encryptedNames = listOfStrings;
            rc.sectorID = std::stoi(end.substr(0,3));
            rc.checkSum = end.substr(4,5);
            if(isValid(rc)){
                sumOfSectors += rc.sectorID;
                std::string unsc = unscramble(rc);
                if(unsc.compare(partBcheck) == 0){
                    ansB = rc.sectorID;
                }
            }

        }
    }
    std::cout << "Answer part A: the sum of the real rooms is " << sumOfSectors << std::endl;
    std::cout << "Answer part B: the sector ID of the room is " << ansB << std::endl;
}