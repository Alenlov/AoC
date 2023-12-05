#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

struct treeNode
{
    int numChild, numMeta;
    std::vector<int> childs;
    std::vector<int> metaData;
    int value{-1};
};

std::map<int,treeNode> treeMap;

std::pair<int,int> createNode(int head, std::vector<int> tree, int id)
{
    treeNode t;
    t.numChild = tree[head];
    t.numMeta = tree[head+1];
    treeMap[id] = t;
    head += 2;
    int newId = id+1;
    for (int j = 0; j < t.numChild; j++){
        std::pair<int,int> headId = createNode(head, tree, newId);
        treeMap[id].childs.push_back(newId);
        newId = headId.second;
        head = headId.first;
    }
    for (int j = 0; j < t.numMeta; j++)
    {
        treeMap[id].metaData.push_back(tree[head+j]);
    }
    return {head + t.numMeta, newId+1};
    
}

int value(int node)
{
    if (treeMap[node].value >= 0) return treeMap[node].value;
    int val{0};
    if (treeMap[node].numChild == 0)
    {
        for (int m : treeMap[node].metaData)
        {
            val += m;
        }
        
    }
    else
    {
        for (int m : treeMap[node].metaData)
        {
            if ((m <= treeMap[node].numChild) && (m > 0))
            {
                val += value(treeMap[node].childs[m-1] );
            }
        }
    }
    treeMap[node].value = val;
    return val;
}

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
    if (myfile.is_open())
    {
        std::getline(myfile,line);
    }
    myfile.close();
    std::vector<int> tree;
    for(std::string s : splitLine(line))
    {
        tree.push_back(std::stoi(s));
    }

    int id{0};
    int head{0};

    createNode(head, tree, id);
    int totMeta{0};
    for (auto [i, t] : treeMap)
    {
        for (int m : t.metaData)
        {
            totMeta += m;
        }
    }
    
    std::cout << "Answer part A: " << totMeta << std::endl;
    std::cout << "Answer part B: " << value(0) << std::endl;
    
}