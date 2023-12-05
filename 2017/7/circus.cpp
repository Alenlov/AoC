#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
/*




*/


struct circus
{
    std::string name;
    std::string parent;
    std::vector<std::string> children;
    int wgt;
    std::map<std::string, int> balance;
};

int calcWeight(circus& c, std::map<std::string, circus>& d) {
    if (c.children.size() == 0) return c.wgt;

    for (std::string s : c.children) {
        c.balance[s] = calcWeight(d[s], d);
    }

    int totSum = c.wgt;
    for (auto [s, w] : c.balance) totSum += w;
    return totSum;
}


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
    std::map<std::string, circus> discs;
    if (myfile.is_open())
    {
        while(getline(myfile,line)) {
            std::vector<std::string> split1 = splitLine(line, " -> ");
            std::vector<std::string> split = splitLine(split1[0], " ");
            std::string name = split[0];
            int wgt = std::stoi( split[1].substr(1,split[1].length()-2) );
            std::vector<std::string> children;
            if (split1.size() > 1) {
                split = splitLine(split1[1], ", ");
                for (int i = 0; i < split.size(); i++) {
                    children.push_back(split[i]);
                }
            }
            circus c;
            c.name = name;
            c.wgt = wgt;
            c.children = children;
            discs[name] = c;
        }
    }

    
    
    for (auto [k,v] : discs) {
        if (v.children.size() > 0) {
            for (std::string s : v.children) {
                discs[s].parent = k;
            }
        }
    }

    /* for (auto [k,v] : discs) {
        std::cout << k << " : " << v.wgt << " ";
        for(auto s : v.children) {
            std::cout << s << " ";
        }
        std::cout << " parent = " << v.parent << std::endl;
    } */
    std::string head;
    for (auto [k, v] : discs) {
        if (v.parent == "") head = k;
    }
    std::cout << "Answer part A: " << head << std::endl;

    calcWeight(discs[head], discs);
    int diff{0};
    bool diffFound{false};
    while(! diffFound) {
        std::map<int,int> weights;
        for (auto [s, w] : discs[head].balance) {
            if (weights.contains(w)) {
                weights[w] += 1;
            } else {
                weights[w] = 1;
            }
        }
        if (weights.size() > 1) {
            int correctWeight, wrongWeight;
            for (auto [w, id] : weights) {
                if (id > 1) correctWeight = w;
                if (id == 1) wrongWeight = w;
            }
            diff = correctWeight - wrongWeight;
            for (auto [s, w] : discs[head].balance) {
                if (w == wrongWeight) {
                    head = s;
                }
            }
        } else {
            diffFound = true;
        }

    }

    
    std::cout << "Answer part B: " << discs[head].wgt + diff << std::endl;
}