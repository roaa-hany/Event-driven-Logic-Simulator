#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//
// Created by wahba on 02/11/2024.
//
int main() {
    ifstream file;
    ifstream file1;
    file1.open("output_check.txt");
    file.open("simuli.txt");
    if(!file.is_open()) {
        cout<<"File does not exist"<<endl;
    }
    else {
        bool flag;
        flag=true;
        string line;
        string line2;
        while(getline(file,line)  || getline(file1,line2)) {
            if(line!=line2) {
                flag=false;
            }
        }
        if(flag==true) {
            cout<<"failed";
        }
        else {
            cout<<"success";
        }
    }
    file.close();
    file1.close();
}