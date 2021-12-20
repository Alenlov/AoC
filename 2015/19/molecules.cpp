#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <vector>


std::map<std::string, std::set<std::string>> transforms;
std::map<std::string, std::string> revTrans;

std::set<std::string> oneStep(std::set<std::string> currMolSet){
    std::set<std::string> possibleMolecules;
    for(std::string const& currMol : currMolSet){
        for(int i = 0; i < currMol.size(); i++){
            std::string oneStep = currMol.substr(i,1);
            std::string twoStep = "";
            if(i < currMol.size()-1){
                twoStep = currMol.substr(i,2);
            }
            if(transforms.find(oneStep) != transforms.end()){
                for(std::string const& rhs : transforms[oneStep]){
                    std::string newMol = currMol.substr(0,i) + rhs + currMol.substr(i+1,currMol.size());
                    possibleMolecules.insert( newMol );
                }
            }
            if(transforms.find(twoStep) != transforms.end()){
                for(std::string const& rhs : transforms[twoStep]){
                    std::string newMol = currMol.substr(0,i) + rhs + currMol.substr(i+2,currMol.size());
                    possibleMolecules.insert( newMol );
                }
            }
        }
    }
    return possibleMolecules;
}

std::set<std::string> reverseStep(std::set<std::string> currMolSet){
    std::set<std::string> prevMolecules;
    for(std::string const& currMol : currMolSet){
        for(auto const& [rhs, lhs] : revTrans){
            std::size_t startIndx = 0;
            std::size_t indx = currMol.find(rhs,startIndx);
            while(true){
                if (indx == std::string::npos) {
                    break;
                }
                startIndx = indx + 1;
                std::string prevMol = currMol.substr(0,indx) + lhs + currMol.substr(indx + rhs.size(), currMol.size());
                bool possible = true;
                // if ( (prevMol.find("e") != std::string::npos) && (prevMol.size() > 1) ){
                //     possible = false;
                // }
                // if ( (prevMol.find("CRn") != std::string::npos) && (prevMol.find("CRn") != 0)) {
                //     possible = false;
                // }
                if(possible){
                    prevMolecules.insert(prevMol);
                }
                indx = currMol.find(rhs,startIndx);
            }
        }
    }
    
    return prevMolecules;
}

std::vector<std::string> splitAr(std::string input){
    std::vector<std::string> partsToReduce;

    std::size_t indxAr = input.find("Ar");
    std::size_t prevIndx = 0;
    while(indxAr < input.size()){
        std::string part = input.substr(prevIndx,indxAr-prevIndx+2);
        // std::cout << part << " ";
        partsToReduce.push_back(part);
        prevIndx = indxAr + 2;
        indxAr = input.find("Ar", prevIndx);
        
    }
    std::string part = input.substr(prevIndx,input.size());
    // std::cout << part << " ";
    partsToReduce.push_back(part);
    return partsToReduce;
}

std::pair<std::string, int> reduceVec(std::vector<std::string> input){
    int iterations = 0;
    std::string reducedString = "";
    for (std::string const& part : input){
        std::set<std::string> partB = {part};
        int itr = 0;
        bool running = true;
        while(running){
            std::set<std::string> newPartB = reverseStep(partB);
            
            if(newPartB.size() == 0){
                running = false;
            } else {
                partB = newPartB;
                itr += 1;
            }
        }
        iterations += itr;
        if(partB.size() > 1){
            std::cout << "MULTIPLE";
        }
        for(std::string part2 : partB){
            // std::cout << "Reduced " << part << " to " << part2 << " in " << itr << " iterations." << std::endl;
            reducedString += part2;
        }

    }
    // std::cout << reducedString  << std::endl;
    return std::make_pair(reducedString,iterations);
}


std::pair<std::string, int> reverseStepPair(std::string currMol){
    int steps = 0;
    for(auto const& [rhs, lhs] : revTrans){
        std::size_t startIndx = 0;
        std::size_t indx = currMol.find(rhs,startIndx);
        while(true){
            if (indx == std::string::npos) {
                break;
            }
            startIndx = indx + lhs.size();
            currMol = currMol.substr(0,indx) + lhs + currMol.substr(indx + rhs.size(), currMol.size());
            indx = currMol.find(rhs,startIndx);
            steps += 1;
        }
    }
    return std::make_pair(currMol, steps);
}

int main(int argc, char* argv[]){

    std::string sep = " => ";
    std::string line;
    std::string startingMolecule;
    std::ifstream myfile;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile, line)){
            std::size_t indx = line.find(sep);
            if(indx != std::string::npos){
                std::string lhs = line.substr(0,indx);
                std::string rhs = line.substr(indx+sep.size(),line.size());
                // std::cout << lhs << sep << rhs << std::endl;
                if(transforms.find(lhs) == transforms.end()){
                    transforms[lhs] = {rhs};
                } else {
                    transforms[lhs].insert(rhs);
                }
                revTrans[rhs] = lhs;
            } else if (line.size() > 0) {
                startingMolecule = line;
            }
        }
    }
    myfile.close();
    


    std::set<std::string> possibleMolecules = oneStep({startingMolecule});
    
    std::cout << "Answer part A: After 1 step there are " << possibleMolecules.size() << " different molecules!" << std::endl;

    // startingMolecule = "HF";

    bool running = true;
    int totItr = 0;
    while(running){
        std::vector<std::string> partsToReduce = splitAr(startingMolecule);
        // for(std::string const& s : partsToReduce){
        //     std::cout << s << " : ";
        // }
        // std::cout << std::endl;
        std::pair<std::string, int> output = reduceVec(partsToReduce);
        startingMolecule = output.first;
        totItr += output.second;
        // std::cout << startingMolecule << std::endl;
        if(startingMolecule == "e" || startingMolecule.size() == 1){
            running = false;
        }
    }
    std::cout << "Answer part B: Starting with e, we got " << startingMolecule << " after " << totItr << " iterations!" << std::endl;
    return 0;
}