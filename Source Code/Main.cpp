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
int evaluatevalue(char out);
void readstimulifile(string stimulifile);
void writinginsimulifile(string stimulifile);


int main() {
    string verilog = "circuit.txt";
    readVerilogFile(verilog);
    // readstimulifile("stimuli.txt");
    // writinginsimulifile("simuli.txt");
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

// int evaluatevalue(char out) {
//     string gate = outputs[out].at(0);
//     int value=0;
//     if(gate=="and") {
//         char in1 = (outputs[out].at(1))[0];
//         char in2 = (outputs[out].at(2))[0];
//         int in1valueindex= inputs[in1].size()-1;
//         int in2valueindex= inputs[in2].size()-1;
//
//         if(inputs[in1][in1valueindex]=="1" && inputs[in2][in2valueindex]=="1") {
//             value=1;
//         }
//         else
//             value=0;
//     }
//
//     else if(gate=="or") {
//         char in1 = (outputs[out].at(1))[0];
//         char in2 = (outputs[out].at(2))[0];
//         int in1valueindex= inputs[in1].size()-1;
//         int in2valueindex= inputs[in2].size()-1;
//
//         if(inputs[in1][in1valueindex]=="0" && inputs[in2][in2valueindex]=="0") {
//             value=0;
//         }
//         else
//             value=1;
//     }
//
//     else if(gate=="nor") {
//         char in1 = (outputs[out].at(1))[0];
//         char in2 = (outputs[out].at(2))[0];
//         int in1valueindex= inputs[in1].size()-1;
//         int in2valueindex= inputs[in2].size()-1;
//
//         if(inputs[in1][in1valueindex]=="0" && inputs[in2][in2valueindex]=="0") {
//             value=1;
//         }
//         else
//             value=0;
//     }
//
//     else if(gate=="nand") {
//         char in1 = (outputs[out].at(1))[0];
//         char in2 = (outputs[out].at(2))[0];
//         int in1valueindex= inputs[in1].size()-1;
//         int in2valueindex= inputs[in2].size()-1;
//
//         if(inputs[in1][in1valueindex]=="1" && inputs[in2][in2valueindex]=="1") {
//             value=0;
//         }
//         else
//             value=1;
//     }
//     else if(gate=="xor") {
//         char in1 = (outputs[out].at(1))[0];
//         char in2 = (outputs[out].at(2))[0];
//         int in1valueindex= inputs[in1].size()-1;
//         int in2valueindex= inputs[in2].size()-1;
//
//         if(inputs[in1][in1valueindex]==inputs[in2][in2valueindex]) {
//             value=0;
//         }
//         else
//             value=1;
//     }
//     else if(gate=="xnor") {
//         char in1 = (outputs[out].at(1))[0];
//         char in2 = (outputs[out].at(2))[0];
//         int in1valueindex= inputs[in1].size()-1;
//         int in2valueindex= inputs[in2].size()-1;
//
//         if(inputs[in1][in1valueindex]==inputs[in2][in2valueindex]) {
//             value=1;
//         }
//         else
//             value=0;
//     }
//     else if(gate=="not") {
//         char in1 = (outputs[out].at(1))[0];
//         int in1valueindex= inputs[in1].size()-1;
//
//         if(inputs[in1][in1valueindex]=="1") {
//             value=0;
//         }
//         else
//             value=1;
//     }
//     else if(gate=="buf") {
//         char in1 = (outputs[out].at(1))[0];
//         int in1valueindex= inputs[in1].size()-1;
//
//         if(inputs[in1][in1valueindex]=="1") {
//             value=1;
//         }
//         else
//             value=0;
//     }
//     //needs to check whether this output is an input or not and if so, its value needs to be updated.
//     if(!inputs[out].empty()) {
//         int size = inputs[out].size();
//         inputs[out][size-1]=to_string(value);
//     }
//     return value;
// }
// void readstimulifile(string stimulifile) {
//     ifstream stimuli(stimulifile);
//
//
//     if(!stimuli) {
//         cerr<<"Error opening the stimuli file";
//         return ;
//     }
//     else {
//         string line;
//         while (getline(stimuli, line)) {
//             int position=line.find('#');
//             string delay="";
//             int i =position+1;
//             for(i; i<line.size(); i++ ) {
//                 if(line[i]==' ')
//                     break;
//                 delay=delay+line[i];
//             }
//             string inputname = string(1,line[i+1]);
//             string inputvalue=string(1,line[i+3]);
//             vector<string> event1;
//             event1.push_back(delay);
//             event1.push_back(inputname);
//             event1.push_back(inputvalue);
//             events.push_back(event1);
//         }
//     }
// }
// void writinginsimulifile(string stimulifile) {
//     ofstream simuli;
//     simuli.open("simuli.txt");
//     //initializing the inputs to be zero so that line 264 works properly
//     for (unordered_map<char, vector<string>>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
//         it->second.push_back("0");
//     }
//     if(simuli.is_open()) {
//         while(events.size()>0) {
//             vector<string> event=events.front();
//             events.erase(events.begin());
//             simuli<<event[0] <<","<<event[1]<<","<<event[2]<<endl;
//             //this loop is there to handly many outputs connected to a single input
//             for(int i =0; i<inputs[event[1][0]].size()-1; i++) {
//                 char output=inputs[event[1][0]][i][0];
//                 int size=outputs[output].size();
//                 int finaldelay=(event[0][0]-'0')+(outputs[output][size-1][0]-'0');//final event delay = event delay + gate delay;
//                 vector<string> newevent;
//                 newevent.push_back(to_string(finaldelay));
//                 newevent.push_back(string(1,output));
//                 newevent.push_back(to_string(evaluatevalue(output)));
//                 //simuli<<newevent[0]<<","<<newevent[1]<<","<<newevent[2]<<endl;
//                 for(int j =0; j<events.size(); j++) {
//                     int currentdelay = events[j][0][0]-'0';
//                     if(currentdelay>finaldelay) {
//                         events.insert(events.begin()+j,newevent);
//                         break;
//                     }
//                 }
//             }
//
//         }
//     }
//     else {
//         cerr<<"Error opening the file";
//     }
// }