#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <vector>
#include <set>

struct star
{
    int x, y, vx, vy;
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
    const std::regex reFull("position=<([- \\d]+),([- \\d]+)> velocity=<([- \\d]+),([- \\d]+)>");
    std::smatch m;
    std::vector<star> stars;
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            if (std::regex_match(line, m, reFull))
            {
                star s;
                s.x = std::stoi(m[1]);
                s.y = std::stoi(m[2]);
                s.vx = std::stoi(m[3]);
                s.vy = std::stoi(m[4]);
                stars.push_back(s);
                /* for (int i = 0; i < 4; i++)
                {
                    std::cout << m[i+1] << " " << std::stoi(m[i+1]) << " : ";
                }
                std::cout << std::endl; */
            }
        }
    }
    myfile.close();

    bool noPattern{true};
    int s{0};
    int minY{1<<30};
    int maxY{1<<31};
    int minX{1<<30};
    int maxX{1<<31};
    while(noPattern)
    {
        minY = 1<<30;
        maxY = 1<<31;
        minX = 1<<30;
        maxX = 1<<31;
        for (int i = 0; i < stars.size(); i++)
        {
            //std::cout << std::endl;
            //std::cout << stars[i].x << "," << stars[i].y << std::endl;
            //std::cout << stars[i].vx << "," << stars[i].vy << std::endl;
            stars[i].x += stars[i].vx;
            stars[i].y += stars[i].vy;
            if (stars[i].y > maxY) maxY = stars[i].y;
            if (stars[i].y < minY) minY = stars[i].y;
            if (stars[i].x > maxX) maxX = stars[i].x;
            if (stars[i].x < minX) minX = stars[i].x;
            //std::cout << stars[i].x << "," << stars[i].y << std::endl;
        }
        ++s;
        std::cout << s << " " << minY << " " << maxY << " diff " << maxY - minY << std::endl;
        if (maxY - minY <= 9) noPattern = false;
    }

    std::set<std::pair<int,int>> starSet;
    for (star s : stars)
    {
        starSet.insert({s.x,s.y});
    }

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            if (starSet.contains({x,y}))
            {
                std::cout << "#";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

