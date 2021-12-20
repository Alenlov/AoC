#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]){
    int presents = std::stoi(argv[1]);
    int size = presents/10;
    std::vector<long long> presentsToHouse(size+1,0);
    for(int i = 1; i <= size; i++){
        for(int j = i; j <= size; j += i){
            presentsToHouse[j] += i * 10;
        }
    }
    int indx = 1;
    while(true){
        if(presentsToHouse[indx] > presents){
            std::cout << "Answer part A: The first house to get " << presents << " is house " << indx << std::endl;
            break;
        }
        indx += 1;
    }
    std::vector<long long> presentsToHouse50(size+1,0);
    for(int i = 1; i <= size; i++){
        for(int j = i; (j <= size) && (j <= i*50); j += i){
            presentsToHouse50[j] += i * 11;
        }
    }
    indx = 1;
    while(true){
        if(presentsToHouse50[indx] > presents){
            std::cout << "Answer part B: The first house to get " << presents << " is house " << indx << std::endl;
            break;
        }
        indx += 1;
    }
    return 0;
}