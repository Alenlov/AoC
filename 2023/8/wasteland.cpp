#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <map>

struct wasteland
{
    std::map<char, std::string> to;
};


long gcd(long lhs, long rhs)
{
    while (rhs != 0)
    {
        long temp = rhs;
        rhs = lhs % rhs;
        lhs = temp;
    }
    return lhs;
}

long lcm(long lhs, long rhs)
{
    return (lhs*rhs)/gcd(lhs,rhs);
}

int main(int argc, char const *argv[])
{
    const std::regex mazeMatch("([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)");
    std::smatch m;
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
    std::string directions;
    std::map<std::string, wasteland> wastelandMap;
    std::vector<std::string> startB;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            if (std::regex_match(line, m, mazeMatch))
            {
                wasteland w;
                w.to['L'] = m[2];
                w.to['R'] = m[3];
                wastelandMap[m[1]] = w;
                if (std::string(m[1])[2] == 'A') startB.push_back(m[1]);
            }
            else if (line.length() > 0)
            {
                directions = line;
            }
            
        }
    }
    myfile.close();

    std::string cur{"AAA"}, end{"ZZZ"};
    bool foundEnd{false};
    long ansA{0};
    while (!foundEnd)
    {
        for (char d : directions)
        {
            cur = wastelandMap[cur].to[d];
            ++ansA;
            if (cur == end)
            {
                foundEnd = true;
                break;
            }
        }
    }
    
    std::cout << "Answer part A: " << ansA << std::endl;

    std::map<std::string, long> startToEnd;
    for( std::string start : startB)
    {
        long steps{0};
        foundEnd = false;
        cur = start;
        while(!foundEnd)
        {
            for (char d : directions)
            {
                cur = wastelandMap[cur].to[d];
                ++steps;
                if (cur[2] == 'Z')
                {
                    if (startToEnd[start] == 0)
                    {
                        startToEnd[start] = steps;
                    }
                    else
                    {
                        foundEnd = true;
                        break;
                    }
                }
                
            }
        }
    }

    long ansB{1};
    for (auto const [w, s] : startToEnd)
    {
        ansB = lcm(ansB, s);
    }
    std::cout << "Answer part B: " << ansB << std::endl;
}