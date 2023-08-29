#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <utility>
#include <vector>
#include <tuple>
#include <map>

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> treeMap;
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            std::vector<int> row;
            for (int i = 0; i < line.length(); i++) {
                row.push_back(std::stoi(line.substr(i,1)));
                std::cout << std::stoi(line.substr(i,1));
            }
            std::cout << std::endl;
            treeMap.push_back(row);
        }
    }

    myfile.close();

    int numRows = treeMap.size();
    int numCols = treeMap[0].size();

    std::cout << numRows << " " << numCols << std::endl;
    std::set<std::tuple<int,int>> seenTrees;
    std::set<int> test;
    test.insert(3);

    for(int i = 0; i < numRows; i++){
        int maxUp = -1, maxDown = -1, maxLeft = -1, maxRight = -1;
        // Kolla på rad och kolumn i samtidigt!
        for (int j = 0; j < numRows; j++) {
            if(maxUp == 9 && maxDown == 9 && maxLeft == 9 && maxRight == 9) {
                break;
            }
            int revJ = numRows - j - 1;
            int up = treeMap[j][i];
            if (up > maxUp) {
                std::tuple<int,int> tree = std::make_tuple(j,i);
                seenTrees.insert( tree );
                maxUp = up;
            }
            int down = treeMap[revJ][i];
            if (down > maxDown) {
                std::tuple<int,int> tree = std::make_tuple(revJ,i);
                seenTrees.insert( tree );
                maxDown = down;
            }
            int left = treeMap[i][j];
            if (left > maxLeft) {
                seenTrees.insert( std::make_tuple(i,j));
                maxLeft = left;
            }
            int right = treeMap[i][revJ];
            if (right > maxRight) {
                seenTrees.insert( std::make_tuple(i, revJ));
                maxRight = right;
            }
            
        }
    }

    std::cout << "Number of seen trees is " << seenTrees.size() << std::endl;

    std::map<std::tuple<int,int>, int> scenicScore;

    for( int row = 1; row < numRows - 1; row++) {
        for (int col = 1; col < numCols - 1; col++) {
            int h = treeMap[row][col];
            int seenUp = 0;
            for(int l = 1; row - l >= 0 ; l ++){
                seenUp += 1;
                if (treeMap[row-l][col] >= h) {
                    break;
                }
            }
            int seenDown = 0;
            for(int l = 1; row + l < numRows ; l ++){
                seenDown += 1;
                if (treeMap[row+l][col] >= h) {
                    break;
                }
            }
            int seenLeft = 0;
            for(int l = 1; col - l >= 0 ; l ++){
                seenLeft += 1;
                if (treeMap[row][col - l] >= h) {
                    break;
                }
            }
            int seenRight = 0;
            for(int l = 1; col + l < numCols ; l ++){
                seenRight += 1;
                if (treeMap[row][col + l] >= h) {
                    break;
                }
            }
            //std::cout << "Tree at " << row << "," << col << " with height " << h << " sees " << seenUp << " " << seenDown << " "  << seenLeft << " " << seenRight << std::endl;
            int score = seenUp * seenDown * seenLeft * seenRight;
            scenicScore[std::make_tuple(row,col)] = score;

        }
    }
    int maxV = 0;
    for(auto const &[k, v] : scenicScore) {
        if ( v > maxV) {
            maxV = v;
        }
    }
    std::cout << "Max scenic score is " << maxV << std::endl;

}