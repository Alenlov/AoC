#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <algorithm>


int main(int argc, char const *argv[])
{
    int input;
    if (argc > 1)
    {
        input = std::stoi(argv[1]);
    }
    else
    {
        return -1;
    }
    int ansA{0};
    std::list<int> spinLock{0};
    auto it = spinLock.begin();
    for (int v = 1; v < 2018; v++)
    {
        for (int step = 0; step < input; step++)
        {
            ++it;
            if (it == spinLock.end()) it = spinLock.begin();
        }
        ++it;
        spinLock.insert(it, v);
        --it;
        if (v == 2017)
        {
            ++it;
            ansA = *it;
            --it;
        }
    }
    std::cout << "Answer part A: " << ansA << std::endl;
    int totSpins{50000000};
    int after0{0};
    int curPos{0};
    for (int v = 1; v<totSpins;v++)
    {
        curPos = (curPos+input)%v;
        if (curPos==0)
        {
            after0 = v;
            //std::cout << v << std::endl;
        }
        curPos += 1;
    }
    std::cout << "Answer part B: " << after0 << std::endl;
}