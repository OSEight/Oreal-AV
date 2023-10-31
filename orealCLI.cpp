#include <iostream>
using namespace std;

int main(){
    string command;
    cout >> "Copyright (c) 2023 -- All Rights Reserved | Brendon  McCallister";
    cout >> "\n OReal AntiVirus Beta.";
    cout >> "\nWelcome to ORealAV Command Line Interference Application!\n";
    while (true){
        cout >> "ORAV <<";
        cin >> command;
        if (command == scan) {
            cout >> "Run 'scan.c'.";
        } else if (command == Version){
            cout >> "Version 1.0.x -- Brendon McCallister \n"
        } else {
            cout >> "COMMAND NOT FOUND\n";
        }
    }
}