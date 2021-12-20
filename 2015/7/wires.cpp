#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <set>
#include <vector>

const int maxVal = 65535;

class Wire {
        bool evaluated = false;
        bool isNumber = true;
        int value;
        int input;
        std::string name;
    public:
        Wire() {}
        Wire(std::string name);
        void setInput(int input) {
            this->input = input;
        }
        int getInput() {return input;}
        void evaluate();
        int getValue();
        void setValue(int val);
        std::string getName() {return name;}
        void reset();
};

class Gate {
        int identifier;
        std::string type;
        std::pair<std::string, std::string> inputs;
        std::string output;
    public:
        void evaluate();
        Gate() {}
        Gate(int id, std::string type, std::pair<std::string, std::string> inputs, std::string output);
};

std::map<std::string, Wire> wires;
std::map<int, Gate> gates;

Wire::Wire(std::string name) {
            this->name = name;
            int number;
            try { 
                number = stoi(name);
            } catch (...) {
                isNumber = false;
            }
            if (isNumber) {
                evaluated = true;
                value = number;
            }
        }

void Wire::reset() {
    if (!isNumber) {
        evaluated = false;
    }
}

void Wire::evaluate() {
    if (!evaluated) {
        gates.at(input).evaluate();
    }
}

void Wire::setValue(int val) {
    value = val;
    evaluated = true;
}

int Wire::getValue(){
    //std::cout << this->name << std::endl;

    if (!evaluated) {
        evaluate();
    }
    return this->value;
}

Gate::Gate(int id, std::string type, std::pair<std::string, std::string> inputs, std::string output)  {
    identifier = id;
    this->type = type;
    this->inputs = inputs;
    this->output = output;
}

// Gate types, AND, OR, NOT, LSHIFT, RSHIFT, PASS ON
void Gate::evaluate() {
    int value;
    if (type == "PASS") {
        value = wires.at(inputs.first).getValue();
    } else if (type == "NOT") {
        value = (wires.at(inputs.first).getValue() ^ maxVal);
    } else if (type == "AND") {
        value = (wires.at(inputs.first)).getValue() & (wires.at(inputs.second)).getValue();
    } else if (type == "OR") {
        value = wires.at(inputs.first).getValue() | (wires.at(inputs.second)).getValue();
    } else if (type == "LSHIFT") {
        value = wires.at(inputs.first).getValue() << wires.at(inputs.second).getValue();
        value &= maxVal;
    } else if (type == "RSHIFT") {
        value = wires.at(inputs.first).getValue() >> wires.at(inputs.second).getValue();
        value &= maxVal;
    } else {
        std::cout << "ERROR UNKNOWN GATE TYPE! " << type << " at identifier: " << identifier << std::endl;
        return;
    }
    wires.at(output).setValue(value);
    return;
}



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

int main(int argc, char *argv[]) {
    
    std::string line;
    std::ifstream myfile;
    myfile.open(argv[1]);
    int id = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            std::string type;
            std::string output;
            std::pair<std::string, std::string> inputs;
            std::vector<std::string> operations = splitTask(line);
            if (operations.size() == 3) {
                type = "PASS";
                inputs = std::make_pair(operations.at(0), operations.at(0));
                output = operations.at(2);
            } else if (operations.size() == 4) {
                type = operations.at(0);
                inputs = std::make_pair(operations.at(1), operations.at(1));
                output = operations.at(3);
            } else {
                type = operations.at(1);
                inputs = std::make_pair(operations.at(0), operations.at(2));
                output = operations.at(4);
            }
            gates[id] = Gate(id, type, inputs, output);
            if (wires.find(output) == wires.end()) {
                wires[output] = Wire(output);
                wires[output].setInput(id);
            } else {
                wires[output].setInput(id);
            }
            if (wires.find(inputs.first) == wires.end()) {
                wires[inputs.first] = Wire(inputs.first);
            }
            if (wires.find(inputs.second) == wires.end()) {
                wires[inputs.second] = Wire(inputs.second);
            }

            id++;
        }
    }
    myfile.close();
    /*for (auto const& x : wires) {
        std::cout << x.first << ": " << wires[x.first].getValue() << std::endl;
    }
    std::cout << maxVal << " is the maxVal, xor with " << 123 << " gives " << (maxVal ^ 123) << std::endl;*/
    int valueA = wires["a"].getValue();
    for (auto const& x: wires) {
        wires[x.first].reset();
    }
    wires["b"].setValue(valueA);
    int valueB = wires["a"].getValue();
    std::cout << "Answer part A: The value on wire a is " << valueA << std::endl;
    std::cout << "Answer part B: The value on wire a is " << valueB << std::endl;
    return 0;
}