#include<bits/stdc++.h>
#include<string>
#include<iostream>
using namespace std;

unordered_map<string, vector<string>> inputs;
unordered_map<string, vector<string>> outputs;
vector<vector<string>> events;

// Parces the line into the string with white spaces and removes such whitespaces from the string and returns the string
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

void readVerilogFile(const string& verilog); // Reads the the verilog file containing the module description
int evaluateValue(char out); //evaluates the value based on each gate and returns the value as well as inserting it at the last element of the vector of outputs in the map of inputs
void readStimuliFile(string stimuliFile); //Reads the stimuli file and creates events using the events vector
void writingInSimuliFile(string simuliFile); //checks if the current output is the final output or an intermediate event


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

    if(!verilog.is_open()) { // detects an error if the file does not open
        cerr << "Error opening file " << verilogFile << endl;
        return;
    }
    else {
        string line;

        while(getline(verilog, line)) {

            if(line.find("module") != string::npos || line.find("wire") != string::npos // ignores certain keywords
               || line.find("endmodule") != string::npos || line.find("timescale") != string::npos) {
                continue; //continues upon finding the kewords
               }

                size_t delayPos = line.find('#'); // find the position of the delay

                string gateType = trim(line.substr(0, delayPos)); //detects the gate type after parsing and slicing using the position of the delay

                string delay;
                if (delayPos != string::npos) {
                    size_t delayStart = line.find('(', delayPos) + 1;
                    size_t delayEnd = line.find(')', delayStart);
                    delay = trim(line.substr(delayStart, delayEnd - delayStart));

                    size_t ioStart = line.find('(', delayEnd) + 1;
                    size_t ioEnd = line.find(')', ioStart);
                    string ioString = line.substr(ioStart, ioEnd - ioStart);

                    vector<string> ioTokens = split(ioString, ',');
                    //cout<<"the delay is " <<delay<<endl;
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
    verilog.close(); //closes the file and the last section of code puts the delay in the last element of the vector of outputs in the map of inputs and loops to place all inputs in the map as well as outputs in the vector of strings
}                     // stores the inputs inside the vector of string in the map of outputs

int evaluateValue(string out) {
    string gate = outputs[out].at(0);
    bool validinputs=true;
    for(int i = 1; i < outputs[out].size() - 1; i++) {
        string in = (outputs[out].at(i));
        if(stoi(inputs[in][inputs[in].size() - 1])==-1) // checks if the value of input is equal to -1, if so then the input is not valid and is empty
            validinputs=false;
    }
    if(validinputs) { // if the input value is true
        int value = -1;                  //sets the value to the initial value of the output

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
        cout<<"or gate evaluation called"<<endl;
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
        cout<<"or gate evaluation done"<<endl;

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



    return value;
    }
    else
        return -1;

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
            size_t delayPos = line.find('#') + 1; //saves the delay in a variable
            size_t delayfinalpos=delayPos;
            while(line[delayfinalpos] != ' ') {
                delayfinalpos++;
            }
            string delay = line.substr(delayPos, delayfinalpos-delayPos);
            cout<<"The delay is: "<<delay<<endl;
            size_t inputEnd = line.find('=');
            string inputName = trim(line.substr(delayfinalpos,inputEnd - (delayfinalpos))); //saves the name of the input

            size_t valueEnd = line.find(';');
            string inputValue = trim(line.substr(inputEnd + 1, valueEnd - (inputEnd + 1))); //saves the value of the input


            vector<string> event1; //creates a vector of events and pushes the data related to each event onto the vector
            event1.push_back(delay);
            event1.push_back(inputName);
            event1.push_back(inputValue);

            events.push_back(event1);
        }

        for(int i =0; i<events.size(); i++) {
            for(int j =0; j<3;j++)
                cout<<events[i][j]<<" ";
            cout<<endl;
        }

    }
}

void writingInSimuliFile(string simuliFile) {
    ofstream simuli;
    simuli.open(simuliFile);

    //initializing the inputs to be zero so that line 264 works properly
    for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        it->second.push_back("-1");
    }

    if(simuli.is_open()) {

        while(!events.empty()) {
            vector<string> event = events.front();
            events.erase(events.begin());

            if(inputs[event[1]].empty()) { //checks if the output is the final output or the intermediate output
                simuli<< event[0] << "," << event[1] << "," << event[2] <<endl;
                cout<<"will not be added"<<endl; //if the vector of ouputs is empty, then this is the final output and will be outputted
            }
            else {
                int inputssize= inputs[event[1]].size();
                //saves the input value from the event vector to the inputs map
                inputs[event[1]][inputssize-1]=event[2];
                //loops over all outputs of the first event in the input
                for(int i = 0; i < inputs[event[1]].size() - 1; i++) {

                    string output = inputs[event[1]][i];
                    int size = outputs[output].size();
                    cout<<"output: "<<output<<endl;
                    for(int n=0; n<size;n++)
                        cout<<outputs[output][n]<<" ";
                    int finaldelay = stoi(event[0]) + stoi(outputs[output][size-1]);//The final delay is the sum of the gate delay and the input delay
                    cout<<"final delay: "<<finaldelay<<endl;
                    vector<string> newevent; //creates a new event and push the delay and output
                    newevent.push_back(to_string(finaldelay));
                    newevent.push_back(output);
                    cout<<"it is pussheeed"<<endl;
                    newevent.push_back(to_string(evaluateValue(output))); //push the value of the output
                    cout<<"the new event that should be pushed"<<endl;
                    for(int k =0; k<3;k++)
                        cout<<newevent[k]<<" ";
                    if(evaluateValue(output)!=-1) { // if the value is not empty then the delay will be output and the events vector is sorted according to the events
                        simuli<< event[0] << "," << event[1] << "," << event[2] <<endl;
                        bool added=false;
                        for(int j = 0; j < events.size(); j++) {
                            int currentDelay = stoi(events[j][0]);
                            cout<<"current delay: "<<currentDelay<<endl;
                            if(currentDelay > finaldelay) {
                                cout<<"insert " << j <<endl;
                                events.insert(events.begin() + j, newevent);
                                added=true;
                                break;
                            }
                        }
                        if(!added) {
                            events.push_back(newevent);
                        }
                        cout<<"events inside the writing function"<<endl;
                        for(int i =0; i<events.size(); i++) {
                            for(int j =0; j<3;j++)
                                cout<<events[i][j]<<" ";
                            cout<<endl;
                        }
                    }
                }
            }
        }
    }
    else {
        cerr << "Error opening the file: " << simuliFile;
    }
}