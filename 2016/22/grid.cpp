#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>

/*




*/

struct Disc
{
    int size{};
    int used{};
    int avail{};
};

std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos)
    {
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0)
        {
            vectorOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }
    return vectorOfStrings;
}

int main(int argc, char const *argv[])
{
    std::map<std::pair<int,int>, Disc> gridMap;
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
        while(getline(myfile,line)) {
            std::vector<std::string> split = splitLine(line);
            if(split.at(0).at(0) == '/') 
            {
                std::vector<std::string> node = splitLine(split.at(0),"-");
                int x{std::stoi(node.at(1).substr(1,-1))}, y{std::stoi(node.at(2).substr(1,-1))};
                int size{std::stoi(split.at(1).substr(0,split.at(1).length() - 1))};
                int used{std::stoi(split.at(2).substr(0,split.at(2).length() - 1))};
                int avail{std::stoi(split.at(3).substr(0,split.at(3).length() - 1))};
                gridMap.insert({std::make_pair(x,y), Disc{size, used, avail}});
            }
        }
    }
    int numPair = 0;
    for (auto const& [k1, v1] : gridMap)
    {
        for (auto const& [k2, v2] : gridMap)
        {
            if (k1 != k2)
            {
                if (v1.used <= v2.avail && v1.used > 0) {
                    //std::cout << "x" << k1.first << " y" << k1.second << " uses " << v1.used << std::endl;
                    //std::cout << "x" << k2.first << " y" << k2.second << " has " << v2.avail << std::endl;
                    numPair++;
                }

            }
        }
    }
    std::cout << "Answer part A: " << numPair << std::endl;

    
    for(int y = 0; y < 30; y++){ 
        for(int x = 0; x<=31; x++) {
            Disc d{gridMap[std::make_pair(x,y)]};
            if(d.used == 0)
            {
                std::cout << "_ ";
            }
            else if (d.used > 100)  
            {
                std::cout << "# ";
            }
            else
            {
                std::cout << ". ";
            }
            
        }
        std::cout << std::endl;
    }

    std::cout << "Answer part B: 181 (by hand)" << std::endl;
}