#include <string>
#include <iostream>
#include <vector>
#include <set>
int minLetter = int('a');
int maxLetter = int('z');

std::set<int> notOk = {int('i'), int('o'), int('l')};

void nextPassword(std::vector<int> &password, int inc){
    bool addOne = true;
    for(int i = password.size() ; i > -1 ; --i){
        if(i > inc){
            password[i] = minLetter;
        } else {
            int val = password[i];
            if(addOne){
                addOne = false;
                val += 1;
                if(val > maxLetter){
                    val = minLetter;
                    addOne = true;
                }
            }
            password[i] = val;
        }
    }

    return;
}

int isValid(std::vector<int> password){
    int passLen = password.size();
    bool isValid = false;
    bool oneDouble = false;
    bool twoDouble = false;
    bool threeIncreased = false;
    int i = 0;
    while(i < password.size()){
        int curr = password[i];
        // std::cout << "Checking " << char(curr) << std::endl;
        if(i < password.size()-2){
            if ( (curr+1 == password[i+1]) && (curr+2 == password[i+2]) ){
                // std::cout << "Set three increased double!" << std::endl;
                threeIncreased = true;
            }
        }
        if(i < password.size() - 1){
            if (curr == password[i+1]){
                if(oneDouble){
                    // std::cout << "Set second double!" << std::endl;
                    twoDouble = true;
                }else{
                    // std::cout << "Set first double!" << std::endl;
                    oneDouble = true;
                }
                
            }
        }
        if(notOk.find(curr) != notOk.end()){
            // std::cout << "Return 1: " << i << std::endl;
            return i;
        }
        int numLeft = passLen - i;
        if( ((!oneDouble) && (!threeIncreased)) && (numLeft == 5)){
            // std::cout << "Return 2: " << i << " we have " << char(curr) << std::endl;
            return i+1;
        } else if ((!oneDouble) && (numLeft == 4)) {
            // std::cout << "Return 3: " << i << " we have " << char(curr) << std::endl;
            return i+1;
        } else if ((!threeIncreased) && (numLeft == 3)) {
            // std::cout << "Return 4: " << i << " we have " << char(curr) << std::endl;
            return i+1;
        } else if ((!twoDouble) && (numLeft == 2)) {
            // std::cout << "Return 5: " << i << " we have " << char(curr) << std::endl;
            return i+1;
        }
        i += 1;
    }
    if(twoDouble && threeIncreased){
        return passLen;
    }
    return passLen - 1;
}

int main(int argc, char *argv[]) {
    std::string startPassword = argv[1];
    std::vector<int> password;
    for(int i = 0; i < startPassword.length(); i++){
        password.push_back(int(startPassword[i]));
    }
    bool foundPassword = false;
    int toInc = password.size()-1;
    int tested = 0;
    while(!foundPassword){
        nextPassword(password, toInc);
        
        toInc = isValid(password);
        if(toInc == password.size()){
            foundPassword = true;
        }
        for(int i = 0; i < password.size(); i++){
            std::cout << char(password[i]);
        }
        std::cout << " char to increase is " << toInc << std::endl;
        tested += 1;
        // if(tested > 10) {
        //     foundPassword = true;
        // }
    }
    std::cout << "Answer part A: The next password is ";
    for(int i = 0; i < password.size(); i++){
        std::cout << char(password[i]);
    }
    std::cout << std::endl;
    foundPassword = false;
    toInc = password.size()-1;
    while(!foundPassword){
        nextPassword(password, toInc);
        
        toInc = isValid(password);
        if(toInc == password.size()){
            foundPassword = true;
        }
        for(int i = 0; i < password.size(); i++){
            std::cout << char(password[i]);
        }
        std::cout << " char to increase is " << toInc << std::endl;
        tested += 1;
        // if(tested > 10) {
        //     foundPassword = true;
        // }
    }
    std::cout << "Answer part B: The next password is ";
    for(int i = 0; i < password.size(); i++){
        std::cout << char(password[i]);
    }
    std::cout << std::endl;
    return 0;
}