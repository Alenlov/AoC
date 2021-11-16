#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

string toPos(int x, int y){
    string pos;
    pos = '(' + to_string(x) + ',' + to_string(y) + ')';
    return pos;
}

void move(int& x, int& y, char c) {
    const char left = '<',right = '>',up = '^',down = 'v';
    switch(c) {
            case up:
                y += 1;
                break;
            case down:
                y -= 1;
                break;
            case left:
                x -= 1;
                break;
            case right:
                x += 1;
                break;
        }
}

int main(int argc, char *argv[]) {
    cout << __cpluplus << '\n';
    string line;
    const char left = '<',right = '>',up = '^',down = 'v';
    ifstream myfile;
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        getline(myfile,line);
    }
    myfile.close();
    map<string, int> m;
    int posx = 0, posy = 0;
    string pos = toPos(posx, posy);
    cout << pos << '\n';
    m[pos] = 1;
    for (string::size_type i = 0; i < line.size(); i++ ){
        char c = line[i];
        switch(c) {
            case up:
                posy += 1;
                break;
            case down:
                posy -= 1;
                break;
            case left:
                posx -= 1;
                break;
            case right:
                posx += 1;
                break;
        }
        pos = toPos(posx, posy);
        if (m.find(pos) != m.end()) {
            m[pos] += 1;
        } else {
            m[pos] = 1;
        }


    }
    cout << "Answer part A: Number of visited houses is: " << m.size() << '\n';

    int santax = 0, santay = 0, robotx = 0, roboty = 0;
    map<string, int> m2;
    pos = toPos(robotx, roboty);
    m2[pos] = 2;
    for(size_t i = 0; i < line.size(); i ++ ) {
        if (i % 2) {
            move(robotx, roboty, line[i]);
            pos = toPos(robotx, roboty);
        } else {
            move(santax, santay, line[i]);
            pos = toPos(santax, santay);
        }
        if (m2.find(pos) != m2.end()) {
            m2[pos] += 1;
        } else {
            m2[pos] = 1;
        }
    }
    cout << "Anser part B: Number of visited houses is: " << m2.size() << '\n';

    
}

