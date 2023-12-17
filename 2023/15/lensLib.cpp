#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <list>

struct lens
{
    std::string label;
    int focal;
};

struct box
{
    std::list<lens> lenses;
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

int hash(std::string s)
{
    int val{0};
    for (char c : s)
    {
        val = (val + int(c))*17 % 256;
    }
    return val;
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
    std::vector<std::string> instructions;
    long ansA{0};
    if (myfile.is_open())
    {
        getline(myfile,line);
        for (auto s : splitLine(line, ","))
        {
            ansA += hash(s);
            instructions.push_back(s);
        }
    }
    myfile.close();

    std::cout << "Answer part A " << ansA << std::endl;
    std::map<int, std::list<lens>> boxes;
    for (auto inst : instructions)
    {
        if (inst[inst.size()-1] == '-')
        {
            std::string label = inst.substr(0,inst.size()-1);
            int box = hash(label);
            std::cout << label << " " << box << " " << inst << std::endl;
            if (boxes.contains(box))
            {
                auto it = boxes[box].begin();
                while (it != boxes[box].end())
                {
                    if (it->label == label)
                    {
                        it = boxes[box].erase(it);
                        break;
                    }
                    ++it;
                }
            }
        }
        else
        {
            int focal = int(inst[inst.size()-1]) - int('0');
            std::string label = inst.substr(0,inst.size()-2);
            int box = hash(label);
            std::cout << label << " " << box << " " << inst << std::endl;
            auto it = boxes[box].begin();
            while (it != boxes[box].end())
            {
                if (it->label == label)
                {
                    it->focal = focal;
                    break;
                }
                ++it;
            }
            if (it == boxes[box].end())
            {
                lens l;
                l.focal = focal;
                l.label = label;
                boxes[box].push_back(l);
            }
            
        }
        
    }
    long ansB{0};
    for (auto const [box, lenses] : boxes)
    {
        int i{1};
        for (auto lens : lenses)
        {
            std::cout << (box + 1) << " " << lens.label << " " << lens.focal << std::endl;
            ansB += (box+1)*i*lens.focal;
            ++i;
        }
    }
    std::cout << "Answer part B " << ansB << std::endl;
    
    
}