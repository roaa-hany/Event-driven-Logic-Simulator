//
// Created by roaah on 10/16/2024.
//
#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include<vector>
using namespace std;

unordered_map<char, vector<string>> inputs;//consider changing the map so that is maps strings instead of char to handly multi-char inputs
unordered_map<char, vector<string>> outputs;
vector<vector<string>> events;


void readverilogfile(string verilog);
int evaluatevalue(char out);
void readstimulifile(string stimulifile);
void writinginsimulifile(string stimulifile);


int main() {
    string verilog="D:\\Fall 2024\\Digital Design 1\\Project 1\\DD1_Project\\Source Code\\circuit.txt";
    readverilogfile(verilog);
    readstimulifile("D:\\Fall 2024\\Digital Design 1\\Project 1\\DD1_Project\\Source Code\\stimuli.txt");
    writinginsimulifile("simuli.txt");
    return 0;
}

void readverilogfile(string verilogfile) {
    ifstream verilog(verilogfile); //think of why it doesn't work when it is written only as "circuit.txt"


    if(!verilog) {
        cerr<<"Error opening the circuit module";
        return ;
    }
    else {
        string line;
        string andgate =" and";
        string orgate =" or";
        string nandgate ="nand";
        string norgate =" nor";
        string xnorgate ="xnor";
        string notgate ="not";
        string bufgate = "buf";
        string xorgate="xor";
        while (getline(verilog, line)) {
            //handling and gates
            if(line.find(andgate) != string::npos) {
                int delay = line[line.find(andgate) + 7]- '0';
                char out = line[line.find(andgate) + 11];
                char in1 = line[line.find(andgate) + 13];
                char in2 = line[line.find(andgate) + 15];

                inputs[in1].push_back(string(1,out));
                inputs[in2].push_back(string(1,out));
                outputs[out].push_back("and");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(string(1,in2));
                outputs[out].push_back(to_string(delay));


            }
            //handling or gates
            if(line.find(orgate) != string::npos) {
                int delay = line[line.find(orgate) + 6]- '0';
                char out = line[line.find(orgate) + 10];
                char in1 = line[line.find(orgate) + 12];
                char in2 = line[line.find(orgate) + 14];

                inputs[in1].push_back(string(1,out));
                inputs[in2].push_back(string(1,out));
                outputs[out].push_back("or");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(string(1,in2));
                outputs[out].push_back(to_string(delay));
            }
            //handling nand gates
            if(line.find(nandgate) != string::npos) {
                int delay = line[line.find(nandgate) + 7]- '0';
                char out = line[line.find(nandgate) + 11];
                char in1 = line[line.find(nandgate) + 13];
                char in2 = line[line.find(nandgate) + 15];

                inputs[in1].push_back(string(1,out));
                inputs[in2].push_back(string(1,out));
                outputs[out].push_back("nand");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(string(1,in2));
                outputs[out].push_back(to_string(delay));
            }
            //handling nor gates
            if(line.find(norgate) != string::npos) {
                int delay = line[line.find(norgate) + 7]- '0';
                char out = line[line.find(norgate) + 11];
                char in1 = line[line.find(norgate) + 13];
                char in2 = line[line.find(norgate) + 15];

                inputs[in1].push_back(string(1,out));
                inputs[in2].push_back(string(1,out));
                outputs[out].push_back("nor");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(string(1,in2));
                outputs[out].push_back(to_string(delay));
            }
            //handling xnor gates
            if(line.find(xnorgate) != string::npos) {
                int delay = line[line.find(xnorgate) + 7]- '0';
                char out = line[line.find(xnorgate) + 11];
                char in1 = line[line.find(xnorgate) + 13];
                char in2 = line[line.find(xnorgate) + 15];

                inputs[in1].push_back(string(1,out));
                inputs[in2].push_back(string(1,out));
                outputs[out].push_back("xnor");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(string(1,in2));
                outputs[out].push_back(to_string(delay));
            }
            //handling not gates
            if(line.find(notgate) != string::npos) {
                int delay = line[line.find(notgate) + 6]- '0';
                char out = line[line.find(notgate) + 10];
                char in1 = line[line.find(notgate) + 12];

                inputs[in1].push_back(string(1,out));
                outputs[out].push_back("not");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(to_string(delay));
            }
            //handling buf gates
            if(line.find(bufgate) != string::npos) {
                int delay = line[line.find(bufgate) + 6]- '0';
                char out = line[line.find(bufgate) + 10];
                char in1 = line[line.find(bufgate) + 12];

                inputs[in1].push_back(string(1,out));
                outputs[out].push_back("buf");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(to_string(delay));
            }
            //handling xor gates
            if(line.find(xorgate) != string::npos) {
                int delay = line[line.find(xorgate) + 6]- '0';
                char out = line[line.find(xorgate) + 10];
                char in1 = line[line.find(xorgate) + 12];
                char in2 = line[line.find(xorgate) + 14];

                inputs[in1].push_back(string(1,out));
                inputs[in2].push_back(string(1,out));
                outputs[out].push_back("xor");
                outputs[out].push_back(string(1,in1));
                outputs[out].push_back(string(1,in2));
                outputs[out].push_back(to_string(delay));
            }
        }
    }
    verilog.close();


}
int evaluatevalue(char out) {
    string gate = outputs[out].at(0);
    int value=0;
    if(gate=="and") {
        char in1 = (outputs[out].at(1))[0];
        char in2 = (outputs[out].at(2))[0];
        int in1valueindex= inputs[in1].size()-1;
        int in2valueindex= inputs[in2].size()-1;

        if(inputs[in1][in1valueindex]=="1" && inputs[in2][in2valueindex]=="1") {
            value=1;
        }
        else
            value=0;
    }

    else if(gate=="or") {
        char in1 = (outputs[out].at(1))[0];
        char in2 = (outputs[out].at(2))[0];
        int in1valueindex= inputs[in1].size()-1;
        int in2valueindex= inputs[in2].size()-1;

        if(inputs[in1][in1valueindex]=="0" && inputs[in2][in2valueindex]=="0") {
            value=0;
        }
        else
            value=1;
    }

    else if(gate=="nor") {
        char in1 = (outputs[out].at(1))[0];
        char in2 = (outputs[out].at(2))[0];
        int in1valueindex= inputs[in1].size()-1;
        int in2valueindex= inputs[in2].size()-1;

        if(inputs[in1][in1valueindex]=="0" && inputs[in2][in2valueindex]=="0") {
            value=1;
        }
        else
            value=0;
    }

    else if(gate=="nand") {
        char in1 = (outputs[out].at(1))[0];
        char in2 = (outputs[out].at(2))[0];
        int in1valueindex= inputs[in1].size()-1;
        int in2valueindex= inputs[in2].size()-1;

        if(inputs[in1][in1valueindex]=="1" && inputs[in2][in2valueindex]=="1") {
            value=0;
        }
        else
            value=1;
    }
    else if(gate=="xor") {
        char in1 = (outputs[out].at(1))[0];
        char in2 = (outputs[out].at(2))[0];
        int in1valueindex= inputs[in1].size()-1;
        int in2valueindex= inputs[in2].size()-1;

        if(inputs[in1][in1valueindex]==inputs[in2][in2valueindex]) {
            value=0;
        }
        else
            value=1;
    }
    else if(gate=="xnor") {
        char in1 = (outputs[out].at(1))[0];
        char in2 = (outputs[out].at(2))[0];
        int in1valueindex= inputs[in1].size()-1;
        int in2valueindex= inputs[in2].size()-1;

        if(inputs[in1][in1valueindex]==inputs[in2][in2valueindex]) {
            value=1;
        }
        else
            value=0;
    }
    else if(gate=="not") {
        char in1 = (outputs[out].at(1))[0];
        int in1valueindex= inputs[in1].size()-1;

        if(inputs[in1][in1valueindex]=="1") {
            value=0;
        }
        else
            value=1;
    }
    else if(gate=="buf") {
        char in1 = (outputs[out].at(1))[0];
        int in1valueindex= inputs[in1].size()-1;

        if(inputs[in1][in1valueindex]=="1") {
            value=1;
        }
        else
            value=0;
    }
    //needs to check whether this output is an input or not and if so, its value needs to be updated.
    if(!inputs[out].empty()) {
        int size = inputs[out].size();
        inputs[out][size-1]=to_string(value);
    }
    return value;
}
void readstimulifile(string stimulifile) {
    ifstream stimuli(stimulifile); //think of why it doesn't work when it is written only as "circuit.txt"


    if(!stimuli) {
        cerr<<"Error opening the stimuli file";
        return ;
    }
    else {
        string line;
        while (getline(stimuli, line)) {
            int position=line.find('#');
            string delay="";
            int i =position+1;
            for(i; i<line.size(); i++ ) {
                if(line[i]==' ')
                    break;
                delay=delay+line[i];
            }
            string inputname = string(1,line[i+1]);
            string inputvalue=string(1,line[i+3]);
            vector<string> event1;
            event1.push_back(delay);
            event1.push_back(inputname);
            event1.push_back(inputvalue);
            events.push_back(event1);
        }
    }
}
void writinginsimulifile(string stimulifile) {
    ofstream simuli;
    simuli.open("D:\\Fall 2024\\Digital Design 1\\Project 1\\DD1_Project\\Source Code\\simuli.txt");
    //initializing the inputs to be zero so that line 264 works properly
    for (unordered_map<char, vector<string>>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
        it->second.push_back("0");
    }
    if(simuli.is_open()) {
        while(events.size()>0) {
            vector<string> event=events.front();
            events.erase(events.begin());
            simuli<<event[0] <<","<<event[1]<<","<<event[2]<<endl;
            //this loop is there to handly many outputs connected to a single input
            for(int i =0; i<inputs[event[1][0]].size()-1; i++) {
                char output=inputs[event[1][0]][i][0];
                int size=outputs[output].size();
                int finaldelay=(event[0][0]-'0')+(outputs[output][size-1][0]-'0');//final event delay = event delay + gate delay;
                vector<string> newevent;
                newevent.push_back(to_string(finaldelay));
                newevent.push_back(string(1,output));
                newevent.push_back(to_string(evaluatevalue(output)));
                //simuli<<newevent[0]<<","<<newevent[1]<<","<<newevent[2]<<endl;
                for(int j =0; j<events.size(); j++) {
                    int currentdelay = events[j][0][0]-'0';
                    if(currentdelay>finaldelay) {
                        events.insert(events.begin()+j,newevent);
                        break;
                    }
                }
            }

        }
    }
    else {
        cerr<<"Error opening the file";
    }
}