#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <map>

struct point
{
    int r{0}, c{0};
    char d{' '};
    std::strong_ordering operator<=>(const point& that) const
    {
        if (r != that.r)
        {
            return r <=> that.r;
        }
        else if (c != that.c)
        {
            return c <=> that.c;
        }
        else
        {
            return d <=> that.d;
        }
        
        
    }
};

struct path
{
    point p;
    int heatLoss{0};

    std::strong_ordering operator<=>(const path& that) const
    {
        if (heatLoss != that.heatLoss) return heatLoss <=> that.heatLoss;
        else return p.d <=> that.p.d;
    }
};



std::vector<std::vector<int>> cityMap;


int maxCol, maxRow;


int calcHeatloss(int minS=1, int maxS=3)
{
    maxRow = cityMap.size();
    maxCol = cityMap[0].size();
    std::priority_queue<path, std::vector<path>, std::greater<path>> heads;
    std::map<point, int> visited;
    path h;
    heads.push(h);
    while(!heads.empty())
    {
        path h = heads.top();
        heads.pop();
        {
            //std::cout << h.p.r << "," << h.p.c << " " << h.p.d << " " <<  h.heatLoss << std::endl;
        }
        if (h.p.d != 'V')
        {
            int valR{0}, valL{0};
            for (int l{1}; l < minS; l++)
            {
                if (h.p.c + l < maxCol) valR += cityMap[h.p.r][h.p.c + l];
                if (h.p.c - l >= 0) valL += cityMap[h.p.r][h.p.c - l];
            }
            // move horizontal
            for (int l{minS}; l<=maxS; l++)
            {
                
                path nr, nl;
                nr.heatLoss = h.heatLoss;
                nr.p = h.p;
                nl.heatLoss = h.heatLoss;
                nl.p = h.p;
                if (nr.p.c + l < maxCol)
                {
                    valR += cityMap[h.p.r][nr.p.c+l];
                    nr.p.c += l;
                    nr.p.d = 'V';
                    nr.heatLoss += valR;
                    if (visited.contains(nr.p))
                    {
                        if (visited[nr.p] > nr.heatLoss)
                        {
                            //std::cout << nr.heatLoss << std::endl;
                            visited[nr.p] = nr.heatLoss;
                            heads.push(nr);
                        }
                    }
                    else
                    {
                        //std::cout << "Ny! " << nr.heatLoss << std::endl;
                        visited[nr.p] = nr.heatLoss;
                        heads.push(nr);
                    }
                }
                if (nl.p.c - l >= 0)
                {
                    valL += cityMap[h.p.r][nl.p.c-l];
                    nl.p.c -= l;
                    nl.p.d = 'V';
                    nl.heatLoss += valL;
                    if (visited.contains(nl.p))
                    {
                        if (visited[nl.p] > nl.heatLoss)
                        {
                            //std::cout << nl.heatLoss << std::endl;

                            visited[nl.p] = nl.heatLoss;
                            heads.push(nl);
                        }
                    }
                    else
                    {
                        //std::cout << "Ny! " << nl.heatLoss << std::endl;
                        visited[nl.p] = nl.heatLoss;
                        heads.push(nl);
                    }
                }
            }
        }
        if (h.p.d != 'H')
        {
            // move vertically
            int valD{0}, valU{0};

            for (int l{1}; l < minS; l++)
            {
                if (h.p.r + l < maxCol) valD += cityMap[h.p.r + l][h.p.c];
                if (h.p.r - l >= 0) valU += cityMap[h.p.r - l][h.p.c];
            }
            // move horizontal
            for (int l{minS}; l<=maxS; l++)
            {
                
                path nd, nu;
                nd.heatLoss = h.heatLoss;
                nd.p = h.p;
                nu.heatLoss = h.heatLoss;
                nu.p = h.p;
                if (nd.p.r + l < maxRow)
                {
                    valD += cityMap[nd.p.r+l][h.p.c];
                    nd.p.r += l;
                    nd.p.d = 'H';
                    nd.heatLoss += valD;
                    if (visited.contains(nd.p))
                    {
                        if (visited[nd.p] > nd.heatLoss)
                        {
                            //std::cout << nd.heatLoss << std::endl;
                            visited[nd.p] = nd.heatLoss;
                            heads.push(nd);
                        }
                    }
                    else
                    {
                        //std::cout << "Ny! " << nd.heatLoss << std::endl;
                        visited[nd.p] = nd.heatLoss;
                        heads.push(nd);
                    }
                }
                if (nu.p.r - l >= 0)
                {
                    valU += cityMap[nu.p.r-l][h.p.c];
                    nu.p.r -= l;
                    nu.p.d = 'H';
                    nu.heatLoss += valU;
                    if (visited.contains(nu.p))
                    {
                        if (visited[nu.p] > nu.heatLoss)
                        {
                            //std::cout << nu.heatLoss << std::endl;
                            visited[nu.p] = nu.heatLoss;
                            heads.push(nu);
                        }
                    }
                    else
                    {
                        //std::cout << "Ny! " << nu.heatLoss << std::endl;
                        visited[nu.p] = nu.heatLoss;
                        heads.push(nu);
                    }
                }
            }
        }
    }
    point end;
    end.c = maxCol - 1;
    end.r = maxRow - 1;
    end.d = 'H';
    int lossH = visited[end];
    end.d = 'V';
    int lossV = visited[end];
    if (lossH < lossV) return lossH;
    else return lossV;
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
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<int> row;
            for (char c : line) row.push_back(int(c) - int('0'));
            cityMap.push_back(row);
        }
    }
    myfile.close();
    std::cout << "Answer part A: " << calcHeatloss() << std::endl;
    std::cout << "Answer part B: " << calcHeatloss(4,10) << std::endl;
}