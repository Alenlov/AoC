#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

const int numLights = 1000;

int lights[numLights][numLights] = {0};

vector<string> splitTask(string line){
    vector<string> split;
    int lastIndex = 0, newIndex = 0;
    string sep = " ";
    newIndex = line.find(sep, lastIndex);
    while ( newIndex != string::npos) {
        string part = line.substr(lastIndex,newIndex-lastIndex);
        //cout << "Last index = " << lastIndex << " new index = " << newIndex << " sub string = " << part << endl;
        split.push_back(part);
        lastIndex = newIndex+1;
        newIndex = line.find(sep, lastIndex);
    }
    string part = line.substr(lastIndex,string::npos);
    split.push_back(part);
    //cout << "Last part is " << part << endl;
    return split;
}

pair<int, int> coordFromString(string msg) {
    pair<int, int> coordinates;
    string sep = ",";
    int indx = msg.find(sep);
    if (indx != string::npos) {
        int x = stoi(msg.substr(0,indx));
        int y = stoi(msg.substr(indx+1,string::npos));
        coordinates = make_pair(x,y);
    }
    return coordinates;
}

void performTask(string line) {
    //cout << line << endl;
    vector<string> split = splitTask(line);
    //for (string part : split) {
    //    cout << part << " ";
    //}
    //cout << endl;
    pair<int,int> upLeft, downRight;
    upLeft = coordFromString(split.at(split.size() - 3));
    downRight = coordFromString(split.at(split.size() - 1));
    if (split.size() == 4) {
        // TOGGLE
        cout << "TOGGLE : " << line << endl;
        for (int x = upLeft.first; x <= downRight.first; x++) {
            for (int y = upLeft.second; y <= downRight.second; y++) {
                lights[x][y] = 1 - lights[x][y];
            }
        }
    } else if (split.at(1) == "on") {
        //turn ON
        cout << "TURN ON : " << line << endl;
        for (int x = upLeft.first; x <= downRight.first; x++) {
            for (int y = upLeft.second; y <= downRight.second; y++) {
                lights[x][y] = 1;
            }
        }
    } else {
        //turn OFF
        cout << "TURN OFF : " << line << endl;
        for (int x = upLeft.first; x <= downRight.first; x++) {
            for (int y = upLeft.second; y <= downRight.second; y++) {
                lights[x][y] = 0;
            }
        }
    }

}

int main(int argc, char *argv[]) {
    
    string line;
    ifstream myfile;
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            performTask(line);
        }
    }
    myfile.close();
    int lightsOn = 0;
    for (int x = 0; x < numLights; x++) {
        for (int y = 0; y < numLights; y++) {
            lightsOn += lights[x][y];
        }
    }
    cout << "Answer part A : There are in total " << lightsOn << " lights on.\n";
    return 0;
}