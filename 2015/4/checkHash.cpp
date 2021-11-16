#include <iostream>
#include "md5.h"
#include <string>
 
using namespace std;
 
int main(int argc, char *argv[])
{
    string start = "yzbqklnj";
    bool hashNotFound = true;
    int posNum = 0;
    while (hashNotFound) {
        posNum++;
        string md5test = md5( start + to_string(posNum));
        if (md5test.substr(0,5) == "00000") {
            hashNotFound = false;
            break;
        }
        
    }
    cout << "Answer part A: The positive number is: " << posNum << '\n';

    hashNotFound = true;
    posNum = 0;
    while (hashNotFound) {
        posNum++;
        string md5test = md5( start + to_string(posNum));
        if (md5test.substr(0,6) == "000000") {
            hashNotFound = false;
            break;
        }
        
    }
    cout << "Answer part B: The positive number is: " << posNum << '\n';
}