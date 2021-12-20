#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <utility>


int totWgt;
int wgtPerCont;
int numPkg;
int maxPkg;

int sumPkg(std::set<int> packages){
    int wgt = 0;
    for(int const& pkg : packages){
        wgt += pkg;
    }
    return wgt;
}

long long QE(std::set<int> compartment){
    long long qe = 1;
    for(int const& pkg : compartment){
        qe *= pkg;
    }
    return qe;
}

std::set<int> minimialNumberOfPackages(std::set<int> compartment, std::set<int> packagesLeft){
    if(sumPkg(compartment) == wgtPerCont){
        if(compartment.size() < maxPkg){
            maxPkg = compartment.size();
        }
        // std::cout << "Found wgt of " << wgtPerCont << " using " << compartment.size() << " packages" << std::endl;
        return compartment;
    } else if(packagesLeft.size()==0){
        return {};
    } else if(compartment.size() > maxPkg){
        return {};
    }
    int pkgToPlace = *(packagesLeft.begin());
    packagesLeft.erase(pkgToPlace);

    std::set<int> inBack = minimialNumberOfPackages(compartment,packagesLeft);
    compartment.insert(pkgToPlace);
    std::set<int> inFront = minimialNumberOfPackages(compartment,packagesLeft);

    if(inBack.size() == 0){
        if(inFront.size() == 0){
            return {};
        } else {
            return inFront;
        }
    } else if(inFront.size() == 0){
        return inBack;
    }
    if(inBack.size() < inFront.size()){
        return inBack;
    } else if(inFront.size() < inBack.size()){
        return inFront;
    } else {
        long long qeB = QE(inBack);
        long long qeF = QE(inFront);
        if(qeB < qeF){
            return inBack;
        } else {
            return inFront;
        }
    }
    return {};
}

int main(int argc, char* argv[]){
    std::set<int> packages;
    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            packages.insert(std::stoi(line));
        }
    }
    myfile.close();
    int numCont;
    if(argc == 3){
        numCont = std::stoi(argv[2]);
    } else {
        numCont = 3;
    }
    totWgt = sumPkg(packages);
    wgtPerCont = totWgt/numCont;
    numPkg = packages.size();
    maxPkg = numPkg/numCont;
    std::cout << "We have " << numPkg << " packages, with total weight " << totWgt << " " << wgtPerCont << " per compartment" << std::endl;

    std::set<int> bestFront = minimialNumberOfPackages({}, packages);
    std::cout << "The minium number of packages is " << bestFront.size() << " with QE " << QE(bestFront) << std::endl;
    std::cout << "Packages are:";
    for(int const& pkg : bestFront){
        std::cout << " " << pkg;
    }
    std::cout << std::endl;
}