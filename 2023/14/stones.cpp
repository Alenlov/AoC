#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
#include <set>
#include <map>

struct stone
{
    int row, col;

    stone(int r, int c) : row(r), col(c) {};
};

struct sort_east
{
    inline bool operator() (const stone& s1, const stone& s2)
    {
        return (s1.col > s2.col);
    }
};
struct sort_west
{
    inline bool operator() (const stone& s1, const stone& s2)
    {
        return (s1.col < s2.col);
    }
};
struct sort_north
{
    inline bool operator() (const stone& s1, const stone& s2)
    {
        return (s1.row < s2.row);
    }
};
struct sort_south
{
    inline bool operator() (const stone& s1, const stone& s2)
    {
        return (s1.row > s2.row);
    }
};

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

std::set<std::pair<int,int>> blocks;
std::vector<stone> stones;
int maxRow{0}, maxCol{0};
void moveNorth()
{
    std::map<int,int> depthPerCol;
    std::sort(stones.begin(), stones.end(), sort_north());
    for (int i{0}; i < stones.size(); i++)
    {
        int minRow{0};
        int c = stones[i].col, r = stones[i].row;
        if (depthPerCol.contains(c))
        {
            minRow = depthPerCol[c] + 1;
        }
        while( (!blocks.contains({r-1,c}) ) && ((r-1) >= minRow) )
        {
            --r;
        }
        stones[i].row = r;
        depthPerCol[c] = r;
    }
}
void moveWest()
{
    std::map<int,int> depthPerRow;
    std::sort(stones.begin(), stones.end(), sort_west());
    for (int i{0}; i < stones.size(); i++)
    {
        int minCol{0};
        int c = stones[i].col, r = stones[i].row;
        if (depthPerRow.contains(r))
        {
            minCol = depthPerRow[r] + 1;
        }
        while( (!blocks.contains({r,c-1}) ) && ((c-1) >= minCol) )
        {
            --c;
        }
        stones[i].col = c;
        depthPerRow[r] = c;
    }
}
void moveSouth()
{
    std::map<int,int> depthPerCol;
    std::sort(stones.begin(), stones.end(), sort_south());
    for (int i{0}; i < stones.size(); i++)
    {
        int minRow{maxRow-1};
        int c = stones[i].col, r = stones[i].row;
        if (depthPerCol.contains(c))
        {
            minRow = depthPerCol[c] - 1;
        }
        while( (!blocks.contains({r+1,c}) ) && ((r+1) <= minRow) )
        {
            ++r;
        }
        stones[i].row = r;
        depthPerCol[c] = r;
    }
}
void moveEast()
{
    std::map<int,int> depthPerRow;
    std::sort(stones.begin(), stones.end(), sort_east());
    for (int i{0}; i < stones.size(); i++)
    {
        int minCol{maxCol-1};
        int c = stones[i].col, r = stones[i].row;
        if (depthPerRow.contains(r))
        {
            minCol = depthPerRow[r] - 1;
        }
        while( (!blocks.contains({r,c+1}) ) && ((c+1) <= minCol) )
        {
            ++c;
        }
        stones[i].col = c;
        depthPerRow[r] = c;
    }
}


long loadOnNorthSupport()
{
    long load{0};
    for (stone s : stones)
    {
        load += maxRow - s.row;
    }
    return load;
}
long ansA{0};
void makeCycle()
{
    moveNorth();
    if (ansA == 0) ansA = loadOnNorthSupport();
    moveWest();
    moveSouth();
    moveEast();
}
void printMap()
{
    std::cout << "===== Map =====" << std::endl;
    std::sort(stones.begin(), stones.end(), sort_north());
    for (int row{0}; row < maxRow; row++)
    {
        for (int col{0}; col < maxCol; col++)
        {
            if (blocks.contains({row,col}))
            {
                std::cout << '#';
            }
            else
            {
                bool aStone{false};
                for (stone s : stones)
                {
                    if (s.row == row && s.col == col)
                    {
                        std::cout << 'O';
                        aStone = true;
                        break;
                    }
                }
                if(!aStone) std::cout << '.';
            }
            
        }
        std::cout << std::endl;
    }
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
    int row{0}, col{0};

    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            col = 0;
            for (char c : line)
            {
                if (c == 'O')
                {
                    stones.push_back({row,col});
                }
                else if (c == '#')
                {
                    blocks.insert({row,col});
                }
                
                ++col;
            }
            ++row;
        }
    }
    maxRow = row;
    maxCol = col;

    myfile.close();

    // One move nor

    std::map<long,std::vector<long>> valsToCycles;
    long cycles{0}, possCycle{0}, cycleOk{0};
    valsToCycles[loadOnNorthSupport()].push_back(cycles);
    bool cyclesFound{false}, testCycle{false};

    while(!cyclesFound)
    {
        ++cycles;
        makeCycle();
        long northLoad = loadOnNorthSupport();
        valsToCycles[northLoad].push_back(cycles);
        int sizeOfVals = valsToCycles[northLoad].size(); 
        if (sizeOfVals>2)
        {
            if (!testCycle)
            {
                possCycle = valsToCycles[northLoad][sizeOfVals-1] - valsToCycles[northLoad][sizeOfVals-2];
                cycleOk = 0;
                testCycle = true;
                //std::cout << "Possible cycle " << possCycle << std::endl;
            }
            else
            {
                int j{2};
                while( valsToCycles[northLoad][sizeOfVals-1] - valsToCycles[northLoad][sizeOfVals-j] < possCycle) ++j;
                if (valsToCycles[northLoad][sizeOfVals-1] - valsToCycles[northLoad][sizeOfVals-j] == possCycle)
                {
                    //std::cout << valsToCycles[northLoad][sizeOfVals-1] - valsToCycles[northLoad][sizeOfVals-j] << " : " << cycleOk << std::endl;
                    ++cycleOk;
                }
                else
                {
                    testCycle = false;
                    cycleOk = 0;
                    possCycle = 0;
                }
            }
        }
        else
        {
            if (testCycle)
            {
                testCycle = false;
                cycleOk = 0;
                possCycle = 0;
            }
        }
        if (cycleOk == possCycle && testCycle)
        {
            cyclesFound = true;
        }
    }

    std::cout << "Answer part A: " << ansA << std::endl;
    long target{1000000000};
    long ansB{0}, cycleLength{possCycle}; // 7 for test 26 for input :(
   //std::cout << cycleLength << " " << cycles << std::endl;
    for (auto const [k,v] : valsToCycles)
    {
        if (v.size() > 2)
        {
            //std::cout << k << " : ";
            //for (int i{0}; i < v.size(); i++) std::cout << v[i] << " ";
            //std::cout <<std::endl;
            long sum{v[v.size()-1] - v[v.size()-2]}, i{1};
            //std::cout << sum << std::endl;
            while(sum <= cycleLength)
            {
                sum += v[v.size()-i];
                if ((target - v[v.size()-i]) % cycleLength == 0)
                {
                    //std::cout << target << " - " << v[v.size()-i] << " = " << (target - v[v.size()-i]) << std::endl;
                    //std::cout << k << " : ";
                    //for (int i{0}; i < v.size(); i++) std::cout << v[i] << " ";
                    //std::cout <<std::endl;
                    ansB = k;
                    break;
                }
                ++i;
                
                sum -= v[v.size()-i];
            }
            
        }
        if (ansB != 0) break;
    }
    std::cout << "Answer part B: " << ansB << std::endl;
    
}