#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <tuple>
#include <limits>

struct magic{
    int cost =0;
    int dmg =0;
    int heal =0;
    int arm =0;
    int gainMana =0;
    int effectDur =0;
};

struct player{
    int hp =0;
    int mana =0;
    int manaSpent =0;
};

struct boss{
    int hp =0;
    int dmg =0;
};

std::map<std::string, magic> magics;
int minManaUsed = std::numeric_limits<int>::max();
void setMagics(){
    magic MM;
    MM.cost = 53;
    MM.dmg = 4;
    magics["MagicMissile"] = MM;
    magic D;
    D.cost = 73;
    D.dmg = 2;
    D.heal = 2;
    magics["Drain"] = D;
    magic S;
    S.cost = 113;
    S.arm = 7;
    S.effectDur = 6;
    magics["Shield"] = S;
    magic P;
    P.cost = 173;
    P.effectDur = 6;
    P.dmg = 3;
    magics["Poison"] = P;
    magic R;
    R.cost = 229;
    R.effectDur = 5;
    R.gainMana = 101;
    magics["Recharge"] = R;
}

bool hardMode = false;

std::tuple<player, boss, std::map<std::string, int>> oneTurn(player P, boss B, std::map<std::string, int> activeEffects, std::string magicToUse){
    // PLayers turn
    std::map<std::string, int> effectsAfterPlayer;
    // std::cout << "----------------" << std::endl;
    if(hardMode){
        P.hp -= 1;
    }
    if(P.hp < 1){
        return std::make_tuple(P, B, activeEffects);
    }
    for(auto const& [name, turns] : activeEffects){
        // std::cout << "Effect " << name << " has " << turns << " left" << std::endl;
        // std::cout << "Applying " << name << " hp before " << B.hp;
        B.hp -= magics[name].dmg;
        // std::cout << " after " << B.hp << std::endl;
        P.mana += magics[name].gainMana;
        if(turns > 0){
            effectsAfterPlayer[name] = turns - 1;
        }
    }
    if (B.hp < 1){
        return std::make_tuple(P, B, effectsAfterPlayer);
    }
    // std::cout << std::endl;
    // std::cout << "Using " << magicToUse << std::endl;
    P.mana -= magics[magicToUse].cost;
    P.manaSpent += magics[magicToUse].cost;
    if(P.mana < 0) {
        // std::cout << "Out of mana" << std::endl;
        P.hp = 0;
        B.hp = 1;
        return std::make_tuple(P,B,effectsAfterPlayer);
    }
    if(magics[magicToUse].effectDur > 0){
        effectsAfterPlayer[magicToUse] = magics[magicToUse].effectDur - 1;
        // std::cout << "Added effect " << magicToUse << " with duration " << magics[magicToUse].effectDur << std::endl;
    } else {
        B.hp -= magics[magicToUse].dmg;
        P.hp += magics[magicToUse].heal;
    }
    
    // Boss turn
    std::map<std::string, int> effectsAfterBoss;

    int playerArm = 0;
    for(auto const& [name, turns] : effectsAfterPlayer){
        // std::cout << "Effect " << name << " has " << turns << " left" << std::endl;
        B.hp -= magics[name].dmg;
        P.mana += magics[name].gainMana;
        playerArm += magics[name].arm;
        if(turns > 0){
            // std::cout << "Effect " << name << " is here for next turn" << std::endl;
            effectsAfterBoss[name] = turns - 1;
        }
    }
    // std::cout << "Player armor is " << playerArm << std::endl;
    P.hp -= (B.dmg - playerArm);
    return std::make_tuple(P, B, effectsAfterBoss);
}

std::pair<int, std::string> leastManaForWin( player P, boss B, std::map<std::string, int> activeEffects  ){
    // Choose magic
    if (P.manaSpent > minManaUsed)
    {
        return std::make_pair(-1, "");
    }
    
    std::map<std::string, std::pair<int, std::string>> manaUsedWithMagic;
    for(auto const& [magicString, M] : magics){
        bool override = false;
        if(activeEffects.find(magicString) != activeEffects.end()){
            if (activeEffects[magicString] == 0) {
                override = true;
            }
        }
        if((activeEffects.find(magicString) == activeEffects.end() || override)){
            // std::cout << "Trying to win with " << magicString << std::endl;
            // One turn
            auto [newP, newB, newAct] = oneTurn(P, B, activeEffects, magicString);
            // std::cout << newP.hp << " " << newB.hp << " after " << magicString << std::endl;
            // Check if win
            if (newB.hp < 1){
                // std::cout << "Won using " << magicString << " spent " << newP.manaSpent << " mana" <<  std::endl;
                manaUsedWithMagic[magicString] = std::make_pair(newP.manaSpent, "");
                if(newP.manaSpent < minManaUsed){
                    minManaUsed = newP.manaSpent;
                }
            } else if (newP.hp < 1){
                // std::cout << "Fail" << std::endl;
                manaUsedWithMagic[magicString] = std::make_pair(-1, "");
            } else {
                manaUsedWithMagic[magicString] = leastManaForWin(newP, newB, newAct);
            }
        }
    }
    
    int minMana = std::numeric_limits<int>::max();
    std::string minMagic = "";
    for( auto const& [name, val] : manaUsedWithMagic){
        if ((val.first > 0) && (minMana > val.first)){
            minMana = val.first;
            minMagic = name;
        }
    }
    // std::cout << "Won using down here " << minMagic << std::endl;
    return std::make_pair(minMana,minMagic+" "+manaUsedWithMagic[minMagic].second);

}

int main(int argc, char* argv[]){
    if (argc > 1){
        hardMode = true;
    }
    setMagics();
    player P;
    P.hp = 50;
    P.mana = 500;
    boss B;
    B.hp = 71;
    B.dmg = 10;
    std::map<std::string, int> activeEffects;
    std::pair<int,std::string> leastMana = leastManaForWin(P, B, activeEffects);
    std::cout << "Answer part A: The least amount of mana used to win is " << leastMana.first << std::endl;
    std::cout << "Using " << leastMana.second << std::endl;

    return 0;
}