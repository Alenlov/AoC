#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <list>

std::map<char, char> dirB{{'0','R'},{'1','D'},{'2','L'},{'3','U'}};

std::map<bool, std::string> Uturn{{true, "URDL"}, {false, "ULDR"}};

struct point
{
    long x, y;

    point& operator+=(const point& rhs) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        this->x += rhs.x;
        this->y += rhs.y;
        return *this; // return the result by reference
    }

    std::strong_ordering operator<=>(const point& that) const
    {
        return std::tie(x,y) <=> std::tie(that.x,that.y);
    }
};

struct line
{
    point start, end;
    char dir;
    //line *prev, *next;
};


point operator+(point lhs, const point& rhs)
{
    lhs += rhs;
    return lhs;
}

point operator*(point lhs, const long i)
{
    lhs.x *= i;
    lhs.y *= i;
    return lhs;
}

std::map<char, point> dirs{ {'R',{1,0}}, {'L',{-1,0}}, {'U',{0,1}}, {'D',{0,-1}}  };

std::map<char, char> left{ {'R','U'},{'D','R'},{'L','D'},{'U','L'} },right{ {'R','D'},{'D','L'},{'L','U'},{'U','R'}  };

std::map<char,char> lr{{'L','R'},{'R','L'}};

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

long calcArea(std::list<line> lines)
{
    long area{0};
    long lineLength{0};
    for (line l : lines)
    {
        //std::cout << l.start.x << "," << l.start.y << " -> " << l.end.x << "," << l.end.y << std::endl;
        point end = l.end;// + dirs[l.dir];

        area += ( (l.start.y + end.y)*(l.start.x - end.x) );
        lineLength += dirs[l.dir].y*(l.end.y-l.start.y) + dirs[l.dir].x*(l.end.x-l.start.x);
    }
    //std::cout << lineLength << std::endl;
    if (area < 0) area *= -1;
    return area/2 + lineLength/2 + 1;
}

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string inLine;
    if (argc > 1)
    {
        myfile.open(argv[1]);
    }
    else
    {
        return -1;
    }
    
    std::list<line> lines, linesB;
    long minX{0}, maxX{0}, minY{0}, maxY{0};
    long minXb{0}, maxXb{0}, minYb{0}, maxYb{0};
    bool leftOut{false}, leftOutb{false};
    point head{0,0}, headb{0,0};
    if (myfile.is_open())
    {
        while(getline(myfile,inLine))
        {
            std::vector<std::string> split = splitLine(inLine, " ");
            char dir = split[0][0];
            long length = std::stol(split[1]);
            std::string color = split[2].substr(2,split[2].length()-3);
            std::cout << color << std::endl;
            line l;
            l.start = head;
            head += (dirs[dir]*length);
            l.end = head;
            l.dir = dir;
            lines.push_back(l);
            point lh = head + dirs[left[dir]];
            point rh = head + dirs[right[dir]];
            //std::cout << head.x << "," << head.y << " heading " << dir << " left " << lh.x << "," << lh.y << " right " << rh.x << "," << rh.y << std::endl;
            
            if (head.x < minX) minX = head.x;
            if (head.y < minY) minY = head.y;
            if (head.x > maxX) maxX = head.x;
            if (head.y > maxY) maxY = head.y;
            if (lh.x < minX || lh.x > maxX || lh.y < minY || lh.y > maxY) leftOut = true;
            else if (rh.x < minX || rh.x > maxX || rh.y < minY || rh.y > maxY) leftOut = false;

            line lb;
            lb.start = headb;
            long lenB = std::stol(color.substr(0,color.size()-1), nullptr, 16);
            dir = dirB[color[color.size()-1]];
            //std::cout << dir << " " << lenB << std::endl;
            headb += (dirs[dir]*lenB);
            lb.end = headb;
            lb.dir = dir;
            linesB.push_back(lb);
            
            lh = headb + dirs[left[dir]];
            rh = headb + dirs[right[dir]];
            //std::cout << head.x << "," << head.y << " heading " << dir << " left " << lh.x << "," << lh.y << " right " << rh.x << "," << rh.y << std::endl;
            
            if (headb.x < minXb) minXb = headb.x;
            if (headb.y < minYb) minYb = headb.y;
            if (headb.x > maxXb) maxXb = headb.x;
            if (headb.y > maxYb) maxYb = headb.y;
            if (lh.x < minXb || lh.x > maxXb || lh.y < minYb || lh.y > maxYb) leftOutb = true;
            else if (rh.x < minXb || rh.x > maxXb || rh.y < minYb || rh.y > maxYb) leftOutb = false;

        }
    }
    myfile.close();
    std::cout << lines.size() << " " << leftOut << std::endl;
    std::cout << linesB.size() << " " << leftOutb << std::endl;

    std::cout << "Answer part A: " << calcArea(lines) << std::endl;
    std::cout << "Answer part B: " << calcArea(linesB) << std::endl;
    
}