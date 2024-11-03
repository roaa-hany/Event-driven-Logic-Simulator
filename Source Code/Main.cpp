#include<bits/stdc++.h>
#include<string>
#include<iostream>

using namespace std;

unordered_map<string, vector<string>> inputs;                //stores each input name, and its corresponding vector of outputs associated with it as well as its value at the end of the vector
unordered_map<string, vector<string>> outputs;               //stores each output name, and its corresponding vector of gatName, inputs associated with it, and the delay of the gate at the end of the vector
vector<vector<string>> events;                               // stores the events where each event is a vector of inputName, delay, and changed value
unordered_map<string, vector<string>> inputsValue;           //to store the values of the inputs over time needed to draw the waveform
unordered_map<string, vector<string>> outputsValue;          //to store the values of the outputs over time needed to draw the waveform

//removes unnecessary whitespaces from a string
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? str : str.substr(first, last - first + 1);
}

// slices the string depending on the delimiter and symbol chosen for slicing and parcing and returns it
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

void readVerilogFile(const string& verilog); // Reads the verilog file containing the module description
int evaluateValue(char out); //evaluates the value based on each gate and returns the value as well as inserting it at the last element of the vector of the map of inputs
void readStimuliFile(string stimuliFile); //Reads the stimuli file and creates events using the events vector
void writingInSimuliFile(string simuliFile); //checks if the current output is the final output or an intermediate event to print the events into the simuli file
void writeWaveformSyntax(const string& filename); // Writes WaveDrom-compatible waveform syntax


int main() {
    string verilog = "circuit.txt";
    readVerilogFile(verilog);

    string stimuli = "stimuli.txt";
    readStimuliFile(stimuli);

    string simuli = "simuli.txt";
    writingInSimuliFile(simuli);

    string waveform = "waveDrom.txt";
    writeWaveformSyntax(waveform);

    return 0;
}

