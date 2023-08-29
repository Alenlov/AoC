#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

char safe{'.'}, trap{'^'};

std::set<std::string> newTrap{ "^^.", "^..", "..^", ".^^" };

std::string nextRow(std::string prevRow)
{
    std::string fullRow{'.' + prevRow + '.'};
    std::string row{""};
    for (int i = 0; i < prevRow.length(); i ++)
    {
        if(newTrap.contains(fullRow.substr(i,3)))
        {
            row += '^';
        }
        else
        {
            row += '.';
        }
    }

    return row;
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
        getline(myfile,line);
    }
    unsigned int count{0};
    for (int i{0}; i < 400000; i++) {
        if (i==40) std::cout << "Answer part A: " << count << '\n';
        count += std::count(line.begin(), line.end(), '.');
        line = nextRow(line);

    }

    std::cout << "Answer part B: " << count << '\n';
    return 0;
}
