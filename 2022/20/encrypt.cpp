#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <list>
#include <vector>

//std::vector<std::pair<int,long long> >
void shuffleVector(std::vector<std::pair<int,long long> > &encrypt) {
    int curPlace = 0;
    int numVals = encrypt.size();
    
    for (int i = 0; i < numVals ; i++) {

        int order = encrypt[curPlace].first;

        long long val = encrypt[curPlace].second;

        while (order != i) {
            curPlace = curPlace + 1 % numVals;
            order = encrypt[curPlace].first;
            val = encrypt[curPlace].second;
        }
        int newPlace;
        long long newVal = val % (numVals-1);
        if (curPlace + val <= 0) {
            newPlace = ((curPlace + newVal + (curPlace + newVal - numVals)/numVals)%numVals);
        } else if (curPlace + newVal >= numVals){
            newPlace = ((curPlace+newVal+(curPlace + newVal)/numVals)%numVals);
        } else {
            newPlace = ((curPlace+newVal)%numVals);
        }
        

        if (newPlace < 0) {
            newPlace += numVals;
        } 
        encrypt.erase(encrypt.begin()+curPlace);
        encrypt.insert(encrypt.begin()+newPlace, std::make_pair(order,val));
        
    }
    //return encrypt;
}

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;

    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return 0;
    }
    std::vector<std::pair<int,long long> > encrypt;
    int indx = 0;
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            encrypt.push_back(std::make_pair(indx,std::stoi(line)));
            indx++;
        }
    }
    myfile.close();
    shuffleVector(encrypt);
    int numVals = encrypt.size();
    int zeroIndx = 0;
    long long value = encrypt[zeroIndx].second;
    while( value != 0) {
        zeroIndx++;
        value = encrypt[zeroIndx].second;
    }
    long long val1 = encrypt[(zeroIndx+1000)%numVals].second;
    long long val2 = encrypt[(zeroIndx+2000)%numVals].second;
    long long val3 = encrypt[(zeroIndx+3000)%numVals].second;
    std::cout << "Answer part A: " << val1 + val2 + val3 << std::endl;
    int decKey = 811589153;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return 0;
    }
    std::vector<std::pair<int,long long> > encryptB;
    indx = 0;
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            std::cout << "Hej!" << std::endl;
            long long v = std::stoi(line);
            long long newV = v * decKey;
            encryptB.push_back(std::make_pair(indx,newV));
            std::cout << line << " " << std::stoi(line)*decKey << std::endl;
            indx++;
        }
    }
    myfile.close();
    for(auto c : encryptB) {
        std::cout << c.second << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << i << std::endl;
        shuffleVector(encryptB);
        for(auto c : encryptB) {
            std::cout << c.second << " ";
        }
        std::cout << std::endl;
    }
    int zeroIndxB = 0;
    long long valueB = encryptB[zeroIndxB].second;
    while( valueB != 0) {
        zeroIndxB++;
        valueB = encryptB[zeroIndxB].second;
        
    }
    long long valB1 = encryptB[(zeroIndxB+1000)%numVals].second;
    long long valB2 = encryptB[(zeroIndxB+2000)%numVals].second;
    long long valB3 = encryptB[(zeroIndxB+3000)%numVals].second;
    std::cout << "Answer part B: " << valB1 + valB2 + valB3 << std::endl;
    return 0;

}
