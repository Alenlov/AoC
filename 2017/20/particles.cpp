#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <tuple>
#include <set>

struct particle
{
    std::map<char,std::tuple<int,int,int>> p;
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
    std::set<int> particleIds;
    std::map<int,particle> particles;
    int indx{0};
    int smallest{(1<<30)}, smallIndx;
    std::vector<int> smallVec;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line,", ");
            particle p;
            for (std::string s : split)
            {
                std::vector<std::string> vStrings = splitLine(s.substr(3,s.length()-4),",");
                //for (auto sv : vStrings) std::cout << sv << " ";
                //std::cout << std::endl;
                std::tuple<int,int,int> vals = std::make_tuple(std::stoi(vStrings[0]),std::stoi(vStrings[1]),std::stoi(vStrings[2]));
                p.p[s[0]] = vals;
                if (s[0] == 'a')
                {
                    int acc{0};
                    for (std::string sv : vStrings)
                    {
                        acc += abs(std::stoi(sv));
                    }
                    if (acc < smallest)
                    {
                        smallVec = {indx};
                        smallest = acc;
                        smallIndx = indx;
                    }
                    else if (acc == smallest)
                    {
                        smallVec.push_back(indx);
                    }
                    
                }
            }
            particles[indx] = p;
            particleIds.insert(indx);
            ++indx;
        }
    }
    int smallV{(1<<30)};
    myfile.close();
    for(int i : smallVec)
    {
        std::tuple<int,int,int> v = particles[i].p['v'];
        int totVec{0};
        totVec = abs(std::get<0>(v)) + abs(std::get<1>(v)) + abs(std::get<2>(v));
        if (totVec < smallV)
        {
            smallV = totVec;
            smallIndx = i;
        }
    }

    std::cout << "Answer part A: " << smallIndx << std::endl; 

    /*
    For each coordinate we have that
    position at time t = position at time 0 + t * velocity at zero + t*(t-1)/2 * acceleration at 0.

    For two particles to collide we have that

    For each coordinate

    p_1 + t * v_1 + t*(t-1)/2 * a_1 = p_2 + t * v_2 + t*(t-1)/2 * a_2

    
    */
    std::map<int, std::vector<std::pair<int,int>>> collisions;
    int maxTime{-1};
    for (auto [i,p1] : particles)
    {
        for (auto [j,p2] : particles)
        {
            if (i > j)
            {
                // X
                int p_1_x, v_1_x, a_1_x, p_2_x, v_2_x, a_2_x;
                p_1_x = std::get<0>(p1.p['p']);
                v_1_x = std::get<0>(p1.p['v']);
                a_1_x = std::get<0>(p1.p['a']);
                p_2_x = std::get<0>(p2.p['p']);
                v_2_x = std::get<0>(p2.p['v']);
                a_2_x = std::get<0>(p2.p['a']);
                int A_x{a_1_x - a_2_x};
                int B_x{2*v_1_x - 2*v_2_x - a_2_x + a_1_x};
                int C_x{2*p_1_x - 2*p_2_x};
                if ( 4*A_x*C_x <= B_x*B_x  )
                {
                    int maxT{ abs(B_x) + abs(C_x) };
                    for (int t = 0; t < maxT ; t++)
                    {
                        if ((A_x * t * t + B_x * t + C_x) == 0 )
                        {
                            // Träff
                            
                            int p_1_y, v_1_y, a_1_y, p_2_y, v_2_y, a_2_y;
                            p_1_y = std::get<1>(p1.p['p']);
                            v_1_y = std::get<1>(p1.p['v']);
                            a_1_y = std::get<1>(p1.p['a']);
                            p_2_y = std::get<1>(p2.p['p']);
                            v_2_y = std::get<1>(p2.p['v']);
                            a_2_y = std::get<1>(p2.p['a']);
                            int A_y{a_1_y - a_2_y};
                            int B_y{2*v_1_y - 2*v_2_y - a_2_y + a_1_y};
                            int C_y{2*p_1_y - 2*p_2_y};
                            if (((A_y * t * t + B_y * t + C_y) == 0) )
                            {
                                int p_1_z, v_1_z, a_1_z, p_2_z, v_2_z, a_2_z;
                                p_1_z = std::get<2>(p1.p['p']);
                                v_1_z = std::get<2>(p1.p['v']);
                                a_1_z = std::get<2>(p1.p['a']);
                                p_2_z = std::get<2>(p2.p['p']);
                                v_2_z = std::get<2>(p2.p['v']);
                                a_2_z = std::get<2>(p2.p['a']);
                                int A_z{a_1_z - a_2_z};
                                int B_z{2*v_1_z - 2*v_2_z - a_2_z + a_1_z};
                                int C_z{2*p_1_z - 2*p_2_z};

                                if (((A_z * t * t + B_z * t + C_z) == 0) )
                                {
                                    std::cout << i << " collided with " << j << " at " << t << std::endl;
                                    collisions[t].push_back(std::make_pair(i,j));
                                    if (t > maxTime) maxTime = t;
                                    break;
                                }
                            }

                            
                        }
                    }
                }
                else continue;
            }
        }
    }
    std::cout << collisions.size() << std::endl;
    for (int t = 0; t <= maxTime; t++)
    {
        if (collisions.contains(t))
        {
            std::cout << t << std::endl;
            std::set<int> toRemove;
            for (std::pair<int,int> p : collisions[t])
            {
                if (particleIds.contains(p.first) && particleIds.contains(p.second))
                {
                    toRemove.insert(p.first);
                    toRemove.insert(p.second);
                }
            }
            for (int id : toRemove)
            {
                particleIds.erase(id);
            }
        }
    }
    std::cout << "Answer part B: " << particleIds.size() << std::endl;
}
