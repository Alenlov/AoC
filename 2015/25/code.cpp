#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> splitTask(std::string line){
    std::vector<std::string> split;
    int lastIndex = 0, newIndex = 0;
    std::string sep = " ";
    newIndex = line.find(sep, lastIndex);
    while ( newIndex != std::string::npos) {
        std::string part = line.substr(lastIndex,newIndex-lastIndex);
        split.push_back(part);
        lastIndex = newIndex+1;
        newIndex = line.find(sep, lastIndex);
    }
    std::string part = line.substr(lastIndex,std::string::npos);
    split.push_back(part);
    return split;
}

long long nextCode(long long code){
    return ((252533 * code) % 33554393);
}

int main(int argc, char *argv[]) {
    
    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    getline(myfile,line);
    myfile.close();

    int rowHead = line.find("row");
    int colHead = line.find("column");
    int comAfterRow = line.find(',', rowHead);
    int dotAfterCol = line.find('.', colHead);
    std::cout << line.substr(rowHead+4,comAfterRow-rowHead-4) << " " << line.substr(colHead+7,dotAfterCol - colHead-7) << std::endl;
    int row = std::stoi(line.substr(rowHead+4,comAfterRow-rowHead-4));
    int col = std::stoi(line.substr(colHead+7,dotAfterCol - colHead-7));
    int diag = row + col - 1;
    int codeNum = (diag * (diag-1))/2 + col;
    
    std::cout << "For row " << row << " and col " << col << " we have code number " << codeNum << std::endl;
    
    long long code = 20151125;
    for(int i = 1; i < codeNum; i++){
        code = nextCode(code);
    }
    std::cout << "The code is " << code << std::endl;
    return 0;
}