#include <iostream>
#include <fstream>
#include <string>
#include <vector>
/*




*/


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
    std::vector<int> inst, instB;
    if (myfile.is_open())
    {
        while(getline(myfile,line)) {
            inst.push_back(std::stoi(line));
        }
    }
    instB = inst;
    myfile.close();
    int head{0}, steps{0}, headB{0}, stepsB{0};
    while (head < inst.size()) {
        
        int newHead = head + inst[head];

        inst[head]++;
        steps++;
        head = newHead;

    }
    while (headB < instB.size()) {
        int newHead = headB + instB[headB];
        if (instB[headB] > 2) {
            instB[headB]--;
        } else {
            instB[headB]++;
        }
        stepsB++;

        headB = newHead;
    }
    std::cout << "Answer part A: " << steps << std::endl;
    std::cout << "Answer part B: " << stepsB << std::endl;
    
}