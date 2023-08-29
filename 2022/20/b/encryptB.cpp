#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>

struct node
{
    node *pre;
    node *nex;
    int order;
    long long value;
};

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    node *head = NULL;
    node *zero = NULL;
    node *prev = NULL;
    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return 0;
    }
    int order = 0;
    long long decKey = 811589153;
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            long long value = std::stoll(line) * decKey;
            node *toInsert = new node;
            toInsert->order = order;
            toInsert->value = value;
            toInsert->pre = prev;
            std::cout << value << " ";
            if (prev != NULL) {
                prev->nex = toInsert;
            }
            if (head == NULL) {
                head = toInsert;
            }
            if (value == 0) {
                zero = toInsert;
            }
            order++;
            prev = toInsert;
        }
        std::cout << std::endl;
    }
    head->pre = prev;
    prev->nex = head;
    myfile.close();
    prev = head;
    for (int i = 0; i < order; i++){
        std::cout << prev->value << " ";
        prev = prev->nex;
    }
    std::cout << std::endl;

    for (int iter = 0; iter < 10; iter++) {
        std::cout << "iteration :" << iter << std::endl;
        for (int o = 0; o < order; o++) {
            while (head->order != o) {
                //std::cout << "Have order " << head->order << " want " << o << std::endl;
                head = head->nex;
            }

            //std::cout << head->order << std::endl;
            //std::cout << head->nex->order << std::endl;
            node *toRemove = head;
            node *previous = head->pre;
            node *next = head->nex;
            next->pre = toRemove->pre;
            previous->nex = toRemove->nex;
            long long val = (toRemove->value) % (order - 1);
            if (val < 0) {
                val += order-1;
            }
            for (int i = 0; i < val; i ++) {
                previous = previous->nex;
            }
            next = previous->nex;
            toRemove->nex = next;
            toRemove->pre = previous;
            next->pre = toRemove;
            previous->nex = toRemove;
            //std::cout << head->order << std::endl;
            //std::cout << head->nex->order << std::endl;
            

        }
    for (int i = 0; i < order; i++){
        std::cout << head->value << " ";
        head = head->nex;
    }
    std::cout << std::endl;
    }
    long long ansB = 0;
    for(int i = 0; i < 3; i ++) {
        for (int j = 0; j < 1000; j ++) {
            zero = zero->nex;
        }
        std::cout << "Value " << i+1 << " is " << zero->value << std::endl; 
        ansB += zero->value;
    }
    std::cout << "Answer part B " << ansB << std::endl;
}