void readVerilogFile(const string& verilogFile) {
    ifstream verilog;
    verilog.open(verilogFile);

    if(!verilog.is_open()) { // detects an error if the file does not open
        cerr << "Error opening file " << verilogFile << endl;
        return;
    }
    else {
        string line;

        while(getline(verilog, line)) {

            // ignores unneeded lines
            if(line.find("module") != string::npos || line.find("wire") != string::npos
               || line.find("endmodule") != string::npos || line.find("timescale") != string::npos
               || line.find("input") != string::npos || line.find("output") != string::npos) {
                continue; //skips upon finding the keywords
               }

                size_t delayPos = line.find('#'); // find the position of the delay

                string gateType = trim(line.substr(0, delayPos)); //detects the gate type

                string delay;
                if (delayPos != string::npos) {
                    size_t delayStart = line.find('(', delayPos) + 1;
                    size_t delayEnd = line.find(')', delayStart);
                    delay = trim(line.substr(delayStart, delayEnd - delayStart));       //gets the value of the delay

                    size_t ioStart = line.find('(', delayEnd) + 1;
                    string gateName = trim(line.substr(delayEnd, ioStart - delayEnd));

                    size_t ioEnd = line.find(')', ioStart);
                    string ioString = line.substr(ioStart, ioEnd - ioStart);

                    //gets the inputs and outputs of each gate to store them one at a time
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

    string gate = outputs[out].at(0);               //gets the gate type to determine how to calculate the output

    bool validInputs = true;

    for(int i = 1; i < outputs[out].size() - 1; i++) {
        string in = (outputs[out].at(i));
        if(stoi(inputs[in][inputs[in].size() - 1]) == -1) // if the input value is still -1, this means it is not valid as it hasn't received a valid value yet
            validInputs = false;
    }

    if(validInputs) {
        // if all the inputs associated with this output are valid, start calculating its value
        int value = -1;                  //initialize the output value to -1

        //if and gate, multiply its inputs' values
        if(gate == "and") {
            int product = 1;
            for(int i = 1; i < outputs[out].size() - 1; i++) {
                string in = (outputs[out].at(i));
                product = product * stoi(inputs[in][inputs[in].size() - 1]);
                cout << inputs[in][inputs[in].size() - 1];
            }
            value = product;
        }

        //if or gate, sum its inputs' values and if the sum is > 0, it means there is at least one input with a value of 1
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

        //if nor, reverse the values calculated in or
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

        //if nand, reverse the values calculated in and
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

        //if xor, it returns 1 if the number of inputs with value of 1 are odd, otherwise returns 0
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

        //if xnor, reverse the values calculated in xor
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

        //if not, just reverse the value of the input
        else if(gate == "not") {

            string in = (outputs[out].at(1));

            if(inputs[in][inputs[in].size()-1] == "1") {
                value = 0;
            }
            else
                value = 1;
        }

        //if buffer, return the value of the input as is
        else if(gate == "buf") {
            string in = (outputs[out].at(1));

            if(inputs[in][inputs[in].size()-1] == "1") {
                value = 1;
            }
            else
                value = 0;
        }

        return value;              //return the calculated value of the output according to the gate type
    }

    else
        return -1;           // if the input values are not valid, return -1
}

void readStimuliFile(string stimuliFile) {
    ifstream stimuli(stimuliFile);

    if(!stimuli) {
        cerr << "Error opening the file: " << stimuliFile;     //cout an error if file is not opened
        return ;
    }
    else {
        string line;
        int currentTime = 1;

        while (getline(stimuli, line)) {
            // read the file line by line

            //get the delay value
            size_t delayPos = line.find('#') + 1;
            size_t delayfinalpos = delayPos;

            while(line[delayfinalpos] != ' ') {
                delayfinalpos++;
            }

            string delay = line.substr(delayPos, delayfinalpos-delayPos);

            //get the name of the input that needs to be changed
            size_t inputEnd = line.find('=');
            string inputName = trim(line.substr(delayfinalpos,inputEnd - (delayfinalpos)));

            //get the new value of the input
            size_t valueEnd = line.find(';');
            string inputValue = trim(line.substr(inputEnd + 1, valueEnd - (inputEnd + 1)));

            //creates a vector of the event and pushes the data related to each event onto the vector
            vector<string> event1;
            event1.push_back(delay);
            event1.push_back(inputName);
            event1.push_back(inputValue);

            //add the event to the vector of events
            events.push_back(event1);

            //maintain the old values of the inputs while they are not changed
            while (currentTime < stoi(delay)) {
                for(auto it = inputsValue.begin(); it != inputsValue.end(); it++) {
                    it->second.push_back(".");
                }
                currentTime++;
            }

            // Now, at the specific event time, update the input value
            inputsValue[inputName].push_back(inputValue);
        }
    }
}

void writingInSimuliFile(string simuliFile) {
    ofstream simuli;
    simuli.open(simuliFile);

    //initializing the inputs' values to -1 so that each input get a value to indicate if it is valid or not
    for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        it->second.push_back("-1");
    }

    if(simuli.is_open()) {
        int currentTime = 1;

        //reade the existing events
        while(!events.empty()) {
            //read each event one at a time and remove it from the existing events
            vector<string> event = events.front();
            events.erase(events.begin());

            //checks if the output is the final output or the intermediate output
            if(inputs[event[1]].empty()) {
                simuli << event[0] << "," << event[1] << "," << event[2] << endl; //if the vector of outputs is empty, then this is the final output and will be outputted

                // update the output value to draw the waveform
                while(currentTime < stoi(event[0])) {
                    for(auto it = outputs.begin(); it != outputs.end(); it++){
                        if(outputsValue[it->first].empty()) {
                            outputsValue[it->first].push_back("x");
                        }
                        else {
                            outputsValue[it->first].push_back(".");
                        }
                    }
                    currentTime++;
                }
                outputsValue[event[1]].push_back(event[2]);
            }

            //if the output is an input for another gate, print it, then create a newEvent with this output
            else {
                simuli << event[0] << "," << event[1] << "," << event[2] <<endl;

                int inputssize= inputs[event[1]].size();

                //saves the input value from the event vector to the inputs map
                inputs[event[1]][inputssize-1] = event[2];

                //loops over all outputs associated with the input in the event
                for(int i = 0; i < inputs[event[1]].size() - 1; i++) {
                    string output = inputs[event[1]][i];
                    int size = outputs[output].size();

                    int finaldelay = stoi(event[0]) + stoi(outputs[output][size-1]);       //The final delay is the sum of the gate delay and the input delay

                    vector<string> newevent; //creates a new event and push the delay and output
                    newevent.push_back(to_string(finaldelay));
                    newevent.push_back(output);
                    newevent.push_back(to_string(evaluateValue(output))); //push the value of the output

                    if(newevent[2] != "-1") {
                        bool added = false;
                        for(int j = 0; j < events.size(); j++) {
                            int currentDelay = stoi(events[j][0]);
                            if(currentDelay > finaldelay) {
                                events.insert(events.begin() + j, newevent);
                                added = true;
                                break;
                            }
                        }

                        //if not added, add it to the end as the final event
                        if(!added) {
                            events.push_back(newevent);
                        }
                    }
                }
            }
        }
    }
    //if file is not opened, cout an error
    else {
        cerr << "Error opening the file: " << simuliFile;
    }
}

void writeWaveformSyntax(const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening the file: " << filename << endl;
        return;
    }

    // Find the maximum length among all input and output vectors
    size_t maxLength = 0;
    for (const auto& pair : inputsValue) {
        maxLength = max(maxLength, pair.second.size());
    }
    for (const auto& pair : outputsValue) {
        maxLength = max(maxLength, pair.second.size());
    }

    // Make all the vectors have the same length of waveform
    for (auto& pair : inputsValue) {
        while (pair.second.size() < maxLength) {
            pair.second.push_back(".");
        }
    }

    for (auto& pair : outputsValue) {
        while (pair.second.size() < maxLength) {
            pair.second.push_back(".");
        }
    }

    // Start writing to the WaveDrom file
    outFile << "{\n"
            << "  signal: [\n"
            << "    ['Outputs',\n";

    // Write the outputs section
    for (auto i = outputsValue.begin(); i != outputsValue.end(); i++) {
        outFile << "      { name: \"" << i->first << "\", wave: \"";

        // Adding wave values for outputs over time
        for (const auto& value : i->second) {
            outFile << (value == "1" ? "1" : (value == "0" ? "0" : (value == "." ? "." : "x")));
        }
        outFile << "\" },\n";
    }

    outFile << "    ],\n"
            << "    ['Inputs',\n";

    // Write the inputs section
    for (auto i = inputsValue.begin(); i != inputsValue.end(); i++) {
        outFile << "      { name: \"" << i->first << "\", wave: \"";

        // Adding wave values for inputs over time
        for (const auto& value : i->second) {
            outFile << (value == "1" ? "1" : (value == "0" ? "0" : (value == "." ? "." : "x")));
        }
        outFile << "\" },\n";
    }

    // Close the signal array and add configuration settings
    outFile << "    ]\n"
            << "  ],\n"
            << "  'config': { 'hscale': 1 },\n"
            << "  'head': { 'text': 'Waveform of the Simulator' },\n"
            << "  'foot': { 'tick': 0, 'every': 1 }\n"
            << "}\n";

    outFile.close();
}

