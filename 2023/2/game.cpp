#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

std::map<std::string,int> maxVals{{"red",12}, {"green",13}, {"blue",14}};

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
    int sumA{0}, sumB{0};
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::map<std::string,int> minCubes{{"red",0},{"blue",0},{"green",0}};
            std::vector<std::string> idGames = splitLine(line, ": ");
            std::vector<std::string> game = splitLine(idGames[0], " ");
            std::vector<std::string> games = splitLine(idGames[1], "; ");
            int id = std::stoi(game[1]);
            bool possibleGame{true};
            for (int i{0}; i < games.size(); i++)
            {
                std::vector<std::string> gameSplit = splitLine(games[i], ", ");
                for (int j{0}; j < gameSplit.size(); j++)
                {
                    std::vector<std::string> ballSplit = splitLine(gameSplit[j], " ");
                    int num = std::stoi(ballSplit[0]);
                    if (num > maxVals[ballSplit[1]]) possibleGame = false;
                    if (num > minCubes[ballSplit[1]]) minCubes[ballSplit[1]] = num;
                }
            }

            if (possibleGame) sumA += id;
            int power{1};
            for (auto const [c, n] : minCubes)
            {
                power *= n;
            }
            sumB += power;
        }
    }
    myfile.close();

    std::cout << "Answer part A: " << sumA << std::endl;
    std::cout << "Answer part B: " << sumB << std::endl;
    
    
}