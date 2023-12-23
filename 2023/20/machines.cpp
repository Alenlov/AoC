#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>

int itr{0};
std::map<std::string, int> periods;
struct sigMod
{
    std::string name, type;
    std::vector<std::string> outputs, inputs;
    bool movedSand{false};
    sigMod() : type("")
    {
    }

    virtual std::vector<std::pair<std::string,int>> recieveSignal(std::string from, int val) 
    {
        if (name == "rx")
        {
            if (val == 0) movedSand = true;
        }
        std::vector<std::pair<std::string,int>> signals;
        for (std::string s : outputs)
        {
            signals.push_back({s, val});
        }
        return signals;
    }

    virtual void printMod()
    {
        for (std::string s : inputs) std::cout << s << " ";
        std::cout << " -> " <<  name << " -> ";
        for (std::string s : outputs) std::cout << s << " ";
        std::cout << std::endl;
        std::cout << std::endl;
    }

    virtual void reset() 
    {
        movedSand = false;
    }
};

struct flip : sigMod
{
    bool on;
    flip()
    {
        type = "flip";
        on = false;
    }

    std::vector<std::pair<std::string,int>> recieveSignal(std::string from, int val) 
    {
        std::vector<std::pair<std::string,int>> signals;
        if (val == 1) return signals;
        else
        {
            on = !on;
            int sendVal;
            if (on) sendVal = 1;
            else sendVal = 0;
            for (std::string s : outputs)
            {
                signals.push_back({s, sendVal});
            }
        }
        return signals;

    }

    void printMod()
    {
        std::cout << "F: ";
        for (std::string s : inputs) std::cout << s << " ";
        std::cout << " -> " <<  name << " -> ";
        for (std::string s : outputs) std::cout << s << " ";
        std::cout << std::endl;
        std::cout << std::endl;
    }

    void reset()
    {
        on = false;
    }
};

struct conj : sigMod
{
    std::map<std::string, int> incPulses;
    conj()
    {
        type = "conj";
    }

    std::vector<std::pair<std::string,int>> recieveSignal(std::string from, int val) 
    {
        if (incPulses.size() < inputs.size())
        {
            for (std::string s : inputs) incPulses[s] = 0;
        }
        incPulses[from] = val;
        bool allHigh{true};
        for (auto const [s, v] : incPulses) if( v == 0) allHigh = false;
        
        int sendVal{1};
        if (allHigh) sendVal = 0;
        std::vector<std::pair<std::string,int>> signals;
        for (std::string s : outputs)
        {
            signals.push_back({s, sendVal});
        }
        return signals;

    }

    void printMod()
    {
        std::cout << "C: ";
        for (std::string s : inputs) std::cout << s << " ";
        std::cout << " -> " <<  name << " -> ";
        for (std::string s : outputs) std::cout << s << " ";
        std::cout << std::endl;
        std::cout << std::endl;
        
    }

    void reset()
    {
        for (std::string s : inputs) incPulses[s] = 0;
    }
};

std::map<std::string, sigMod*> modules;


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

std::pair<long,long> pressButton()
{
    long numLow{0}, numHigh{0};
    std::queue<std::pair<std::pair<std::string, std::string>,int>> sigsToSend;
    sigsToSend.push({{"button","broadcaster"},0});

    while(!sigsToSend.empty())
    {
        std::string to = sigsToSend.front().first.second, from = sigsToSend.front().first.first;
        int val = sigsToSend.front().second;
        if (to == "zh" && val == 1)
        {
            periods[from] = itr;
        }
        sigsToSend.pop();
        //std::cout << from << " sends " << val << " to " << to << std::endl;
        if (val == 0) ++numLow;
        else if (val == 1) ++ numHigh;
        else std::cout << "Tankevurpa!" << std::endl;

        for (auto m : modules[to]->recieveSignal(from, val))
        {
            sigsToSend.push( { {to, m.first  }, m.second } );
        }
        
    }

    return {numLow, numHigh};
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
            std::vector<std::string> split = splitLine(line, " -> ");
            if (split[0][0] == '%')
            {
                flip *f = new flip;
                f->name = split[0].substr(1,split[0].length());
                for (auto s : splitLine(split[1], ", "))
                {
                    f->outputs.push_back(s);
                }
                modules[f->name] = f;
            }
            else if (split[0][0] == '&')
            {
                conj *c = new conj;
                c->name = split[0].substr(1,split[0].length());
                for (auto s : splitLine(split[1], ", "))
                {
                    c->outputs.push_back(s);
                }
                modules[c->name] = c;
            }
            else
            {
                sigMod *m = new sigMod;
                m->name = split[0];
                for (auto s : splitLine(split[1], ", "))
                {
                    m->outputs.push_back(s);
                }
                modules[m->name] = m;
            }
            
        }
    }
    myfile.close();
    //std::cout << modules.size() << std::endl;
    for (auto const [n, m] : modules)
    {
        for (std::string s : m->outputs)
        {
            if (modules.contains(s))
            {
                modules[s]->inputs.push_back(m->name);
            }
            else
            {
                modules[s] = new sigMod;
                modules[s]->name = s;
                modules[s]->inputs.push_back(m->name);
            }
        }
    }

    long numLow{0}, numHigh{0};
    while (itr < 1000)
    {
        ++itr;
        std::pair<long,long> res = pressButton();
        numLow += res.first;
        numHigh += res.second;
        
        
    }
    long ansA = numLow * numHigh;
    std::cout << "Answer part A: " << ansA << std::endl;
    long ansB{0};
    while(ansB == 0)
    {
        ++itr;
        pressButton();
        ansB = 1;
        std::string beforeEnd = modules["rx"]->inputs[0];
        for (auto s : modules[beforeEnd]->inputs)
        {
            ansB *= periods[s];
        }
    }
    std::cout << "Answer part B: " << ansB << std::endl;


}