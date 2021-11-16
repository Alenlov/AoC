#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char *argv[]) {
    string line;
    ifstream myfile;
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        getline(myfile,line);
    }
    myfile.close();
    int level = 0;
    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '(') {
            level++;
        } else if (c == ')')
        {
            level--;
        }
        
    }
    cout << "Answer part A: Santa goes to level: " << level << '\n';
    
    bool enteredBasement = false;
    int indx = 0;
    level = 0;
    while (!enteredBasement) {
        char c = line[indx];
        indx++;
        if (c == '(') {
            level++;
        } else if (c == ')') {
            level--;
        }
        if (level == -1){
            enteredBasement = true;
        }
    }

    cout << "Answer part B: Santa goers into the basement on position: " << indx << '\n';

}