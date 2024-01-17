#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

struct hail
{
    long x,y,z,vx,vy,vz;


    std::map<char,std::pair<int,int>> inOut(long min, long max)
    {
        double inX, outX, inY, outY;
        double minX, minY, maxX, maxY;
        // inX är tiden så att x + inX * vx = min
        inX = (min - x)/(1.0*vx);
        outX = (max - x)/(1.0*vx);
        inY = (min - y)/(1.0*vy);
        outY = (max - y)/(1.0*vy);

        minX = x + inY * vx;
        maxX = x + outY * vx;
        minY = y + inX * vy;
        maxY = y + outX * vy;

        std::cout << min << " - " << max << std::endl;
        std::cout << (x + vx*inX) << " - " << (x + vx*outX) << " | " << (y + vy*inX) << " - " << (y + vy*outX) << " | " << inX << " - " << outX << std::endl;
        std::cout << (x + vx*inY) << " - " << (x + vx*outY) << " | " << (y + vy*inY) << " - " << (y + vy*outY) << " | " << inY << " - " << outY << std::endl;
        std::cout << minX << " - " << maxX << std::endl;
        std::cout << minY << " - " << maxY << std::endl;
        return {};
    }

    bool collisionWithIn(hail other, double min, double max)
    {
        // hitta tid t s.t.
        // x1+t1*vx1 = x2+t2*vx2
        // y1+t1*vy1 = y2+t2*vy2
        // t1 = (x2-x1)/vx1 + t2 vx2/vx1 in i andra f;r
        // y1 + (x2-x1) * vy1 / vx1 + t2 vy1 * vx2 / vx1 = y2 + t2 * vy2
        // Det ger
        // t2 ( vy2 - vy1 * vx2 / vx1) = y1 - y2 + (x2 - x1) * vy1 / vx1
        // Förenkling ger
        // t2 = (  (y1 - y2) * vx1 + (x2 - x1) * vy1 ) / ( vx1 * vy2 - vy1 * vx2)

        double denom = (y - other.y)*vx + (other.x - x) * vy;
        double num = (vx * other.vy - vy * other.vx);
        double t2 = denom / num;
        double t1 = (other.x - x)/vx + t2 * other.vx/vx;

        //std::cout << "Times " << t1 << " " << t2 << std::endl;
        //std::cout << "Point for Line 1: " << x + t1 * vx << "," << y + t1 * vy << std::endl;
        //std::cout << "Point for Line 2: " << other.x + t2 * other.vx << "," << other.y + t2 * other.vy << std::endl;
        if (t1 < 0) return false;
        if (t2 < 0) return false;
        double collX = x + t1 * vx, collY = y + t1 * vy;
        return (min <= collX && collX <= max && min <= collY && collY <= max);
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
    std::vector<hail> hails;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, " @ ");
            std::vector<std::string> pos = splitLine(split[0], ", ");
            std::vector<std::string> vel = splitLine(split[1], ", ");
            hail h;
            h.x = std::stol(pos[0]);
            h.y = std::stol(pos[1]);
            h.z = std::stol(pos[2]);
            h.vx = std::stol(vel[0]);
            h.vy = std::stol(vel[1]);
            h.vz = std::stol(vel[2]);
            hails.push_back(h);

            //std::cout << h.x << ", " << h.y << ", " << h.z << " @ " << h.vx << ", " << h.vy << ", " << h.vz << std::endl;
        }
    }
    myfile.close();
    long ansA{0};
    double min{200000000000000}, max{400000000000000};
    for (int i = 0; i < hails.size(); i++)
    {
        for (int j = i+1; j < hails.size(); j++)
        {
            if (hails[i].collisionWithIn(hails[j], min, max)) ++ansA;
        }
    }
    std::cout << "Answer part A: " << ansA << std::endl;
    
}