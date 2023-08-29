#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <unordered_set>

bool canMove(std::string shape, int col, int row, std::vector<std::unordered_set<int>> playField) {
    // pos is lower left corner of the shape 
    if (row <= 0) return false;
    if (shape == "row") {
        if (col < 0 || col + 3 > 6) return false;
        if(playField[col].contains(row)) {
            return false;
        } else if(playField[col+1].contains(row)) {
            return false;
        } else if(playField[col+2].contains(row)) {
            return false;
        } else if(playField[col+3].contains(row)) {
            return false;
        }
        return true;
    } else if (shape == "plus") {
        if (col < 0 || col + 2 > 6) return false;
        if(playField[col+1].contains(row)) {
            return false;
        } else if(playField[col+1].contains(row+1)) {
            return false;
        } else if(playField[col+1].contains(row+2)) {
            return false;
        } else if(playField[col].contains(row+1)) {
            return false;
        } else if(playField[col+2].contains(row+1)) {
            return false;
        }
        return true;
    } else if (shape == "corner") {
        if (col < 0 || col + 2 > 6) return false;
        if(playField[col].contains(row)) {
            return false;
        } else if(playField[col+1].contains(row)) {
            return false;
        } else if(playField[col+2].contains(row)) {
            return false;
        } else if(playField[col+2].contains(row+1)) {
            return false;
        } else if(playField[col+2].contains(row+2)) {
            return false;
        }
        return true;
    } else if (shape == "col") {
        if (col < 0 || col > 6) return false;
        if(playField[col].contains(row)) {
            return false;
        } else if(playField[col].contains(row+1)) {
            return false;
        } else if(playField[col].contains(row+2)) {
            return false;
        } else if(playField[col].contains(row+3)) {
            return false;
        }
        return true;
    } else if (shape == "square") {
        if (col < 0 || col + 1 > 6) return false;
        if(playField[col].contains(row)) {
            return false;
        } else if(playField[col+1].contains(row)) {
            return false;
        } else if(playField[col].contains(row+1)) {
            return false;
        } else if(playField[col+1].contains(row+1)) {
            return false;
        } 
        return true;
    }
    std::cout << "ERROR!" << std::endl;
    return false;
}

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
        getline(myfile,line);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        myfile.open("input");
        getline(myfile,line);
    }

    std::vector<std::unordered_set<int>> playField(7);
    std::vector<std::string> order = {"row", "plus", "corner", "col", "square"};

    int dropped = 0;
    int maxHeight = 0;
    int iteration = 0;
    while (dropped < 500) {

        std::cout << dropped%order.size() << " : " << iteration % line.length() << " " << maxHeight << std::endl;
        std::string toDrop = order[dropped % order.size()];
        int row = maxHeight + 4;
        int col = 2;
        bool falling = true;
        while (falling) {
            char move = line[iteration % line.length()];
            //std::cout << toDrop << " moving " << move << " at " << std::get<0>(pos) << " : " << std::get<1>(pos) << std::endl;
            if (move == '<') {
                int newCol = col - 1;
                if (canMove(toDrop, newCol, row, playField)) {
                    col = newCol;
                }
            } else if (move == '>') {
                int newCol = col + 1;
                if (canMove(toDrop, newCol, row, playField)) {
                    col = newCol;
                }
            }
            //std::cout << toDrop << " moving " << " DOWN " << " at " << std::get<0>(pos) << " : " << std::get<1>(pos) << std::endl;
            int newRow = row - 1;
            if (canMove(toDrop, col, newRow, playField)) {
                row = newRow;
            } else {
                falling = false;
                //std::cout << toDrop << " stopped with coord " << col << "," << row << " iteration " << iteration << std::endl;
                if (toDrop == "row") {
                    playField[col].insert(row);
                    playField[col+1].insert(row);
                    playField[col+2].insert(row);
                    playField[col+3].insert(row);
                    if (row > maxHeight) {
                        maxHeight = row;
                    }
                } else if (toDrop == "plus") {
                    playField[col+1].insert(row);
                    playField[col+1].insert(row+1);
                    playField[col+1].insert(row+2);
                    playField[col].insert(row+1);
                    playField[col+2].insert(row+1);
                    if (row + 2 > maxHeight) {
                        maxHeight = row+2;
                    }
                } else if (toDrop == "corner") {
                    playField[col].insert(row);
                    playField[col+1].insert(row);
                    playField[col+2].insert(row);
                    playField[col+2].insert(row+1);
                    playField[col+2].insert(row+2);
                    if (row + 2 > maxHeight) {
                        maxHeight = row+2;
                    }
                } else if (toDrop == "col") {
                    playField[col].insert(row);
                    playField[col].insert(row+1);
                    playField[col].insert(row+2);
                    playField[col].insert(row+3);
                    if (row + 3 > maxHeight) {
                        maxHeight = row+3;
                    }
                } else if (toDrop == "square") {
                    playField[col].insert(row);
                    playField[col].insert(row+1);
                    playField[col+1].insert(row);
                    playField[col+1].insert(row+1);
                    if (row + 1 > maxHeight) {
                        maxHeight = row+1;
                    }
                }
            }

            iteration += 1;
        }

        dropped += 1;
    }
    std::cout << "After 2022 rocks we have height " << maxHeight << " and " << iteration << " iterations" << std::endl;

}