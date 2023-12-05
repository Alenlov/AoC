#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <tuple>
#include <map>

struct proc
{
    char type;
    std::pair<std::tuple<int,char,char>,std::tuple<int,char,char>> rule;
};

int main(int argc, char const *argv[])
{
    
    long steps{12134527};
    char state{'A'};


    proc A;
    A.type = 'A';
    A.rule = {{1, 'r', 'B'},{0,'l','C'}};
    proc B;
    B.type = 'B';
    B.rule = {{1, 'l', 'A'},{1,'r','C'}};
    proc C;
    C.type = 'C';
    C.rule = {{1, 'r', 'A'},{0,'l','D'}};
    proc D;
    D.type = 'D';
    D.rule = {{1, 'l', 'E'},{1,'l','C'}};
    proc E;
    E.type = 'E';
    E.rule = {{1, 'r', 'F'},{1,'r','A'}};
    proc F;
    F.type = 'F';
    F.rule = {{1, 'r', 'A'},{1,'r','E'}};

    std::map<char, proc> states{ {'A',A}, {'B',B}, {'C',C}, {'D',D}, {'E',E}, {'F',F} };

    std::unordered_set<long> ones;
    long head{0};
    
    for(long s = 0; s < steps; s++)
    {
        std::tuple<int,char,char> r;
        if (ones.contains(head))
        {
            r = states[state].rule.second;
        }
        else
        {
            r = states[state].rule.first;
        }
        if (std::get<0>(r) == 1)
        {
            if(!ones.contains(head)) ones.insert(head);
        }
        else
        {
            ones.erase(head);
        }
        if (std::get<1>(r) == 'l')
        {
            --head;
        }
        else
        {
            ++head;
        }
        state = std::get<2>(r);
    }
    
    
    std::cout << "Answer part A: " << ones.size() << std::endl;
}