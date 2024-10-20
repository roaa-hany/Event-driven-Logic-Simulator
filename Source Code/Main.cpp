#include<bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> inputs;
unordered_map<string, vector<string>> outputs;
vector<vector<string>> events;

// Trim the unnecessary whitespaces
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? str : str.substr(first, last - first + 1);
}

// Split the inputs and outputs between the brackets
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

void readVerilogFile(const string& verilog);
int evaluateValue(char out);
void readStimuliFile(string stimuliFile);
void writingInSimuliFile(string simuliFile);


int main() {
    string verilog = "circuit.txt";
    readVerilogFile(verilog);

    string stimuli = "stimuli.txt";
    readStimuliFile(stimuli);

    string simuli = "simuli.txt";
    writingInSimuliFile(simuli);

    return 0;
}

void readVerilogFile(const string& verilogFile) {
    ifstream verilog;
    verilog.open(verilogFile);

    if(!verilog.is_open()) {
        cerr << "Error opening file " << verilogFile << endl;
        return;
    }
    else {
        string line;

        while(getline(verilog, line)) {

            if(line.find("module") != string::npos || line.find("wire") != string::npos
               || line.find("endmodule") != string::npos || line.find("timescale") != string::npos) {
                continue;
               }

                size_t delayPos = line.find('#');

                string gateType = trim(line.substr(0, delayPos));

                string delay;
                if (delayPos != string::npos) {
                    size_t delayStart = line.find('(', delayPos) + 1;
                    size_t delayEnd = line.find(')', delayStart);
                    delay = trim(line.substr(delayStart, delayEnd - delayStart));

                    size_t ioStart = line.find('(', delayEnd) + 1;
                    size_t ioEnd = line.find(')', ioStart);
                    string ioString = line.substr(ioStart, ioEnd - ioStart);

                    vector<string> ioTokens = split(ioString, ',');

                    if(gateType == "and") {
                        outputs[ioTokens[0]].push_back("and");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                        }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                    else if(gateType == "nand") {
                        outputs[ioTokens[0]].push_back("nand");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                    }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                    else if(gateType == "or") {
                        outputs[ioTokens[0]].push_back("or");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                        }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                    else if(gateType == "nor") {
                        outputs[ioTokens[0]].push_back("nor");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                        }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                    else if(gateType == "xor") {
                        outputs[ioTokens[0]].push_back("xor");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                        }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                    else if(gateType == "xnor") {
                        outputs[ioTokens[0]].push_back("xnor");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                        }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                    else if(gateType == "not") {
                        outputs[ioTokens[0]].push_back("not");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                        }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                    else if(gateType == "buf") {
                        outputs[ioTokens[0]].push_back("buf");

                        for(int i = 1; i < ioTokens.size(); i++) {
                            inputs[ioTokens[i]].push_back(ioTokens[0]);
                            outputs[ioTokens[0]].push_back(ioTokens[i]);
                        }

                        outputs[ioTokens[0]].push_back(delay);
                    }
                }
            }
        }
    verilog.close();
}

