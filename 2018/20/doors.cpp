#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

std::map<char,std::pair<int,int>> dirs{{'E',{1,0}},{'S',{0,-1}},{'W',{-1,0}},{'N',{0,1}}};

struct room
{
    std::map<char,bool> doors{{'E',false},{'S',false},{'W',false},{'N',false}};
};

std::map<std::pair<int,int>,room> rooms;

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    if (argc > 1)
    {
        myfile.open(argv[1]);
    }
    else
    {
        return -1;
    }
    if (myfile.is_open())
    {
        getline(myfile,line);
    }
    myfile.close();
    
    
    
}