#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

int diff = int('a') - int('A');

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
    if (myfile.is_open())
    {
        getline(myfile,line);
    }
    myfile.close();
    std::cout << line.size() << std::endl;
    bool react{true};
    while(react)
    {
        react = false;
        std::string newString{""};
        for(int i = 0; i < line.size()-1;)
        {
            char c1{line[i]}, c2{line[i+1]};
            if (abs(int(c1) - int(c2)) == diff)
            {
                react = true;
                i += 2;
                if(i == line.size()-1)
                {
                    newString += line[i];
                }
            }
            else
            {
                newString += c1;
                ++i;
                if(i == line.size()-1)
                {
                    newString += c2;
                }
            }
            //std::cout << newString << std::endl;

        }
        line = newString;
    }
    std::cout << "Answer part A: " <<  line.size() << std::endl;
    int minLen = line.size();
    for(int c = int('a'); c <= int('z'); c++)
    {
        std::string lineB;
        for (char lc : line)
        {
            if (!((int(lc) == c) || (int(lc) == (c - diff))))
            {
                lineB += lc;
            }
        }
        //std::cout << c << ":" << lineB << std::endl;
        react = true;
        while(react)
        {
            react = false;
            std::string newString{""};
            for(int i = 0; i < lineB.size()-1;)
            {
                char c1{lineB[i]}, c2{lineB[i+1]};
                if (abs(int(c1) - int(c2)) == diff)
                {
                    react = true;
                    i += 2;
                    if(i == lineB.size()-1)
                    {
                        newString += lineB[i];
                    }
                }
                else
                {
                    newString += c1;
                    ++i;
                    if(i == lineB.size()-1)
                    {
                        newString += c2;
                    }
                }
                //std::cout << newString << std::endl;

            }
            lineB = newString;
        }
        //std::cout << lineB << std::endl;
        if (lineB.size() < minLen)
        {
            minLen = lineB.size();
        }
    }
    std::cout << "Answer part B: " << minLen << std::endl;
}