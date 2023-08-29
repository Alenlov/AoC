#ifndef MONKEY_H
#define MONKEY_H

#include <deque>
#include <string>
#include <tuple>
#include <vector>

class monkey
{
private:
    std::deque<long long> items;
    std::vector<std::string> operations;
    int tM;
    int fM;
    int divBy;
    int inspected;
    int worryRed;
public:
    monkey(char prob);
    ~monkey();

    void addItem(long long worry);

    std::deque<std::tuple<int,long long>> processItems();

    void setTM(int tM);

    void setFM(int fM);

    void setOperation(std::vector<std::string> operations);

    void setDivBy(int divBy);

    long long getInspected();

    std::string getItems();

    void setWorryRed(int worryRed);

};






#endif