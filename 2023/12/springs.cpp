#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <deque>
#include <map>
#include <unordered_map>

std::unordered_map<std::string, long> cacheVals;

std::map<std::pair<int,int>, long> pascal;

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





long binom(long i, long j)
{
    //std::cout << i << " over " << j << std::endl;
    if (i < j) return 0;
    if (pascal.contains({i,j})) return pascal[{i,j}];
    else if (pascal.contains({i,i-j}))
    {
        return pascal[{i,i-j}];
    }
    

    if (j == 0 || j == i)
    {
        pascal[{i,j}] = 1;
        pascal[{i,j-i}] = 1;
        return 1;
    }
    else
    {
        pascal[{i,j}] = binom(i-1,j) + binom(i-1,j-1);
        pascal[{i,i-j}] = pascal[{i,j}];
        return pascal[{i,j}];
    }
}



long calcCombinations(std::string line)
{
    //std::cout << line;
    if (cacheVals.contains(line))
    {
        //std::cout << " fanns! " << cacheVals[line] << std::endl;;
        return cacheVals[line];
    }
    //std::cout << std::endl;

    std::vector<std::string> split = splitLine(line, " ");

    if (split.size() == 0)
    { 
        //std::cout << "Okej inget kvar!" << std::endl;
        cacheVals[line] = 1;
        return 1;
    }
    else if (split.size() == 1)
    {
        if (line[0] == ' ')
        {
            //std::cout << "Fel finns tal kvar!" << std::endl;
            cacheVals[line] = 0;
            return 0;
        }
        else
        {
            if (line.find('#') != std::string::npos)
            {
                //std::cout << "Fel, finns # kvar" << std::endl;
                cacheVals[line] = 0;
                return 0;
            }
            else
            {
                //std::cout << "Okej, inget # kvar" << std::endl;
                cacheVals[line] = 1;
                return 1;
            }
        }
        
    }
    else
    {
        long numCombs{0};
        std::string combs{split[0]}, numbs{split[1]};
        std::size_t firstQ = combs.find('?');
        std::size_t firstH = combs.find('#');
        std::size_t firstIndx;
        std::size_t firstC = numbs.find(',');
        long nextDmg = std::stol(numbs.substr(0,firstC));
        std::string nextNumbs{""};
        if (firstC != std::string::npos) nextNumbs = numbs.substr(firstC+1,std::string::npos);
        if (firstQ == std::string::npos && firstH == std::string::npos)
        {
            //std::cout << "Fel, Inga ? eller # kvar" << std::endl;
            cacheVals[line] = 0;
            return 0;
        }
        else if (firstH < firstQ)
        {
            firstIndx = firstH;
        }
        else
        {
            firstIndx = firstQ;
        }
        combs = combs.substr(firstIndx, std::string::npos);
        //std::cout << "Inga punkter! " << combs << " " << numbs << "  nn  " << nextNumbs << std::endl;
        std::size_t firstDot = combs.find('.');
        if (combs[0] == '?')
        {
            numCombs += calcCombinations(combs.substr(1,std::string::npos) + " " + numbs);  
        }
        if ((combs.length() < nextDmg))
        {
            //std::cout << "Fel, finns inte plats kvar! 1" << std::endl;
            cacheVals[line] = 0;
            return 0;
        }
        /* else if (firstDot < nextDmg && combs.find('#') < nextDmg)
        {
            std::cout << "Fel, finns inte plats kvar! 2" << std::endl;
            cacheVals[line] = 0;
            return 0;
        } */
        else
        {
            if (combs.length() == nextDmg && firstDot == std::string::npos)
            {
                numCombs += calcCombinations( " " + nextNumbs );
            }
            else if ((combs[nextDmg] != '#') && (firstDot >= nextDmg))
            {
                numCombs += calcCombinations( combs.substr(nextDmg+1, std::string::npos) + " " + nextNumbs);
            }
            
        }
        //std::cout << line << " -  " << numCombs << std::endl;
        cacheVals[line] = numCombs;
        return numCombs;
        
        
        
    }
    //std::cout << "SUPERFEL!" << std::endl;
    return -1;
    
    
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
    std::vector<std::string> springs, springsB;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            springs.push_back(line);
            std::vector<std::string> split = splitLine(line, " ");
            std::string config{split[0]}, numbs{split[1]};
            for (int i{0};i<4;i++)
            {
                config += "?" + split[0];
                numbs += "," + split[1];
            }
            springsB.push_back(config + " " + numbs);
        }
    }
    myfile.close();
    //std::cout << springs.size() << std::endl;
    long ansA{0};
    for (std::string s : springs)
    {
        int val = calcCombinations(s);
        ansA += val;
        //std::cout << s << " combs " << val << std::endl;
    }
    std::cout << "Answer part A: " << ansA << std::endl;
    long ansB{0};
    for (std::string s : springsB)
    {
        long val = calcCombinations(s);
        ansB += val;
        //std::cout << s << " combs " << val << std::endl;
    }
    std::cout << "Answer part B: " << ansB << std::endl;
}