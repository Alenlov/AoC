#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

struct star
{
    long x,y,z,t;

    long dist_to(star* other)
    {
        return abs(x - other->x) + abs(y - other->y) + abs(z - other->z) + abs(t - other->t);
    }
};


std::pair<int,int> operator+(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
    return {lhs.first+rhs.first,lhs.second+rhs.second};
}

std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos && (indx < line.length()))
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
    std::list<star*> stars;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> coords = splitLine(line,",");
            star* s = new star;
            s->x = std::stol(coords[0]);
            s->y = std::stol(coords[1]);
            s->z = std::stol(coords[2]);
            s->t = std::stol(coords[3]);
            stars.push_back(s);
        }
    }
    myfile.close();
    
    long ansA{0};
    while(stars.size() > 0)
    {
        ++ansA;
        std::list<star*> constellation;
        constellation.push_front(stars.front());
        stars.pop_front();
        auto it = stars.begin();
        while (it != stars.end())
        {
            bool found{false};
            for (auto s : constellation)
            {
                if ((*it)->dist_to(s) <= 3)
                {
                    constellation.push_back(*it);
                    stars.erase(it);
                    it = stars.begin();
                    found = true;
                    break;
                }
            }
            if (!found) {it++;}
            
        }
        std::cout << "Constellation consists of: " << std::endl;
        for (auto &s : constellation)
        {
            std::cout << s->x << "," << s->y << "," << s->z << "," << s->t << std::endl;
        }
    }

    std::cout << "Answer part A: " << ansA << std::endl;
}