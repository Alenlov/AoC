#include <iostream>
#include <string>
#include "md5.h"
#include <map>
#include <vector>
#include <deque>
#include <limits>

std::map<int,char> dirs{{0,'U'},{1,'D'},{2,'L'},{3,'R'}};

std::vector<char> openDirections(std::string md5hash)
{
    //std::cout << md5hash << '\n';
    std::vector<char> output;
    for (auto const& [k,v] : dirs) {
        //std::cout << "Testing " << md5hash[k] << " " << k << '\n';
        if (md5hash[k] > 'a')
        {
            output.push_back(v);
        }
    }
    return output;
}

std::pair<int,int> position(std::string moves)
{
    int row{0}, col{0};
    for (char c : moves)
    {
        if (c == 'U')
        {
            row--;
        }
        else if (c == 'D')
        {
            row++;
        }
        else if (c == 'L')
        {
            col--;
        }
        else if (c == 'R')
        {
            col++;
        }
        
    }
    return {row, col};
}

int main(int argc, char const *argv[])
{
    if (! (argc >1) )
    {
        std::cout << "Ange vilket problem!\n";
        return -1;
    }
    std::string_view problem{argv[1]};
    std::string input;
    int length;
    if (problem == "test1") 
    {
        input = "ihgpwlah";
    } 
    else if (problem == "test2") 
    {
        input = "kglvqrro";
    } 
    else if (problem == "test3") 
    {
        input = "ulqzkmiv";
    } 
    else if (problem == "input")
    {
        input = "awrkjxxr";
    }

    int minRow{0}, maxRow{3}, minCol{0}, maxCol{3};

    std::deque<std::string> paths{""};
    std::string bestPath{""};
    int curMin{std::numeric_limits<int>::max()};
    int curMax{0};
    while(!paths.empty())
    {   
        std::string curPath{paths.front()};
        paths.pop_front();
        std::pair<int,int> curPos{position(curPath)};
        //std::cout << curPath << " position " << curPos.first << " " << curPos.second << '\n';
        int lengthOfPath = curPath.length();
        if (curPos.first < 0 || curPos.first > 3 || curPos.second < 0 || curPos.second > 3) continue;
        //if (lengthOfPath > curMin) continue;
        if (curPos.first == 3 && curPos.second == 3)
        {
            if (lengthOfPath < curMin)
            {
                curMin = lengthOfPath;
                bestPath = curPath;
            }
            if (lengthOfPath > curMax)
            {
                curMax = lengthOfPath;
            }
        }
        else{
            std::string hash{md5(input + curPath)};
            //std::cout << "Hash for " << input + curPath << " is " << hash << '\n'; 
            std::vector<char> open{openDirections(hash)};

            for (char c : open)
            {
                paths.push_back(curPath + c);
                //std::cout << "Path " << c << " is open giving " << curPath + c << '\n';
            }
        }

    }
    std::cout << "Answer part A: " << bestPath << '\n';
    std::cout << "answer part B: " << curMax << '\n';
    return 0;
}
