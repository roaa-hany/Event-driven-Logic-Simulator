//
// Created by roaah on 10/16/2024.
//
#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include<vector>
using namespace std;

int main() {
    ifstream verilog("D:\\Fall 2024\\Digital Design 1\\Project 1\\DD1_Project\\Source Code\\circuit.txt"); //think of why it doesn't work when it is written only as "circuit.txt"
    unordered_map<char, vector<string>> inputs;//consider changing the map so that is maps strings instead of char to handly multi-char inputs
    unordered_map<char, vector<string>> outputs;

    if(!verilog) {
        cerr<<"Error opening the circuit module";
        return 1;
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
                cout<<delay<<endl;
            }
            //handling or gates
            if(line.find(orgate) != string::npos) {
                int delay = line[line.find(orgate) + 6]- '0';
                cout<<delay<<endl;

            }
            //handling nand gates
            if(line.find(nandgate) != string::npos) {
                int delay = line[line.find(nandgate) + 7]- '0';
                cout<<delay<<endl;

            }
            //handling nor gates
            if(line.find(norgate) != string::npos) {
                int delay = line[line.find(norgate) + 7]- '0';
                cout<<delay<<endl;

            }
            //handling xnor gates
            if(line.find(xnorgate) != string::npos) {
                int delay = line[line.find(xnorgate) + 7]- '0';
                cout<<delay<<endl;

            }
            //handling not gates
            if(line.find(notgate) != string::npos) {
                int delay = line[line.find(notgate) + 6]- '0';
                cout<<delay<<endl;

            }
            //handling buf gates
            if(line.find(bufgate) != string::npos) {
                int delay = line[line.find(bufgate) + 6]- '0';
                cout<<delay<<endl;

            }
            //handling xor gates
            if(line.find(xorgate) != string::npos) {
                int delay = line[line.find(xorgate) + 6]- '0';
                cout<<delay<<endl;

            }
        }
    }

    verilog.close();
    return 0;
}

