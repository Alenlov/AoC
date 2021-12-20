#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

int minNum = int('0');
int maxNum = int('9');
int minusSign = int('-');
std::string stopLine = "";
std::tuple<int, int> parseAccount(std::string account, int head){
    int value = 0;
    int startChar = int(account[head]);
    bool foundClose = false;
    bool inString = false;
    bool redFound = false;
    std::string number = "";
    while(!foundClose) {
        head += 1;
        if(startChar + 2 == int(account[head])){
            foundClose = true;
        } else if( (int(account[head]) == 123) || (int(account[head] == 91)) ){
            std::tuple<int, int> output = parseAccount(account, head);
            value += std::get<0>(output);
            head = std::get<1>(output);
        } else if( startChar == 123 ){
            // Object
            // std::cout << "In part for " << char(123) << " with character " << account[head] << std::endl;
            if(account[head] == '"'){
                inString = !inString;
                int nextHead = account.find('"',head+1);
                if ((nextHead - head - 1) == 3){
                    if(account.substr(head+1,nextHead - head - 1) == stopLine){
                        redFound = true;
                    }

                }
            }else if(!inString){
                if((minNum <= int(account[head])) && (int(account[head] <= maxNum)) || (int(account[head]) == minusSign) ){
                    // std::cout << "We have a number! " << account[head] << " with value " << int(account[head]) << std::endl;
                    number += account[head];
                    if(!( (minNum <= int(account[head+1])) && (int(account[head+1]) <= maxNum))){
                        value += std::stoi(number);
                        number = "";
                    }
                }
                
            }
        } else if( startChar == 91 ){
            // Array
            // std::cout << "In part for " << char(91) << " with character " << account[head] << std::endl;
            if(account[head] == '"'){
                inString = !inString;
            }else{
                if((minNum <= int(account[head])) && (int(account[head] <= maxNum)) || (int(account[head]) == minusSign) ){
                    // std::cout << "We have a number! " << account[head] << " with value " << int(account[head]) << std::endl;
                    number += account[head];
                    if(!( (minNum <= int(account[head+1])) && (int(account[head+1]) <= maxNum))){
                        value += std::stoi(number);
                        number = "";
                    }
                }
                
            }
        }

    }
    if(redFound){
        value = 0;
    }
    // std::cout << value << std::endl;
    return std::make_tuple(value, head);
}

int main(int argc, char *argv[]) {
    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        getline(myfile,line);
    }
    myfile.close();

    std::cout << "{ : " << int('{')<< " } : " << int('}')<< " [ : " << int('[')<< " ] : " << int(']') << std::endl;
    std::cout << char(124) << " " << char(92) << std::endl;
    std::tuple<int, int> output = parseAccount(line, 0);
    std::cout << "Answer part A: The total value is " << std::get<0>(output) << std::endl;
    stopLine = "red";
    output = parseAccount(line, 0);
    std::cout << "Answer part B: The total value is " << std::get<0>(output) << std::endl;
    return 0;
}