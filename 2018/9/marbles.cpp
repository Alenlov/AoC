#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <list>
#include <unordered_map>

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
    const std::regex reFull("(\\d+) players; last marble is worth (\\d+) points");
    std::smatch m;
    int numPlayers;
    int lastPoints;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            if (std::regex_match(line, m, reFull))
            {
                numPlayers = std::stoi(m[1]);
                lastPoints = std::stoi(m[2]);
            }
        }
    }
    myfile.close();
    
    std::list<long> marbles{0};
    bool playing{true};
    long curPlayer{0}, curStone{1};
    std::list<long>::iterator it = marbles.begin();
    std::unordered_map<int,long> points;
    bool aDone{false};
    while(playing)
    {
        //std::cout << *it << std::endl;
        // 2 step to the right
        if (curStone % 23 != 0)
        {
            for (int i = 0; i < 2; i++)
            {
                if (it == marbles.end()) it = marbles.begin();
                ++it;
            }
            marbles.insert(it, curStone);
            --it;
        }
        else
        {
            for (int i = 0; i < 7; i++)
            {
                if (it == marbles.begin()) it = marbles.end();
                --it;
            }
            long valToRemove = *it;
            //std::cout << "Removing " << valToRemove << std::endl;
            it = marbles.erase(it);
            points[curPlayer] += valToRemove + curStone;
            //std::cout << "Removing " << valToRemove << " with " << curStone << " total points: " << valToRemove + curStone << std::endl;
        }
        /* for (int m : marbles)
        {
            std::cout << m << " ";
        }
        std::cout << std::endl; */
        ++curStone;
        ++curPlayer;
        curPlayer %= numPlayers;
        if (curStone > lastPoints && !aDone)
        {
            aDone = true;
            long maxScore{-1};
            for (auto [p, s] : points)
            {
                if (s > maxScore) maxScore = s;
            }

            std::cout << "Answer part A: " << maxScore << std::endl;
        }
        if (curStone > 100*lastPoints) playing = false;

        
    }

    long maxScore{-1};
    for (auto [p, s] : points)
    {
        if (s > maxScore) maxScore = s;
    }

    std::cout << "Answer part B: " << maxScore << std::endl;
}

