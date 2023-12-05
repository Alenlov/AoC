#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
/*




*/

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
    int diffSum{0}, divSum{0};
    if (myfile.is_open())
    {
        while(getline(myfile,line)) {
            int minV{1 << 30}, maxV{0};
            std::vector<int> values;
            for(std::string s : splitLine(line, "\t")){
                int val = std::stoi(s);
                values.push_back(val);
                if (val > maxV) {
                    maxV = val;
                }
                if (val < minV)
                {
                    minV = val;
                }
            }
            diffSum += maxV - minV;
            for(int i = 0; i < values.size()-1; i ++) {
                for(int j = i+1; j < values.size(); j++) {
                    if(values[i] < values[j]) {
                        if (values[j] % values[i] == 0) divSum += values[j]/values[i];
                    } else {
                        if (values[i] % values[j] == 0) divSum += values[i]/values[j];
                    }
                }
            }
            
        }
    }
    std::cout << "Answer part A: " << diffSum << std::endl;
    std::cout << "Answer part B: " << divSum << std::endl;
    

}