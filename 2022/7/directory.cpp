#include "directory.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>

Directory::Directory(const std::string name, Directory *root) {
    localSize = 0;
    totalSize = 0;
    numSmallWithin = 0;
    this->name = name;
    this->root = root;
}

void Directory::setSize() {
    localSize = 0;
    for(auto const& [k, v] : files) {
        localSize += v;
    }
    
    int subSize = 0;
    for(auto const& [k, v] : subDirs) {
        v->setSize();
        subSize += v->getSize();
    }
    totalSize = localSize + subSize;
}

int Directory::getSize() const
{
    return totalSize;
}

void Directory::addFile(const std::string name, const int size)
{
    files[name] = size;
}

void Directory::addSubDir(const std::string name)
{
    subDirs[name] = new Directory(name, this);
}

void Directory::print()
{
    std::cout << name << " " << totalSize  << " Num small : " << this->calcSmall() << std::endl;
}

std::map<std::string, Directory *> Directory::getSubDir() const
{
    return subDirs;
}

Directory * Directory::getSubDirByName(std::string name)
{
    return subDirs[name];
}

Directory * Directory::getRoot() const
{
    return root;
}

int Directory::calcSmall()
{
    
    int numSmall = 0;
    for(auto const& [k, v] : subDirs) {
        numSmall += v->calcSmall();
    }
    if (totalSize < 100000) {
        numSmall += totalSize;
    }
    return numSmall;
    
}