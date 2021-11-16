#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    
    std::string line;
    std::ifstream myfile;
    int lenCode = 0, numChar = 0, numCharB = 0;
    myfile.open(argv[1]);
    int id = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            lenCode += line.size();
            int indx = 1;
            while (indx < line.size() - 1) {
                std::cout << line[indx];
                numChar++;
                if (line[indx] == '\\') {
                    if (line[indx+1] == 'x') {
                        indx += 4;
                    } else {
                        indx += 2;
                    }
                } else {
                    indx += 1;
                }
            }
            std::cout << std::endl;
            int charInNew = 2;
            for (int i = 0; i < line.size(); i++) {
                if ((line[i] == '"') | (line[i] == '\\')) {
                    charInNew += 2;
                } else {
                    charInNew += 1;
                }
            }
            numCharB += charInNew;

        }
    }
    std::cout << "Answer part A: The total number of char in code is " << lenCode << " the number of char in memory is " << numChar << " The difference is " << (lenCode - numChar) << std::endl;
    std::cout << "Answer part B: The total number of char in new code is " << numCharB << " the number of char in original is " << lenCode << " The difference is " << (numCharB - lenCode) << std::endl;
    return 0;
}