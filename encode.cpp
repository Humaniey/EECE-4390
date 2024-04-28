#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Maps binary 1 to postive voltage 
// and binary 0 to negative voltage
string encodeNRZL(string input) {
    string output = "|";
    char c;
    for(unsigned long i = 0; i < input.length(); i++) {
        c = input[i];
        if(c == '1')
            output += "+V|";
        else if(c == '0')
            output += "-V|";
    }

    return output;
}

string encodeNRZI(string input) {
    return input;
}

string encodeBAMI(string input) {
    return input;
}

string encodeManchester(string input) {
    return input;
}

string encodeDManchester(string input) {
    return input;
}

void printEncodings() {
    cout << "Encodings:\n\t0:NRZ-L\n\t1:NRZ-I\n\t2:B-AMI\n\t3:Manchester\n\t4:D-Manchester\n";
}

int main(int argc, char* argv[]) {
    // Validate inputs
    if(argc != 3) {
        cout << "Error: please include filename and encoding as arg (encode <FILENAME> <encoding>)" << endl;
        printEncodings();
        return 1;
    }

    // Open input file
    string inputfile = argv[1];
    ifstream ifs;
    ifs.open(inputfile);
    if(!ifs.good()) {
        cout << "Error: could not open input file." << endl;
        return 1;
    }

    // Read input data stream
    string input;
    ifs >> input;
    ifs.close();

    // Read desired encoding scheme
    short encoding;
    try {
        encoding = stoi(argv[2]);
    } catch(...) {
        cout << "Error: encoding scheme should be a number." << endl;
        printEncodings();
        return 1;
    }

    // Route encoding
    string output;
    cout << "Using encoding ";
    switch(encoding) {
        case 0: 
            cout << "NRZ-L" << endl; 
            output = encodeNRZL(input);
            break;
        case 1: 
            cout << "NRZ-I" << endl;
            output = encodeNRZI(input);
            break;
        case 2: 
            cout << "B-AMI" << endl; 
            output = encodeBAMI(input);
            break;
        case 3: 
            cout << "Manchester" << endl; 
            output = encodeManchester(input);
            break;
        case 4: 
            cout << "D-Manchester" << endl; 
            output = encodeDManchester(input);
            break;
        default:
            cout << "Error: encoding scheme not recognized." << endl;
            printEncodings();
            return 1;
    }

    // Write result to output file
    ofstream ofs;
    ofs.open("OUTPUT.SIGNAL");
    ofs << output;
    ofs.close();

    // Print result to console
    cout << "INPUT: " << input << endl;
    cout << "OUTPUT: " << output << endl;

    return 0;

}