#include <iostream>
#include <string>
#include <set>
#include <math.h>
#include <map>
#include <algorithm>
#include <utility>

std::map<int, std::set<int>> factorsOfNumber;

std::pair<int, int> sumOfFactors(int startNumber){
    int number = startNumber;
    std::set<int> factors = {1,number};

    int factor = 2;
    int maxFactor = ceil(sqrt(number));
    while( factor <= maxFactor){
        if((number % factor) == 0){
            int divisor = number/factor;
            factors.insert(factor);
            if(factorsOfNumber.find(divisor) != factorsOfNumber.end()){
                std::set<int> newFactors;
                std::merge(factorsOfNumber[divisor].begin(), factorsOfNumber[divisor].end(),
                            factors.begin(), factors.end(),
                            std::inserter(newFactors, newFactors.begin()));
                factors = newFactors;
            }
            
            maxFactor = ceil(sqrt(divisor));
        }
        factor += 1;
    }
    factorsOfNumber[startNumber] = factors;
    int sum = 0;
    int sum50 = 0;
    for(int const& factor : factors){
        sum += 10*factor;
        if (factor*50 >= startNumber ){
            sum50 += factor*11;
        }
    }
    return std::make_pair(sum, sum50);
}

int main(int argc, char* argv[]){
    int presents = std::stoi(argv[1]);
    if(argc == 2){
        int house = 1;
        // house = 498960;
        std::pair<int, int> numPres = sumOfFactors(house);
        bool running = true;
        int houseA = 0;
        int houseB = 0;
        while(running){
            if((numPres.first > presents) && (houseA == 0)){
                houseA = house;
                std::cout << "Answer part A: the first house with at least " << presents << " presents is number " << houseA << std::endl;
            }
            if((numPres.second > presents) && (houseB == 0)){
                houseB = house;
                running = false;
            }
            house += 1;
            numPres = sumOfFactors(house);
            
            
        }
        std::cout << "Answer part B: the first house with at least " << presents << " presents is number " << houseB << std::endl;  

    } else {
        int house = std::stoi(argv[2]);
        std::pair<int, int> numPres;
        for(int i = 1; i <= house ; i ++){
            numPres = sumOfFactors(i);
            std::cout << "House " << i << " got " << numPres.first << " presents in A and " << numPres.second << " presents in B." << std::endl;
        }
         
        
    }
      

    return 0;
}