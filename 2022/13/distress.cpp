#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

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

int closeBracket(std::string exp, int indx = 0) {
    if(exp[indx] != '[') {
        for(int i = 0; i < exp.length() - indx; i ++) {
            if(exp[i+indx] == ',' || exp[i+indx] == ']' ) {
                return i;
            }
        }
    } else {
        int toClose = 0;
        for(int i = 0; i < exp.length() - indx; i ++) {
            if(exp[i+indx] == ']' ) {
                toClose -= 1;
            } else if (exp[i+indx] == '[') {
                toClose += 1;
            }
            if(toClose == 0) {
                return i - 1;
            }
        }
    }
    return -1;
}

int smaller(std::string lhs, std::string rhs) {
    //std::cout << lhs << std::endl;
    //std::cout << rhs << std::endl;
    if (lhs.size() == 0 && rhs.size() == 0) {
        return 0;
    } else if (lhs.size() == 0) {
        return 1;
    } else if (rhs.size() == 0) {
        return -1;
    }
    if (lhs == rhs) return 0;
    int lenLhs = closeBracket(lhs);
    int lenRhs = closeBracket(rhs);
    int res = 0;
    std::size_t lhsComma = lhs.find(',',lenLhs);
    std::size_t rhsComma = rhs.find(',',lenRhs);
    std::string newLhs = "";
    std::string newRhs = "";
    if(lhs[0] == '[' && rhs[0] == '[') {
        res = smaller(lhs.substr(1,lenLhs), rhs.substr(1,lenRhs));
        if (res != 0) {
            return res;
        } else {
        }
    } else if(lhs[0] == '[') {
        res = smaller(lhs.substr(1,lenLhs), rhs.substr(0,lenRhs));
        if (res != 0) {
            return res;
        } else {
        }
    } else if(rhs[0] == '[') {
        res = smaller(lhs.substr(0,lenLhs), rhs.substr(1,lenRhs));
        if (res != 0) {
            return res;
        } else {
        }
    } else {
        int l,r;
        if (lhsComma != std::string::npos){
            l = std::stoi(lhs.substr(0,lhsComma));
        } else {
            l = std::stoi(lhs);
        }
        if (rhsComma != std::string::npos) {
            r = std::stoi(rhs.substr(0,rhsComma));
        } else {
            r = std::stoi(rhs);
        }
        if (l < r) {
            return 1;
        } else if (r < l) {
            return -1;
        }
    }
    if (lhsComma != std::string::npos) {
        newLhs = lhs.substr(lhsComma+1);
    }
    if (rhsComma != std::string::npos) {
        newRhs = rhs.substr(rhsComma+1);
    }
    res = smaller(newLhs,newRhs);
    return res;
}

bool compareInputs(std::string lhs, std::string rhs) {
    return smaller(lhs,rhs) == 1;
}

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string lhs, rhs;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    std::vector<std::string> allInputs;
    int sum = 0;
    if(myfile.is_open()) {
        int row = 0;
        while(getline(myfile,lhs)){
            if(lhs != "") {
                row += 1;
                getline(myfile,rhs);
                allInputs.push_back(lhs);
                allInputs.push_back(rhs);
            } else {
                continue;
            }
            int res = smaller(lhs,rhs);
            if (res == 1) {
                
                sum += row;
            }
        }

    }
    allInputs.push_back("[[2]]");
    allInputs.push_back("[[6]]");
    std::cout << "Sum of ordered packages is " <<  sum << std::endl;
    myfile.close();

    std::sort(allInputs.begin(), allInputs.end(), compareInputs);
    int prod = 1;
    for(int i = 0; i < allInputs.size(); i ++) {
        std::cout << allInputs[i] << std::endl;
        if (allInputs[i] == "[[2]]" || allInputs[i] == "[[6]]") prod *= (i+1);
    }
    std::cout << "Product of indices is " << prod << std::endl;
}