int evaluateValue(string out) {
    string gate = outputs[out].at(0);

    int value = -1;                  //initial value of the output

    if(gate == "and") {

        int product = 1;
        for(int i = 1; i < outputs[out].size() - 1; i++) {
            string in = (outputs[out].at(i));
            product = product * stoi(inputs[in][inputs[in].size() - 1]);
            cout << inputs[in][inputs[in].size() - 1];
        }

        value = product;
    }

    else if(gate == "or") {

        int sum = 0;
        for(int i = 1; i < outputs[out].size() - 1; i++) {
            string in = (outputs[out].at(i));
            sum = sum + stoi(inputs[in][inputs[in].size() - 1]);
        }

        if(sum > 0) {
            value = 1;
        }
        else {
            value = 0;
        }
    }

    else if(gate == "nor") {

        int sum = 0;
        for(int i = 1; i < outputs[out].size() - 1; i++) {
            string in = (outputs[out].at(i));
            sum = sum + stoi(inputs[in][inputs[in].size() - 1]);
        }

        if(sum > 0) {
            value = 0;
        }
        else {
            value = 1;
        }
    }

    else if(gate == "nand") {

        int product = 1;
        for(int i = 1; i < outputs[out].size() - 1; i++) {
            string in = (outputs[out].at(i));
            product = product * stoi(inputs[in][inputs[in].size() - 1]);
        }

        if(product == 1) {
            value = 0;
        }
        else {
            value = 1;
        }
    }
    else if(gate == "xor") {

        int numberOfOnes = 0;
        for(int i = 1; i < outputs[out].size() - 1; i++) {
            string in = (outputs[out].at(i));

            if(inputs[in][inputs[in].size() - 1] == "1") {
                numberOfOnes++;
            }
        }

        if(numberOfOnes % 2 == 1) {
            value = 1;
        }
        else {
            value = 0;
        }
    }
    else if(gate == "xnor") {

        int numberOfOnes = 0;
        for(int i = 1; i < outputs[out].size() - 1; i++) {
            string in = (outputs[out].at(i));

            if(inputs[in][inputs[in].size() - 1] == "1") {
                numberOfOnes++;
            }
        }

        if(numberOfOnes % 2 == 1) {
            value = 0;
        }
        else {
            value = 1;
        }
    }
    else if(gate == "not") {

        string in = (outputs[out].at(1));

        if(inputs[in][inputs[in].size()-1] == "1") {
            value = 0;
        }
        else
            value = 1;
    }
    else if(gate == "buf") {

        string in = (outputs[out].at(1));

        if(inputs[in][inputs[in].size()-1] == "1") {
            value = 1;
        }
        else
            value = 0;
    }

    //needs to check whether this output is an input or not and if so, its value needs to be updated.
    if(inputs.find(out) != inputs.end()) {
        int size = inputs[out].size();
        inputs[out][size-1] = to_string(value);
    }

    return value;
}

void readStimuliFile(string stimuliFile) {
    ifstream stimuli(stimuliFile);

    if(!stimuli) {
        cerr << "Error opening the file: " << stimuliFile;
        return ;
    }
    else {
        string line;

        while (getline(stimuli, line)) {
            size_t delayPos = line.find('#') + 1;
            string delay = line.substr(delayPos, 1);

            size_t inputEnd = line.find('=');
            string inputName = trim(line.substr(delayPos + 1,inputEnd - (delayPos + 1)));

            size_t valueEnd = line.find(';');
            string inputValue = trim(line.substr(inputEnd + 1, valueEnd - (inputEnd + 1)));


            vector<string> event1;
            event1.push_back(delay);
            event1.push_back(inputName);
            event1.push_back(inputValue);

            events.push_back(event1);
        }
    }
}

void writingInSimuliFile(string simuliFile) {
    ofstream simuli;
    simuli.open(simuliFile);

    //initializing the inputs to be zero so that line 264 works properly
    for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        it->second.push_back("0");
    }

    if(simuli.is_open()) {

        while(!events.empty()) {
            vector<string> event = events.front();
            events.erase(events.begin());

            simuli<< event[0] << "," << event[1] << "," << event[2] <<endl;

            //this loop is there to handly many outputs connected to a single input
            for(int i = 0; i < inputs[event[1]].size() - 1; i++) {

                string output = inputs[event[1]][i];
                int size = outputs[output].size();

                int finaldelay = stoi(event[0]) + stoi(outputs[output][size-1]);//final event delay = event delay + gate delay;

                vector<string> newevent;
                newevent.push_back(to_string(finaldelay));
                newevent.push_back(output);
                newevent.push_back(to_string(evaluateValue(output)));

                for(int j = 0; j < events.size(); j++) {
                    int currentDelay = stoi(events[j][0]);

                    if(currentDelay > finaldelay) {
                        events.insert(events.begin() + j, newevent);
                        break;
                    }
                }
            }
        }
    }
    else {
        cerr << "Error opening the file: " << simuliFile;
    }
}