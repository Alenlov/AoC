#include <string>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

const set<string> naughty = {"ab", "cd", "pq", "xy"};
const set<char> vowels = {'a', 'e', 'i', 'o', 'u'};


bool isNiceA(string msg) {
    int numVowels = 0;
    bool twiceInRow = false;
    for (int i = 0; i < msg.size(); i++) {
        char current = msg[i];
        if ( vowels.find(current) != vowels.end() ) {
            numVowels++;
        }
        if (i < msg.size() - 1) {
            if (current == msg[i+1]) {
                twiceInRow = true;
            } 
            string dub = msg.substr(i,2);
            if (naughty.find(dub) != naughty.end()) {
                return false;
            }
        }
    }
    if (numVowels > 2 && twiceInRow) {
        return true;
    } else {
        return false;
    }
}

bool isNiceB(string msg) {
    bool repeatIn2 = false;
    bool dubChar = false;
    for (int i = 0; i < msg.size(); i++) {
        if (i < msg.size()-2) {
            char cur = msg[i];
            if (cur == msg[i+2]) {
                repeatIn2 = true;
            }
            string dub = msg.substr(i,2);
            if (msg.find(dub,i+2) != string::npos) {
                dubChar = true;
            }
        }
    }
    return (dubChar && repeatIn2);
}

int main(int argc, char *argv[]) {
    string line;
    ifstream myfile;
    int niceStringsA = 0;
    int niceStringsB = 0;
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            if (isNiceA(line)) {
                niceStringsA++;
                //cout << line << " is nice!\n";
            } else {
                //cout << line << " is not nice!\n";
            }
            if (isNiceB(line)) {
                niceStringsB++;
                cout << line << " is nice!\n";
            } else {
                cout << line << " is not nice!\n";
            }
        }
    }
    myfile.close();
    cout << "Answer part A: In total there were " << niceStringsA << " nice lines!\n";
    cout << "Answer part B: In total there were " << niceStringsB << " nice lines!\n";
    return 0;
}