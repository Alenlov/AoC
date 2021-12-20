#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>


int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    std::string code;
    std::string code2;
    int col2 = 0; 
    int row2 = 2;
    int col = 1;
    int row = 1;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            for(char const& c : line){
                if(c == 'R'){
                    col2 +=1;
                    if (col2 > (4 - abs(row2 - 2))){
                        col2 -= 1;
                    }
                    col += 1;
                    if (col > 2) {
                        col = 2;
                    }
                } else if (c == 'L') {
                    col2 -= 1;
                    if (col2 < abs(row2 - 2)) {
                        col2 += 1;
                    }
                    col -= 1;
                    if (col < 0) {
                        col = 0;
                    }
                } else if (c == 'U') {
                    row2 -= 1;
                    if (row2 < abs(col2 - 2)){
                        row2 += 1;
                    }
                    row -= 1;
                    if (row < 0) {
                        row = 0;
                    }
                } else if (c == 'D') {
                    row2 += 1;
                    if (row2 > (4 - abs(col2 - 2))){
                        row2 -= 1;
                    }
                    row += 1;
                    if (row > 2) {
                        row = 2;
                    }
                }
                std::cout << "At point (row, col) = " << row2 << "," << col2 << std::endl; 
            }
            std::cout << std::endl;
            code += std::to_string(1 + col + row*3);
            if(row2 == 0){
                code2 += '1';
            } else if (row2 == 1){
                code2 += std::to_string(1 + col2);
            } else if (row2 == 2){
                code2 += std::to_string(5 + col2);
            } else if (row2 == 3){
                if (col2 == 1) {
                    code2 += 'A';
                } else if (col2 == 2) {
                    code2 += 'B';
                } else {
                    code2 += 'C';
                }
            } else if (row2 == 4){
                code2 += 'D';
            }
        }
    }
    std::cout << "Answer part A: The code to the bathroom is " << code << std::endl;
    std::cout << "Answer part B: The code to the bathroom is " << code2 << std::endl;
}