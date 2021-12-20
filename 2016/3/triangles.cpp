#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

std::list<std::string> splitLine(std::string line, std::string split = " "){
    std::list<std::string> listOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos){
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0){
            listOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }

    return listOfStrings;

}

int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;
    
    int numTri = 0;
    int numTest = 0;

    std::list<std::list<int>> newTrianges;

    myfile.open(argv[1]);
    
    if(myfile.is_open()){
        std::list<int> tri1, tri2, tri3;
        while(getline(myfile,line)){
            
            numTest += 1;
            std::list<std::string> sides = splitLine(line);
            std::list<int> sidesInt;
            int idx = 1;

            for(std::string const& s : sides){
                sidesInt.push_back(std::stoi(s));
                switch (idx)
                {
                case 1:
                    tri1.push_back(std::stoi(s));
                    break;
                case 2:
                    tri2.push_back(std::stoi(s));
                    break;
                case 3:
                    tri3.push_back(std::stoi(s));
                    break;
                default:
                    break;
                }
                idx +=1;
            }

            if(numTest % 3 == 0){
                newTrianges.push_back(tri1);
                newTrianges.push_back(tri2);
                newTrianges.push_back(tri3);
                tri1.clear();
                tri2.clear();
                tri3.clear();
            }

            sidesInt.sort();
            int val = 0;
            bool triangle = true;
            int i = 0;
            for(int const& s : sidesInt){
                std::cout << s << " ";
                if (i < 2){
                    val += s;
                } else {
                    if (val <= s){
                        triangle = false;
                    }
                }
                i++;
            }
            std::cout << " | " << val << " | ";
            if(triangle){
                std::cout << line << " is a triangle" << std::endl;
                numTri += 1;
            } else{
                std::cout << line << " is not a triangle" << std::endl;
            }

        }
    }
    myfile.close();
    std::cout << "Answer part A: The number of possible triangles are " << numTri << " out of " << numTest << std::endl;
    int validNew = 0;
    for(std::list<int>& tri : newTrianges){
        tri.sort();
        int val = 0;
        int i = 0;
        bool triangle = true;
        for (int const& s : tri){
            std::cout << s << " ";
            if (i < 2) {
                val += s;
            } else {
                if (val <= s){
                    triangle = false;
                }
            }
            i += 1;
        }
        std::cout << std::endl;
        if (triangle) {
            validNew += 1;
        }
    }
    std::cout << "Answer part B: The number of possible triangles are " << validNew << " out of " << newTrianges.size() << std::endl;
}