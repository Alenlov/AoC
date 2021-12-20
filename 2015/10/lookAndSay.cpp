#include <iostream>
#include <string>

std::string newString(std::string oldString) {
    std::string newStr = "";
    int i = 0;
    while(i < oldString.size()) {
        char curr = oldString[i];
        int numCurr = 1;
        // LOOK ahead
        int j = i + 1;
        while(j < oldString.size()){
            if(curr == oldString[j]){
                numCurr += 1;
                j += 1;
            } else {
                break;
            }
        }
        newStr += std::to_string(numCurr) + curr;

        i = j;
    }

    return newStr;

}

int main(int argc, char *argv[]) {
    std::string start = argv[1];
    for(int i = 0; i < 40; i++){
        start = newString(start);
    }
    std::cout << "Answer part A: AFter 40 iteration the string has length " << start.length() << std::endl;
    for(int i = 0; i < 10; i++){
        start = newString(start);
    }
    std::cout << "Answer part B: AFter 50 iteration the string has length " << start.length() << std::endl;
    return 0;
}