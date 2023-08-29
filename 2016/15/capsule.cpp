#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

struct Disc
{
    int level{};
    int positions{};
    int start{};
};

bool isMatch(int time, Disc &d)
{
    std::cout << d.level << " " << d.start << " " << d.positions << '\n';
    int timeForPass = time + d.level;
    return (timeForPass + d.start) % d.positions == 0;
}

int main(int argc, char const *argv[])
{
    std::string line;
    std::ifstream myfile;
    std::cout << argc << '\n';

    if (argc > 1)
    {
        myfile.open(argv[1]);
    }
    
    std::regex reg{"Disc #(\\d+) has (\\d+) positions; at time=(\\d+), it is at position (\\d+)."};
    std::smatch s;

    std::vector<Disc> discs;

    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            if (std::regex_match(line,s,reg))
            {
                discs.emplace_back( Disc{std::stoi(s[1]), std::stoi(s[2]), std::stoi(s[4])} );
            }
        }
       
    }
    if (argc > 2)
    {
        int numDiscs = discs.size();
        discs.emplace_back( Disc{ numDiscs+1 ,11,0} );
    }
    
    int time{-1};
    int increment{1};

    while ( !discs.empty() )
    {
        for (std::vector<Disc>::iterator it = discs.begin(); it != discs.end();) {
            time += increment;
            if (isMatch(time, *it)) 
            {
                increment *= it->positions;
                discs.erase(it);
            }
            else
            {
                ++it;
            }
            
        }
        
    }
    std::cout << "Answer part A: " << time << '\n';

    return 0;
}
