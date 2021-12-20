#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<int, std::pair<int, int>>> weapons = {{8,{4,0}}, {10,{5,0}}, {25,{6,0}}, {40,{7,0}}, {74,{8,0}}};
std::vector<std::pair<int, std::pair<int, int>>> armors = {{0,{0,0}}, {13,{0,1}}, {31,{0,2}}, {53,{0,3}}, {75,{0,4}}, {102,{0,5}}};
std::vector<std::pair<int, std::pair<int, int>>> rings = {{0,{0,0}}, {0,{0,0}}, {25,{1,0}}, {50,{2,0}}, {100,{3,0}}, {20,{0,1}}, {40,{0,2}}, {80,{0,3}}};

int main(){
    int boss_arm = 2;
    int boss_dmg = 8;
    std::vector<int> costsWin;
    std::vector<int> costsLose;
    for(std::pair<int, std::pair<int,int>> const& wpn : weapons){
        for(std::pair<int, std::pair<int,int>> const& arm : armors){
            int ringInd = 0;
            for(std::pair<int, std::pair<int,int>> const& ringA : rings){
                for(int ringBind = ringInd + 1; ringBind < rings.size(); ringBind++){
                    std::pair<int, std::pair<int,int>> ringB = rings[ringBind];
                    int player_dmg = wpn.second.first + arm.second.first + ringA.second.first + ringB.second.first;
                    int player_arm = wpn.second.second + arm.second.second + ringA.second.second + ringB.second.second;
                    int diffPlayer = player_dmg - boss_arm;
                    if(diffPlayer < 1){
                        diffPlayer = 1;
                    }
                    int diffBoss = boss_dmg - player_arm;
                    if(diffBoss < 1){
                        diffBoss = 1;
                    }
                    if(diffBoss <= diffPlayer){
                        costsWin.push_back(wpn.first + arm.first + ringA.first + ringB.first);
                    } else {
                        costsLose.push_back(wpn.first + arm.first + ringA.first + ringB.first);
                    }
                }
            }
        }
    }
    int minCost = 74 + 102 + 100 + 80;
    for(int const& c : costsWin){
        if(c < minCost){
            minCost = c;
        }
    }
    std::cout << "Answer part A: The minimum cost for winning is " << minCost << std::endl;
    int maxCost = 0;
    for(int const& c : costsLose){
        if(c > maxCost){
            maxCost = c;
        }
    }
    std::cout << "Answer part B: The maximum cost for losing is " << maxCost << std::endl;
    return 0;
}