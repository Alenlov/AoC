#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <set>

struct port
{
    int lhs, rhs, strength;
};

struct bridge
{
    std::set<int> ports;
    int openPort;
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
    std::map<int, port> ports;
    std::vector<int> startPorts;
    int indx{0};
    if (myfile.is_open())
    {
        while(std::getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, "/");
            port p;
            p.lhs = std::stoi(split[0]);
            p.rhs = std::stoi(split[1]);
            p.strength = p.lhs + p.rhs;
            ports[indx] = p;
            if ( (p.lhs == 0) || (p.rhs == 0) )
            {
                startPorts.push_back(indx);
            }
            ++indx;
        }
    }
    myfile.close();
    std::vector<bridge> completedBridges;
    std::queue<bridge> bridgeToBuild;
    for (int s : startPorts)
    {
        bridge b;
        b.ports = {s};
        if (ports[s].lhs != 0)
        {
            b.openPort = ports[s].lhs;
        }
        else
        {
            b.openPort = ports[s].rhs;
        }
        bridgeToBuild.push(b);
        std::cout << "id:" << s << "\t " << ports[s].lhs << "/" << ports[s].rhs << " open " << b.openPort << std::endl;
    }
    
    while(bridgeToBuild.size() > 0)
    {
        //std::cout << bridgeToBuild.size() << std::endl;
        bridge b = bridgeToBuild.front();
        bridgeToBuild.pop();
        bool anyNew{false};
        for (auto [id, p] : ports)
        {
            if(!b.ports.contains(id))
            {
                if ( b.openPort == p.lhs )
                {
                    bridge b2;
                    b2.ports = b.ports;
                    b2.ports.insert(id);
                    b2.openPort = p.rhs;
                    bridgeToBuild.push(b2);   
                    anyNew = true;             
                }
                else if (b.openPort == p.rhs)
                {
                    bridge b2;
                    b2.ports = b.ports;
                    b2.ports.insert(id);
                    b2.openPort = p.lhs;
                    bridgeToBuild.push(b2);
                    anyNew = true;
                }
            }
        }
        if(!anyNew)
        {
            completedBridges.push_back(b);
        }

    }
    std::cout << completedBridges.size() << std::endl;
    int maxStrength{-1};
    int maxStrB{-1}, maxLen{-1};
    for (bridge b : completedBridges)
    {
        int str{0}, len{0};
        for (int id : b.ports)
        {
            str += ports[id].strength;
            ++len;
        }
        if (str > maxStrength)
        {
            maxStrength = str;
        }
        if (len > maxLen)
        {
            maxLen = len;
            maxStrB = str;
        }
        else if (len == maxLen)
        {
            if (str > maxStrB) maxStrB = str;
        }
        
    }
    std::cout << "Answer part A: " << maxStrength << std::endl;
    std::cout << "Answer part B: " << maxStrB << std::endl;


}