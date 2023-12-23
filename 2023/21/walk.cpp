#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

std::vector<std::vector<char>> garden;

std::pair<int,int> operator+(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
    return {lhs.first+rhs.first,lhs.second+rhs.second};
}

std::vector<std::pair<int,int>> dirs{ {1,0},{-1,0},{0,1},{0,-1}};

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
    int startCol{0}, startRow{0};
    int numEven{0}, numOdd{0};
    int row{0}, col{0};
    
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            col = 0;
            std::vector<char> rowVec;
            for (char c : line)
            {
                if (c != '#')
                {
                    if((row+col)%2 == 0) ++numEven;
                    else ++numOdd;
                }
                if (c == 'S')
                {
                    startCol = col;
                    startRow = row;
                    rowVec.push_back('.');
                }
                else
                {
                    rowVec.push_back(c);
                }
                ++col;
            }
            garden.push_back(rowVec);
            ++row;
        }
    }
    myfile.close();
    long ansA{0}, ansAsteps{64}, ansB{0}, ansBsteps{26501365};
    int N = garden.size();
    std::pair<int,int> startPos{startRow,startCol};
    std::queue<std::pair<int,int>> heads;
    heads.push(startPos);
    std::set<std::pair<int,int>> visited;
    visited.insert(startPos);
    std::map<std::pair<int,int>,int> distTo;
    distTo[startPos] = 0;
    while (!heads.empty())
    {
        std::pair<int,int> h = heads.front();
        heads.pop();
        int curDist = distTo[h];
        for (std::pair<int,int> d : dirs)
        {
            std::pair<int,int> newH = h + d;
            std::pair<int,int> insideH{ ((newH.first%N)+N)%N,((newH.second%N)+N)%N };
            if (garden[insideH.first][insideH.second] != '#' && !visited.contains(newH))
            {
                visited.insert(newH);
                distTo[newH] = curDist+1;
                if (curDist + 1 <= 3*N)
                {
                    heads.push(newH);
                }
            }
        }
    }
    for (auto const [p, l] : distTo)
    {
        if ( (l%2==0) && l <= 64) ++ansA;
    }
    
    std::vector<long> dp(ansBsteps+400);
    for (int i = ansBsteps; i >= 0; i--)
    {
        dp[i] = (i % 2 == ansBsteps % 2) + 2 * dp[i+N] - dp[i+2*N];
    }

    for (auto const [p, l] : distTo)
    {
        int dr = p.first - startRow;
        int dc = p.second - startCol;
        if (-N <= dr && dr < N && -N <= dc && dc < N)
        {
            //std::cout << dp[distTo[p]] << std::endl;
            ansB += dp[distTo[p]];
        }
    }
    std::cout << N << std::endl;
    std::cout << "Answer part A: " << ansA << std::endl;
    std::cout << "Answer part B: " << ansB << std::endl;
}