#include<bits/stdc++.h>
using namespace std;


string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? str : str.substr(first, last - first + 1);
}


void readVerilog(const string& verilogFile) {
    map<string, int> inputs, outputs;          // to store the name and value of each input and output

    ifstream in;
    in.open(verilogFile);                  // open the verilog description file

    if (!in.is_open()) {
        cout << "Error opening file " << verilogFile << endl;
        exit(1);
    }

    string line;
    while(getline(in, line)) {           // reads the file line by line
        line = trim(line);                    // trim any whitespaces in the line

        string word;
        vector<string> gates;

        if (line.empty() || line[0] == '/' || line[0] == '*')           //skips empty lines and comments
            continue;

        else {
            if (line.find("input") != string::npos) {
                line = line.substr(6);                            // Remove "input" from the line
                line = trim(line);                                   // Trim any whitespace after "input"
                line.pop_back();  // Remove the semicolon at the end

                // Split the remaining string by commas and add inputs to the map
                stringstream ss(line);
                string inputVar;
                while (getline(ss, inputVar, ',')) {
                    inputVar = trim(inputVar);                       // Trim each input name
                    inputs[inputVar] = -1;                          // Initialize the input value (default is -1)
                }
            }

            else if(line.find("wire") != string::npos) {
                line = line.substr(5);                            // Remove "wire" from the line
                line = trim(line);                                   // Trim any whitespace after "wire"
                line.pop_back();  // Remove the semicolon at the end

                // Split the remaining string by commas and add wires to the map
                stringstream ss(line);
                string wireVar;
                while (getline(ss, wireVar, ',')) {
                    wireVar = trim(wireVar);                          // Trim each output name
                    outputs[wireVar] = -1;                            // Initialize the wire value (default is -1)
                }
            }
            else if(line.find("output") != string::npos) {
                line = line.substr(7);                           // Remove "output" from the line
                line = trim(line);                                  // Trim any whitespace after "output"

                stringstream ss(line);
                string outputVar;
                while (getline(ss, outputVar, ';')) {
                    outputVar = trim(outputVar);
                    outputVar.pop_back();                           // Remove the semicolon at the end
                    outputs[outputVar] = -1;                        // Initialize the wire value (default is -1)
                }
            }

            else {
                int parenStart = line.find('(');                               //find the line that contains a gate declaration
                string gateType = line.substr(0, parenStart);              // get the gate type
                gateType = trim(gateType);                                       // trim the gate type from any whitespaces
                int parenEnd = line.find(')');                                 // find the end of the parameters list of the gate
                string args = line.substr(parenStart + 1, parenEnd - parenStart - 1);          //store the gate parameters

                vector<string> par;
                stringstream ss(args);
                string token;

                while (getline(ss, token, ',')) {
                    par.push_back(trim(token));  // Trim and add the token to the list
                }

                if(gateType == "and") {                    //if and gate, output = multiplication of inputs
                    int mult = 1;
                    for(int i = 1; i < par.size(); i++) {
                        mult = mult * inputs[par[i]];
                    }
                    outputs[par[0]] = mult;
                }
                else if(gateType == "or") {               // if or gate, output = summation of inputs
                    int sum = 0;
                    for(int i = 1; i < par.size(); i++) {
                        sum = sum + inputs[par[i]];
                    }
                    outputs[par[0]] = sum;
                }
                else if(gateType == "nand") {              // if nand gate, output = inversion of multiplication of inputs
                    int mult = 1;
                    for(int i = 1; i < par.size(); i++) {
                        mult = mult * inputs[par[i]];
                    }
                    outputs[par[0]] = !(mult);
                }
                else if(gateType == "nor") {              // if nor gate, output = inversion of summation of inputs
                    int sum = 0;
                    for(int i = 1; i < par.size(); i++) {
                        sum = sum + inputs[par[i]];
                    }
                    outputs[par[0]] = !(sum);
                }
                else if(gateType == "not") {             // if not gate, output = inversion of input
                    outputs[par[0]] = !inputs[par[1]];
                }
                else if(gateType == "buf") {            // if buffer gate, output = input
                    outputs[par[0]] = inputs[par[1]];
                }
            }
        }
    }
}

int main() {



    return 0;
}
