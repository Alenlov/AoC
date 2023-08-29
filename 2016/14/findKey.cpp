#include <iostream>
#include "md5.h"
#include <string>
#include <regex>
#include <map>
#include <set>

 
 
int main(int argc, char *argv[])
{
    // start + character
    std::set<int> keys;
    std::map<int, char> keyCandidates;

    std::string start{"jlmsuwbz"};
    if (argc > 1) {
        start = "abc";
    }
    std::regex match3{"([a-z0-9])\\1\\1"};
    std::regex match5{"([a-z0-9])\\1\\1\\1\\1"};
    int posNum{0};
    int finalNumber{0};
    bool doneA{false};
    while(!doneA)
    {    
        std::string md5hash = md5( start + std::to_string(posNum) );
        std::smatch m3;
        if (std::regex_search(md5hash, m3, match3)) {
            char c3{m3[1].str()[0]};
            keyCandidates[posNum] = c3;
        }
        std::smatch m5;
        if (std::regex_search(md5hash, m5, match5)) {
            char c5{m5[1].str()[0]};
            for (auto const &[k,v] : keyCandidates) {
                if (v == c5 && posNum < k + 1000 && posNum > k) {
                    keys.insert(k);
                    std::cout << "Found key " << k << " with char " << v << " second at time " << posNum << " " << keys.size() << '\n';
                    keyCandidates[k] = ' ';
                }
            }
        }
        if (keys.size() >= 64 && finalNumber == 0) {
            finalNumber = posNum + 1000;
        }
        if (finalNumber > 0 && posNum > finalNumber) {
            doneA = true;
        }
        posNum++;
    }
    int n{0};
    for (auto i : keys) {
        n++;
        if (n == 64) {
            std::cout << "Answer part A: " << i << '\n';
            break;
        }
    }
    bool doneB{false};

    std::set<int> keysB;
    std::map<int, char> keyCandidatesB;
    posNum = 0;
    finalNumber = 0;
    while(!doneB)
    {    
        std::string md5hash = start + std::to_string(posNum);
        for (int i = 0; i < 2017; i++) {
            md5hash = md5(md5hash);
        }
        std::smatch m3;
        if (std::regex_search(md5hash, m3, match3)) {
            char c3{m3[1].str()[0]};
            keyCandidatesB[posNum] = c3;
        }
        std::smatch m5;
        if (std::regex_search(md5hash, m5, match5)) {
            char c5{m5[1].str()[0]};
            for (auto const &[k,v] : keyCandidatesB) {
                if (v == c5 && posNum < k + 1000 && posNum > k) {
                    keysB.insert(k);
                    std::cout << "Found key " << k << " with char " << v << " second at time " << posNum << " " << keysB.size() << '\n';
                    keyCandidatesB[k] = ' ';
                }
            }
        }
        if (keysB.size() >= 64 && finalNumber == 0) {
            finalNumber = posNum + 1000;
        }
        if (finalNumber > 0 && posNum > finalNumber) {
            doneB = true;
        }
        posNum++;
    }
    n = 0;
    for (auto i : keysB) {
        n++;
        if (n == 64) {
            std::cout << "Answer part B: " << i << '\n';
            break;
        }
    }

    /* bool hashNotFound = true;
    int posNum = 0;
    while (hashNotFound) {
        posNum++;
        std::string md5test = md5( start + std::to_string(posNum));
        if (md5test.substr(0,5) == "00000") {
            hashNotFound = false;
            break;
        }
        
    }
    std::cout << "Answer part A: The positive number is: " << posNum << '\n';

    hashNotFound = true;
    posNum = 0;
    while (hashNotFound) {
        posNum++;
        std::string md5test = md5( start + std::to_string(posNum));
        if (md5test.substr(0,6) == "000000") {
            hashNotFound = false;
            break;
        }
        
    }
    std::cout << "Answer part B: The positive number is: " << posNum << '\n'; */
}