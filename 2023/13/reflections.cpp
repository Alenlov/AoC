#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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

long reflectionIndx(std::vector<long> nums)
{
    for (long i{1}; i < nums.size(); i++)
    {
        if (nums[i-1] == nums[i])
        {
            // Möjlig match
            long j{1};
            bool isMatch{true};
            while ( (i-1-j >= 0) && (i+j < nums.size()))
            {
                if (nums[i-1-j] != nums[i+j])
                {
                    isMatch = false;
                    break;
                }
                ++j;
            }
            if (isMatch) return i;
        }
    }
    return 0;
}

bool offByOne(long lhs, long rhs)
{
    long diff{lhs ^ rhs};
    
    return (diff>0)&& ((diff & (diff-1)) == 0);
}

long reflectionIndxSmudge(std::vector<long> nums)
{
    for (long i{1}; i < nums.size(); i++)
    {
        if (nums[i-1] == nums[i] || offByOne(nums[i-1], nums[i]))
        {
            int numOffByOne{0};
            if (offByOne(nums[i-1], nums[i])) ++numOffByOne;
            // Möjlig match
            long j{1};
            bool isMatch{true};
            while ( (i-1-j >= 0) && (i+j < nums.size()))
            {
                if (nums[i-1-j] != nums[i+j])
                {
                    if (offByOne(nums[i-1-j], nums[i+j]))
                    {
                        ++numOffByOne;
                    }
                    else
                    {
                        isMatch = false;
                        break;
                    }
                    if (numOffByOne > 1)
                    {
                        isMatch = false;
                        break;
                    }
                }
                ++j;
            }
            if (numOffByOne == 0) isMatch = false;
            if (isMatch) return i;
        }
    }
    return 0;
}

struct lava
{
    std::vector<std::vector<char>> indata;
    std::vector<long> rowNums, colNums;

    void calcNums()
    {
        // Rows
        for (int y{0}; y < indata.size(); y++)
        {
            long pow{1}, num{0};
            for (int x{0}; x < indata[y].size(); x++)
            {
                if (indata[y][x] == '#')
                {
                    num += pow;
                }
                pow *= 2;
            }
            rowNums.push_back(num);
        }

        // Cols
        for (int x{0}; x < indata[0].size(); x++)
        {
            long pow{1}, num{0};
            for (int y{0}; y < indata.size(); y++)
            {
                if (indata[y][x] == '#')
                {
                    num += pow;
                }
                pow *= 2;
            }
            colNums.push_back(num);
        }
    }

    long calcVal()
    {
        return 100*reflectionIndx(rowNums) + reflectionIndx(colNums);
    }

    long calcValSmudge()
    {
        return 100*reflectionIndxSmudge(rowNums) + reflectionIndxSmudge(colNums);
    }
};


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
    std::vector<lava> lavas;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            lava l;
            while (line.size() > 0)
            {
                std::vector<char> row;
                for (char c : line) row.push_back(c);
                l.indata.push_back(row);
                getline(myfile,line); 
            }
            l.calcNums();
            lavas.push_back(l);
        }
    }
    myfile.close();
    
    //std::cout << lavas.size() << std::endl;
    long ansA{0}, ansB{0}, ind{0};
    for (auto l : lavas)
    {
        //std::cout <<  l.calcValSmudge() << std::endl;
        ansA += l.calcVal();
        ansB += l.calcValSmudge();
        ++ind;
    }
    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << ansB << std::endl;
    //std::cout << offByOne(2,1) << std::endl;
}