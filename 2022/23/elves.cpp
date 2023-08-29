#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <list>
#include <vector>
#include <map>

std::map<char,char> nextDir = {{'N','S'},{'S','W'},{'W','E'},{'E','N'}};
std::vector<std::pair<int,int>> around = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
std::map<char,std::vector<int>> moveDir = {{'S',{5,6,7}}, {'E',{0,1,7}}, {'N',{1,2,3}}, {'W',{3,4,5}}};

std::map<char, std::pair<int,int>> move = {{'N', {0,-1}}, {'S', {0,1}}, {'W',{-1,0}}, {'E',{1,0}}};

/*
5   6   7
4       0
3   2   1
*/


int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    
    std::map<int,std::pair<int,int>> elves;
    std::map<std::pair<int,int>,int> elvPos;

    int elvIndx = 0;

    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return 0;
    }
    int y = 0;
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            for (int x = 0; x < line.length(); x++) {
                if (line[x] == '#') {
                    elves[elvIndx] = {x,y};
                    elvPos[{x,y}] = elvIndx;
                    elvIndx += 1;
                }
            }
            y += 1;
        }
    }
    char dir = 'N';
    int itr = 0;
    bool moving = true;
    while (moving) {
        itr += 1;
        
        //std::cout << std::endl << itr << " : " << dir << std::endl << std::endl;
        std::map<std::pair<int,int>,int> newElvPos;
        std::map<std::pair<int,int>,std::vector<int>> candidates;
        for (auto const& [i, e] : elves) {
            bool willMove = false;
            for (auto p : around) {
                if ( elvPos.contains( {p.first+e.first, p.second+e.second} ) ) {
                    willMove = true;
                    break;
                }
            }  
            int triedDirections = 0;
            char thisDir = dir;
            if (!willMove) {
                newElvPos[e]=i;
            }
            bool didMove = false;
            while (triedDirections < 4 && willMove)
            {
                bool canMove = true;
                for (auto j : moveDir[thisDir]) {
                    std::pair<int,int> t = around[j];
                    if ( elvPos.contains( {e.first + t.first, e.second + t.second}) ) {
                        canMove = false;
                        break;
                    }
                    
                }
                if (canMove) {
                    candidates[{e.first + move[thisDir].first, e.second + move[thisDir].second}].push_back(i);
                    didMove = true;
                    break;
                } else {
                    thisDir = nextDir[thisDir];
                    triedDirections += 1;
                }
            }
            if (! didMove) {
                newElvPos[e] = i;
            }
        }
        if (candidates.size() == 0) {
            moving = false;
        }
        for (auto const &[p, e] : candidates) {
            /* std::cout << "To pos " << p.first << "," << p.second << " we get ";
            for (auto q : e) {
                std::cout << q << " | ";
            }
            std::cout << std::endl; */
            if (e.size() == 1) {
                int id = e[0];
                newElvPos[p] = id;
                elves[id] = p;
            } else {
                for (int id : e) {
                    newElvPos[elves[id]] = id;
                }
            }
        }
        /* for (auto const &[e, i] : newElvPos) {
            std::cout << "Elv " << i << " at pos " << e.first << "," << e.second << std::endl;
        } */
        elvPos = newElvPos;
        dir = nextDir[dir];
        if (itr == 10) {
            int maxX = -elvPos.size()*10, minX=elvPos.size()*10, maxY=-elvPos.size()*10, minY=elvPos.size()*10;
            for (auto const &[e,i] : elvPos) {
                if (e.first < minX) minX=e.first;
                if (e.first > maxX) maxX=e.first;
                if (e.second < minY) minY=e.second;
                if (e.second > maxY) maxY=e.second;
            }
            std::cout << "Answer part A " << (maxX-minX+1)*(maxY-minY+1) - elvPos.size() << std::endl;
        }

    }

    
    std::cout << "Answer part B " << itr << std::endl;    
}