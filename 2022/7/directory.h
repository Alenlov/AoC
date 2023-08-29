#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <map>

class Directory
{
    private :
        int localSize;
        int totalSize;
        int numSmallWithin;
        std::string name;
        Directory *root;
        std::map<std::string, Directory *> subDirs;
        std::map<std::string, int> files;

    public :
        // Constructor
        Directory(const std::string name, Directory *root = NULL);

        // Set size
        void setSize();

        // Get size
        int getSize() const;

        // Add file
        void addFile(const std::string name, const int size);

        // add sub dir
        void addSubDir(const std::string name);

        // get sub dir
        std::map<std::string, Directory *> getSubDir() const;

        // get sub dir by name
        Directory * getSubDirByName(std::string name);

        Directory * getRoot() const;

        int calcSmall();

        // print
        void print();
};

#endif