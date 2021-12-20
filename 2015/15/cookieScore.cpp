#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

struct ingredient{
    std::string name;
    std::map<std::string, int> properties;
};

std::map<std::string, ingredient> ingredients;

std::vector<std::string> splitTask(std::string line){
    std::vector<std::string> split;
    int lastIndex = 0, newIndex = 0;
    std::string sep = " ";
    newIndex = line.find(sep, lastIndex);
    while ( newIndex != std::string::npos) {
        std::string part = line.substr(lastIndex,newIndex-lastIndex);
        split.push_back(part);
        lastIndex = newIndex+1;
        newIndex = line.find(sep, lastIndex);
    }
    std::string part = line.substr(lastIndex,std::string::npos);
    split.push_back(part);
    return split;
}

long long score(std::map<std::string, int> recepie){
    long long scoreValue = 1;
    std::map<std::string, int> scorePerProp;
    for(auto const& [ing, quantity] : recepie){
        for(auto const& [prop, val] : ingredients[ing].properties){
            
            if(prop != "calories") {
                if(scorePerProp.find(prop) == scorePerProp.end()){
                    scorePerProp[prop] = 0;
                }
                scorePerProp[prop] += quantity * val;
            }
        }
    }
    for(auto const& [prop, val] : scorePerProp){
        if (val > 0){
            scoreValue *= val;
        } else{
            scoreValue = 0;
        }
    }
    return scoreValue;
}

long long scoreWithCal(std::map<std::string, int> recepie){
    int calories = 0;
    for(auto const& [ing, quantity] : recepie){
        for(auto const& [prop, val] : ingredients[ing].properties){
            if(prop == "calories") {
                calories += quantity * val;
            }
        }
    }
    std::cout << calories << std::endl;
    if(calories > 500) {
        return 0;
    } else {
        return score(recepie);
    }
}

int main(int argc, char* argv[]){
    std::string line;
    std::ifstream myfile;
    std::map<std::string, std::map<std::string, int>> constChange;
    std::set<std::string> addRemove = {"add", "remove"};
    std::set<std::string> ingList;
    std::map<std::string, int> recepie;
    long long totUsed = 0;
    myfile.open(argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            std::vector<std::string> splitLine = splitTask(line);
            ingredient I;
            int i = 0;
            while(i < splitLine.size()){
                //Check for name
                std::size_t indxCol = splitLine[i].find(':');
                if(indxCol != std::string::npos){
                    I.name = splitLine[i].substr(0,indxCol);
                } else {
                    std::string name = splitLine[i];
                    std::string value = splitLine[i+1];
                    std::size_t indxCom = value.find(',');
                    if(indxCom != std::string::npos){
                        value = value.substr(0,indxCom);
                    }
                    int val = std::stoi(value);
                    I.properties[name] = val;
                    i+=1;
                }
                i += 1;
            }
            std::cout << I.name << std::endl;
            for (auto const& [name, val] : I.properties){
                std::cout << name << " " << val << " ";
            }
            std::cout << std::endl;
            ingredients[I.name] = I;
            ingList.insert(I.name);
        }
    }
    std::map<std::string, int> add3;
    std::map<std::string, int> add5;
    add3["Sprinkles"] = 3;
    add3["PeanutButter"] = -1;
    add3["Frosting"] = -1;
    add3["Sugar"] = -1;
    add5["Sprinkles"] = 5;
    add5["PeanutButter"] = -1;
    add5["Frosting"] = -4;
    add5["Sugar"] = 0;
    constChange["3"] = add3;
    constChange["5"] = add5;
    std::map<std::string, int> add3p5;
    std::map<std::string, int> add3m5;
    for(std::string const& name : ingList){
        add3p5[name] = add3[name] + add5[name];
        add3m5[name] = add3[name] - add5[name];
    }
    constChange["3+5"] = add3p5;
    constChange["3-5"] = add3m5;
    myfile.close();
    for(auto const& [name, I] : ingredients){
        recepie[name] = 25;
    }

    bool running = true;
    while(running){
        std::map<std::string, long long> newValues;
        newValues["same"] = score(recepie);
        for(std::string const& ing1 : ingList){
            for(std::string const& ing2 : ingList){
                if(ing1 != ing2){
                    //TEST remove ing1 add ing2;
                    recepie[ing1] -= 1;
                    recepie[ing2] += 1;
                    // TODO Check that they don't become negative.
                    std::string newIng = ing1 + ':' + ing2;
                    newValues[newIng] = score(recepie);
                    recepie[ing1] += 1;
                    recepie[ing2] -= 1;
                }
            }
        }
        long long maxVal = 0;
        std::string newString;
        for(auto const& [newIng, val] : newValues){
            if(val > maxVal){
                maxVal = val;
                newString = newIng;
            }
        }
        if(newString == "same"){
            running = false;
        } else{
            std::size_t indxCol = newString.find(':');
            std::string ing1 = newString.substr(0,indxCol);
            std::string ing2 = newString.substr(indxCol + 1, newString.size() - indxCol);
            // std::cout << newString << " " << ing1 << " " << ing2 << std::endl;
            recepie[ing1] -= 1;
            recepie[ing2] += 1;
        }

    }

    std::cout << "Answer part A: Score for recepie ";
    for(auto const& [name, val] : recepie){
        std::cout << name << ':' << val << " ";
    }
    std::cout << "is " << score(recepie) << std::endl;

    // for(auto const& [name, I] : ingredients){
    //     recepie[name] = 25;
    // }
    recepie["Sprinkles"] = 25;
    recepie["PeanutButter"] = 25;
    recepie["Frosting"] = 25;
    recepie["Sugar"] = 25;

    running = true;
    while(running){
        std::map<std::string, long long> newValues;
        newValues["same"] = scoreWithCal(recepie);
        for(std::string const& change : addRemove){
            for(auto const& [number, diffMap] : constChange){
                for(auto const& [ing, ingChange] : diffMap){
                    if(change == "add"){
                        recepie[ing] += ingChange;
                    } else {
                        recepie[ing] -= ingChange;
                    }
                }
                std::string changeString = change + ":" + number;
                newValues[changeString] = scoreWithCal(recepie);
                for(auto const& [ing, ingChange] : diffMap){
                    if(change == "add"){
                        recepie[ing] -= ingChange;
                    } else {
                        recepie[ing] += ingChange;
                    }
                }
            }
        }

        long long maxVal = 0;
        std::string newString;
        for(auto const& [newIng, val] : newValues){
            if(val > maxVal){
                maxVal = val;
                newString = newIng;
            }
        }
        if(newString == "same"){
            running = false;
        } else{
            std::size_t indxCol = newString.find(':');
            std::string diffType = newString.substr(0,indxCol);
            std::string diffNum = newString.substr(indxCol + 1, newString.size() - indxCol);
            for(auto const& [ing, ingChange] : constChange[diffNum]){
                if(diffType == "add"){
                    recepie[ing] += ingChange;
                } else {
                    recepie[ing] -= ingChange;
                }
            }
        }
        for(auto const& [name, val] : recepie){
            std::cout << name << ':' << val << " ";
        }
        std::cout << "is " << score(recepie) << std::endl;

    }

    std::cout << "Answer part B: Score for recepie ";
    for(auto const& [name, val] : recepie){
        std::cout << name << ':' << val << " ";
    }
    std::cout << "is " << score(recepie) << std::endl;

    return 0;
}