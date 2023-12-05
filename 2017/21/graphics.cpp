#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

std::map<char, int> mapOn{ {'#',1}, {'.',0} };

struct enchancementRule
{
    std::vector<std::vector<char>> lhs, rhs;
    int size, numOn, id;
    std::vector<int> toIds;
};


std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos)
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

void print(std::vector<std::vector<char>> toPrint)
{
    std::cout << "--- Print art ----" << std::endl;
    for(std::vector<char> vc : toPrint)
    {
        for(char c : vc)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}



bool matchArtFixed(std::vector<std::vector<char>> lhs, std::vector<std::vector<char>> rhs)
{
    int size = lhs.size();
    if (size != rhs.size()) return false;

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(lhs[i][j] != rhs[i][j]) return false;
        }
    }
    return true;
}

bool matchArt(std::vector<std::vector<char>> lhs, std::vector<std::vector<char>> rhs)
{
    // generate all rotations and flips!
    bool anyMatch{false};
    int size = lhs.size();
    //std::cout << "--- lhs ---" << std::endl;
    //print(lhs);
    std::vector<std::vector<char>> toTest = lhs;
    for(int f = 0; f < 2; f++)
    {
        std::vector<std::vector<char>> flip = toTest;
        for(int i = 0; i < size; i++)
        {
            flip[0][i] = toTest[size-1][i];
            flip[size-1][i] = toTest[0][i];
        }
        toTest = flip;
        //std::cout << "--- Flip ---" << std::endl;
        //print(toTest);
        // flip
        for(int r = 0; r < 4; r++)
        {
            std::vector<std::vector<char>> rotate = toTest;
            for(int i = 0; i < size - 1; i++)
            {
                rotate[0][i] = toTest[size-1-i][0];
                rotate[size-1][size-1-i] = toTest[i][size-1];
                rotate[size-1-i][0] = toTest[size-1][size-1-i];
                rotate[i][size-1] = toTest[0][i];
            }
            toTest = rotate;
            //std::cout << "--- toTest --- num = " << f*4+r << std::endl;
            //print(toTest);
            //rotate and test
            if(matchArtFixed(toTest, rhs))
            {
                anyMatch = true;
            }
        }
    }
    return anyMatch;
    
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
    int idTwo{0}, idThree{0};
    std::vector<std::vector<char>> art{{'.','#','.'},{'.','.','#'},{'#','#','#'}};
    std::map<int, enchancementRule> rulesTwo, rulesThree;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, " => ");
            std::vector<std::string> splitLhs = splitLine(split[0], "/");
            std::vector<std::string> splitRhs = splitLine(split[1], "/");

            int size = splitLhs.size();
            enchancementRule e;
            e.size = size;
            int numOn{0};
            for(int i = 0; i < size; i++)
            {
                e.lhs.push_back({});
                for(int j = 0; j < size; j++)
                {
                    e.lhs[i].push_back(splitLhs[i][j]);
                    numOn += mapOn[splitLhs[i][j]];
                }
            }
            for(int i = 0; i < size+1; i++)
            {
                e.rhs.push_back({});
                for(int j = 0; j < size+1; j++)
                {
                    e.rhs[i].push_back(splitRhs[i][j]);
                }
            }
            e.numOn = numOn;
            if (size == 2)
            {
                e.id = idTwo;
                rulesTwo[idTwo] = e;
                ++idTwo;
            }
            else if (size == 3)
            {
                e.id = idThree;
                rulesThree[idThree] = e;
                ++idThree;
            }
            

        }
    }
    myfile.close();
    for(auto [i2,e2] : rulesTwo)
    {
        for(auto [i3,e3] : rulesThree)
        {
            if(matchArt(e2.rhs,e3.lhs))
            {
                rulesTwo[i2].toIds = {i3};
                break;
            }
        }
    }
    for(auto [i3,e3] : rulesThree)
    {
        for (int row = 0; row < 2; row++)
        {
            for (int col = 0; col < 2; col++)
            {
                std::vector<std::vector<char>> toTest = { {e3.rhs[row*2][col*2], e3.rhs[row*2][col*2 + 1]}, {e3.rhs[row*2+1][col*2], e3.rhs[row*2+1][col*2 + 1]}  };
                for(auto [i2,e2] : rulesTwo)
                {
                    if(matchArt(toTest,e2.lhs))
                    {
                        rulesThree[i3].toIds.push_back(i2);
                        std::cout << rulesThree[i3].toIds.size() << std::endl;
                        break;
                    }
                }
            }
        }
    }
    
    int maxItr{18};
    for(int itr = 0; itr < maxItr; itr++)
    {   
        std::cout << itr << std::endl;
        if(itr == 5)
        {
            int ansA{0};
            for(std::vector<char> artVec : art)
            {
                for(char a : artVec)
                {  
                    ansA += mapOn[a];
                }
            }
            std::cout << "Answer part A: " << ansA << std::endl;
        }
        std::vector<std::vector<char>> newArts;
        if(art.size() % 2 == 0)
        {
            newArts.resize(art.size()/2 * 3);
            for(int row = 0; row < art.size()/2; row++)
            {
                for(int col = 0; col < art.size()/2; col++)
                {
                    std::vector<std::vector<char>> toEnchance{ {art[row*2][col*2], art[row*2][col*2 + 1]}, {art[row*2+1][col*2], art[row*2+1][col*2 + 1]} };
                    for(auto [i2,e2] : rulesTwo)
                    {
                        if(matchArt(toEnchance, e2.lhs))
                        {
                            for(int r = 0; r < 3; r++)
                            {
                                for(int c = 0; c < 3; c++)
                                {
                                    newArts[row*3 + r].push_back(e2.rhs[r][c]);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        else if(art.size() % 3 == 0)
        {
            newArts.resize(art.size()/3 * 4);
            for(int row = 0; row < art.size()/3; row++)
            {
                for(int col = 0; col < art.size()/3; col++)
                {
                    std::vector<std::vector<char>> toEnchance{ {art[row*3][col*3], art[row*3][col*3 + 1], art[row*3][col*3 + 2]}, {art[row*3+1][col*3], art[row*3+1][col*3 + 1], art[row*3+1][col*3 + 2]}, {art[row*3+2][col*3], art[row*3+2][col*3 + 1], art[row*3+2][col*3 + 2]} };
                    for(auto [i3,e3] : rulesThree)
                    {
                        if(matchArt(toEnchance, e3.lhs))
                        {
                            for(int r = 0; r < 4; r++)
                            {
                                for(int c = 0; c < 4; c++)
                                {
                                    newArts[row*4 + r].push_back(e3.rhs[r][c]);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            std::cout << "ERROR!" << std::endl;
            return -1;
        }
        art = newArts;
        
    }
    int ansB{0};
    for(std::vector<char> artVec : art)
    {
        for(char a : artVec)
        {  
            ansB += mapOn[a];
        }
    }
    std::cout << "Answer part B: " << ansB << std::endl;

}