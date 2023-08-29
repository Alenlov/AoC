#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <list>
#include <vector>
#include <map>
#include <regex>

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

struct monkey
{
    std::string name;
    long long number;
    bool numberSet = false;
    std::string lhs;
    std::string rhs;
    std::string op;
};



void yell(monkey *m, std::map<std::string,monkey*> monkeys, bool b = false) {
    if (b && m->name == "root") {
        return;
    }
    if (b && m->name == "humn") {
        return;
    }
    if (m->numberSet) {
        return;
    }
    long long lhs, rhs;
    if(!monkeys[m->lhs]->numberSet | !monkeys[m->rhs]->numberSet) {
        return;
    }
    lhs = monkeys[m->lhs]->number;
    rhs = monkeys[m->rhs]->number;
    if (m->op == "-") {
        m->number = lhs - rhs;
        m->numberSet = true;
    } else if (m->op == "+") {
        m->number = lhs+rhs;
        m->numberSet = true;
    } else if (m->op == "*") {
        m->number = lhs*rhs;
        m->numberSet = true;
    } else if (m->op == "/") {
        m->number = lhs/rhs;
        m->numberSet = true;
    }
}

std::string makeEqual(monkey *m, std::map<std::string,monkey*> monkeys) {
    std::string nextMonkey;
    if (monkeys[m->lhs]->numberSet) {
        nextMonkey = m->rhs;
        long long lhs = monkeys[m->lhs]->number;
        if (m->op == "-") {
            monkeys[nextMonkey]->number = lhs - m->number;
        } else if (m->op == "+") {
            monkeys[nextMonkey]->number =  m->number - lhs;
        } else if (m->op == "*") {
            monkeys[nextMonkey]->number = m->number / lhs;
        } else if (m->op == "/") {
            monkeys[nextMonkey]->number = lhs / m->number;
        }
    } else if (monkeys[m->rhs]->numberSet) {
        nextMonkey = m->lhs;
        long long rhs = monkeys[m->rhs]->number;
        if (m->op == "-") {
            monkeys[nextMonkey]->number = m->number + rhs;
        } else if (m->op == "+") {
            monkeys[nextMonkey]->number =  m->number - rhs;
        } else if (m->op == "*") {
            monkeys[nextMonkey]->number = m->number / rhs;
        } else if (m->op == "/") {
            monkeys[nextMonkey]->number = m->number * rhs;
        }
    } else {
        std::cout << "Both are missing!" << std::endl;
    }
    return nextMonkey;
}

int main(int argc, char const *argv[])
{
    std::map<std::string, monkey*> monkeys;
    std::map<std::string, monkey*> monkeysB;
    std::ifstream myfile;
    std::string line;

    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return 0;
    }
    
    std::regex cmd1("([a-z]{4}): (\\d+)");
    std::regex cmd2("([a-z]{4}): ([a-z]{4}) ([+\\-*/]) ([a-z]{4})");
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            monkey *m = new monkey;
            std::smatch matches;
            if (std::regex_match(line, matches, cmd1)) {
                m->name = matches[1];
                m->number = std::stoll(matches[2]);
                m->numberSet = true;
            } else if (std::regex_match(line, matches, cmd2)) {
                m->name = matches[1];
                m->lhs = matches[2];
                m->rhs = matches[4];
                m->op = matches[3];
            }
            monkeys[matches[1]] = m;
        }
    }
    myfile.close();

    while(! monkeys["root"]->numberSet) {
        for(auto &[n,m] : monkeys) {
            yell(m, monkeys);
        }
    }
    std::cout << monkeys["root"]->number << std::endl;

    if (argc > 1) {
        myfile.open(argv[1]);
    } else {
        std::cout << "Need a file!" << std::endl;
        return 0;
    }
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            monkey *m = new monkey;
            std::smatch matches;
            if (std::regex_match(line, matches, cmd1)) {
                m->name = matches[1];
                m->number = std::stoll(matches[2]);
                if (matches[1] != "humn") m->numberSet = true;
            } else if (std::regex_match(line, matches, cmd2)) {
                m->name = matches[1];
                m->lhs = matches[2];
                m->rhs = matches[4];
                m->op = matches[3];
            }
            monkeysB[matches[1]] = m;
        }
    }
    myfile.close();
    int numSet = 0;
    int prevNumSet = -1;
    while(numSet!=prevNumSet) {
        prevNumSet = numSet;
        numSet = 0;
        for(auto &[n,m] : monkeysB) {
            yell(m, monkeysB, true);
            if(m->numberSet) {
                numSet += 1;
            }
        }
    }
    monkey *root = monkeysB["root"];
    std::string nextMonkey = "";
    if (monkeysB[root->lhs]->numberSet){
        nextMonkey = root->rhs;
        monkeysB[nextMonkey]->number = monkeysB[root->lhs]->number;
    } else {
        nextMonkey = root->lhs;
        monkeysB[nextMonkey]->number = monkeysB[root->rhs]->number;
    }
    
    while (nextMonkey != "humn") {
        nextMonkey = makeEqual(monkeysB[nextMonkey], monkeysB);
    }
    std::cout << "We should yell " << monkeysB["humn"]->number << std::endl;

}