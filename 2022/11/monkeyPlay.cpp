#include "monkey.h"
#include <deque>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>

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

bool mySort (long long i,long long j) { return (i>j); }

int main(int argc, char* argv[]){
    std::ifstream myfile;
    std::string line;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "NEED A FILE" << std::endl;
        return 0;
    }
    std::map<int, monkey*> monkeys;
    int curMonkey, divider = 1;
    if(myfile.is_open()) {
        while(getline(myfile,line)){
            if(line.length() > 0) {
                std::vector<std::string> lineSplit = splitLine(line);
                if(lineSplit[0] == "Monkey") {
                    curMonkey = std::stoi(lineSplit[1].substr(0,1));
                    monkeys[curMonkey] = new monkey();
                } else if (lineSplit[0] == "Operation:") {
                    monkeys[curMonkey]->setOperation( {lineSplit.begin() + 3, lineSplit.end()} );
                } else if (lineSplit[0] == "Test:") {
                    monkeys[curMonkey]->setDivBy(std::stoi(lineSplit[3]));
                    divider *= std::stoi(lineSplit[3]);
                } else if (lineSplit[0] == "If") {
                    if(lineSplit[1] == "true:") {
                        monkeys[curMonkey]->setTM(std::stoi(lineSplit[5]));
                    } else if (lineSplit[1] == "false:") {
                        monkeys[curMonkey]->setFM(std::stoi(lineSplit[5]));
                    } else {
                        std::cout << " Hamnade i if men inte true eller false " << line << std::endl;
                    }
                } else if (lineSplit[0] == "Starting") {
                    std::vector<std::string> split2 = splitLine(line, ": ");
                    std::vector<std::string> split3 = splitLine(split2[1],", ");
                    for(std::string s : split3) {
                        monkeys[curMonkey]->addItem(std::stoi(s));
                    }
                } else {
                    std::cout << " Hamnade ingenstans :" << line << ":" << std::endl;
                }
            }
        }

    }

    for(auto const& [k,v] : monkeys) {
        v->setWorryRed(divider);
    }

    myfile.close();

    for(int rounds = 0; rounds < 10000; rounds++ ){
        for(auto const& [k,v] : monkeys) {
            std::deque<std::tuple<int,long long>> destinations = v->processItems();
            while(!destinations.empty()) {
                std::tuple<int,long long> item = destinations.front();
                destinations.pop_front();
                monkeys[std::get<0>(item)]->addItem(std::get<1>(item));
            }
        }
        std::cout << "After round " << rounds + 1 << std::endl;
        for (auto const& [k, v] : monkeys) {
            std::cout << "Monkey " << k << " has " << v->getItems() << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<long long> itemProcessed;
    for (auto const& [k,v] : monkeys) {
        itemProcessed.push_back(v->getInspected());
    }
    std::sort(itemProcessed.begin(), itemProcessed.end(), mySort);
    unsigned long long prod = itemProcessed[0] * itemProcessed[1];
    std::cout << "Most " << itemProcessed[0] << " second " << itemProcessed[1] << " product " << prod << std::endl;

    /* std::deque<std::tuple<int,int>> destinations = monkeys[0]->processItems();

    for(std::tuple<int,int> d : destinations) {
        std::cout << "Worry " << std::get<1>(d) << " to monkey " << std::get<0>(d) << std::endl;
    }
    std::cout << "Monkey 0 inspected " << monkeys[0]->getInspected() << std::endl; */
}