#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int width = 50;
int height = 6;



std::vector<std::string> splitLine(std::string line, std::string split = " "){
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos){
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0){
            vectorOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }

    return vectorOfStrings;

}

int main(int argc, char* argv[]){
    char display[height][width];
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            display[y][x] = ' ';
        }
    }

    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            std::vector<std::string> lineVector = splitLine(line);
            if(lineVector.at(0) == "rect"){
                std::vector<std::string> rectSize = splitLine(lineVector.at(1),"x");
                int rectWidth = std::stoi(rectSize.at(0));
                int rectHeight = std::stoi(rectSize.at(1));
                for(int y = 0; y < rectHeight; y ++) {
                    for(int x = 0; x < rectWidth; x++) {
                        display[y][x] = '#';
                    }
                }
            } else {
                int amnt = std::stoi(lineVector.at(4));
                std::vector<std::string> rotAx = splitLine(lineVector.at(2),"=");
                int ax = std::stoi(rotAx.at(1));
                if (lineVector.at(1) == "column") {
                    char newCol[height];
                    for(int y = 0; y < height; y++){
                        newCol[(y+amnt)%height] = display[y][ax];
                    }
                    for(int y = 0; y < height; y++){
                        display[y][ax] = newCol[y];
                    }
                } else if (lineVector.at(1) == "row") {
                    char newRow[width];
                    for(int x = 0; x < width; x++){
                        newRow[(x+amnt)%width] = display[ax][x];
                    }
                    for(int x = 0; x < width; x++){
                        display[ax][x] = newRow[x];
                    }

                }
            }
            
        }
    }
    int numShown = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(display[y][x] == '#'){
                numShown += 1;
            }
        }
    }
    if(argc > 2) {
        std::cout << std::endl;
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                std::cout << display[y][x];
            }
            std::cout << std::endl;
        }
    }
    std::cout << "Answer part A: the number of shown pixels is " << numShown << std::endl;
}