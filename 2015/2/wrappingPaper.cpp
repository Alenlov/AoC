#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string line;
    int totalPaper = 0;
    int totalRibbon = 0;
    ifstream myfile;
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            int paperToAdd = 0;
            int ribbonToAdd = 0;
            size_t firstX = line.find('x');
            size_t secondX = line.find('x',firstX+1);
            // cout << line.substr(0,firstX) << ' ' << line.substr(firstX + 1, secondX - firstX - 1) << ' ' << line.substr(secondX + 1) << '\n';
            int side1, side2, side3, area1, area2, area3, circ1, circ2, circ3, vol;
            side1 = stoi(line.substr(0,firstX));
            side2 = stoi(line.substr(firstX + 1, secondX - firstX - 1));
            side3 = stoi(line.substr(secondX + 1));
            area1 = side1*side2;
            area2 = side2*side3;
            area3 = side3*side1;
            circ1 = 2*(side1 + side2);
            circ2 = 2*(side2 + side3);
            circ3 = 2*(side3 + side1);
            vol = side1*side2*side3;
            paperToAdd += 2*(area1 + area2 + area3);
            if ( (area1 < area2) && (area1 < area3) ) {
                paperToAdd += area1;
            } else if (area2 < area3) {
                paperToAdd += area2;
            } else {
                paperToAdd += area3;
            }
            totalPaper += paperToAdd;
            ribbonToAdd += vol;
            if ( (circ1 < circ2) && (circ1 < circ3) ) {
                ribbonToAdd += circ1;
            } else if (circ2 < circ3) {
                ribbonToAdd += circ2;
            } else {
                ribbonToAdd += circ3;
            }
            totalRibbon += ribbonToAdd;
        }
    }
    myfile.close();
    cout << "Answer part A: Total paper needed is: " << totalPaper << '\n';
    cout << "Answer part B: Total ribbon length needed is: " << totalRibbon << '\n';
    return 0;
}