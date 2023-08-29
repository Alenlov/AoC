#include "monkey.h"
#include <deque>
#include <string>
#include <tuple>
#include <vector>

void monkey::addItem(long long worry)
{
    items.push_back(worry);
}

std::deque<std::tuple<int,long long>> monkey::processItems()
{
    std::deque<std::tuple<int,long long>> itemDest;
    while(! items.empty() ) {
        long long worry = items.front();
        items.pop_front();
        this->inspected += 1;
        // Perform operation
        long long rhs, lhs, newWorry;
        if (operations[0] == "old") {
            lhs = worry;
        } else {
            lhs = std::stoi(operations[0]);
        }
        if (operations[2] == "old") {
            rhs = worry;
        } else {
            rhs = std::stoi(operations[2]);
        }
        if (operations[1] == "+") {
            newWorry = rhs + lhs;
        } else if (operations[1] == "*") {
            newWorry = rhs * lhs;
        }
        // divide by 3
        newWorry %= this->worryRed;

        // check
        if (newWorry % this->divBy == 0) {
            itemDest.push_back(std::make_tuple(tM, newWorry));
        } else {
            itemDest.push_back(std::make_tuple(fM, newWorry));
        }

    }

    return itemDest;
}

void monkey::setTM(int tM)
{
    this->tM = tM;
}

void monkey::setFM(int fM)
{
    this->fM = fM;
}

void monkey::setOperation(std::vector<std::string> operations)
{
    this->operations = operations;
}

void monkey::setDivBy(int divBy)
{
    this->divBy = divBy;
}

long long monkey::getInspected()
{
    return this->inspected;
}

std::string monkey::getItems()
{
    std::string out = "";
    for(int i : items) {
        out += std::to_string(i);
        out += " ";
    }
    return out;
}

void monkey::setWorryRed(int worryRed)
{
    this->worryRed = worryRed;
}

monkey::monkey()
{
}

monkey::~monkey()
{
}