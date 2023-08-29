#include <iostream>
#include "md5.h"
#include <string>
 
 
int main(int argc, char *argv[])
{

    char passwordB[8] = {'-','-','-','-','-','-','-','-'};
    std::cout << passwordB << std::endl;
    int passwordBfound = 0;
    std::string start = "abbhdwsy";
    std::string password = "";
    bool passWordFound = false;
    int posNum = 0;
    while (! passWordFound) {
        posNum++;
        std::string md5test = md5( start + std::to_string(posNum));
        if (md5test.substr(0,5) == "00000") {
            char c = md5test[5];
            if (password.length() < 8){
                password += c;
            }
            if (('0' <= c) && (c <= '7')){
                int indx = c - '0';
                if( passwordB[indx] == '-'){
                    passwordB[indx] = md5test[6];
                    passwordBfound += 1;
                }
            }
        }
        if ((password.length() == 8) && (passwordBfound == 8)) {
            passWordFound = true;
        }
        
    }
    std::cout << "Answer part A: The password is: " << password << '\n';
    std::cout << "Answer part B: The password is: " << passwordB << '\n';

    
}