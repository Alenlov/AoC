#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <map>
#include <vector>

std::map<char, int> snafu = {{'0',0},{'1',1},{'2',2},{'-',-1},{'=',-2}};
std::map<int, char> ufans = {{0,'0'},{1,'1'},{2,'2'},{-1,'-'},{-2,'='}};

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        return -1;
    }
    long long totVal = 0;
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            long long base = 1;
            long long val = 0;
            for (int i = line.length()-1; i > -1; --i) {
                //std::cout << line[i] << " : " << base * snafu[line[i]] << " . ";
                val += base * snafu[line[i]];
                base *= 5;
            }
            //std::cout << std::endl;
            //std::cout << line << " = " << val << std::endl;
            totVal += val;
        }
        myfile.close();
    }

    // bacwards
    std::string finalVal = "";

    while (totVal > 0) {
        long long r = totVal % 5;
        if (r < 3) {
            finalVal += ufans[r];
        } else {
            r = r - 5;
            totVal -= r;
            finalVal += ufans[r];
        }
        totVal /= 5;
    }
    std::cout << "Answer part A = ";
    for (int i = finalVal.length()-1; i >-1; i--) {
        std::cout << finalVal[i];
    }
    std::cout << std::endl;
    return 0;
}
