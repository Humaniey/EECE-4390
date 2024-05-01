#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// NRZ-L encoding switches to negative (or positive) if there is a 1
// then switches back to positive (or negative) if there is a 0
string encodeNRZL(string input) {
    // Set up the inital boundary
    string output = "|";
    // Set up a loop to run through the length of the input code
    for(unsigned long i = 0; i < input.length(); i++) {
        // Check if input is 1
        if(input[i] == '1')
            // Display negative voltage
            output += "-V|";
        // Check if input is 0
        else if(input[i] == '0')
            // Display positive voltage
            output += "+V|";
    }
    // Return the resulting waveform 
    return output;
}

// NRZ-I encoding transitions between positive and negative voltage wherever there is a 1 in the input.
// If there is a 0, proceed to output the voltage previous.
string encodeNRZI(string input) {
    // Set up the inital boundary
    string output = "|";
    // Set up a state of to reaffirm which way to transition
    bool state = 0;
    // Set up a loop to run through the length of the input code
    for(unsigned long i = 0; i < input.length(); i++) {
        // Check if the input is 1
        if (input[i] == '1')
            // Switch the state of output voltage
            state = !state;
        // Check if the state if true or false 
        if (state)
            // Output a positive voltage and bound it
            output += "+V|";
        // Else...    
        else
            // Output a negative voltage and bound it
            output += "-V|";
    }
    // Return the resulting waveform
    return output;        
}

//B-AMI encoding transitions between positive and negative voltage wherever there is a 1 in the input.
// If there is a 0, proceed to output no voltage or 0 volts.
string encodeBAMI(string input) {
    // Set up the inital boundary
    string output = "|";
    // Set up a state of to reaffirm which way to transition
    bool state = 0;
    // Set up a loop to run through the length of the input code
    for (unsigned long i = 0; i < input.length(); i++) {
        // Check if input is 0
        if (input[i] == '0')
            // Display 0 volts and bound it
            output += "0V|";
        // Check if the input is 1
        else if (input[i] == '1') {
            // Switch the state of output voltage
            state = !state;
            // Check if the state if true or false
            if (state)
                // Output a positive voltage and bound it
                output += "+V|";
            // Else...
            else
                // Output a negative voltage and bound it
                output += "-V|";
        }
    }
    // Return the resulting waveform
    return output;
}
// Manchester encoding contains a transition between the clock cycle rather than at the start.
// An input of 0 will transition from positive to negative while an input of 1 transitions from negative to positive voltage.
string encodeManchester(string input) {
    // Set up the inital boundary
    string output = "|";
    // Set up a loop to run through the length of the input code
    for(unsigned long i = 0; i < input.length(); i++) {
        // Check if the input is 1
        if(input[i] == '1')
            // Return a negative to positive voltage
            output += "-V+V|";
        // Else...
        else
            // Return a positive to negative voltage
            output += "+V-V|";
    }
    // Return the resulting waveform
    return output;
}
// D-Manchester encoding contains a transition between the clock cycle rather than at the start.
// With an input of 1, the voltage will be held from the previous cycle then transition.
// An input of 0 will not hold the voltage and transition the same as the previous.
string encodeDManchester(string input) {
    // Set up the inital boundary
    string output = "|";
    // Set up a state of to reaffirm which way to transition
    bool state = 0;
    // Set up a loop to run through the length of the input code
    for (unsigned long i = 0; i < input.length(); i++) {
        // Check if the input is 1
        if (input[i] == '1') {
                // Switch the state of output voltage transition
                state = !state;
            // Check if the state if true or false
            if (state)
                // Return a negative to positive voltage
                output += "-V+V|";
            // Else...    
            else
                // Return a positive to negative voltage
                output += "+V-V|";
            }
        // Check if the input is 0
        else if (input[i] == '0') {
            // Check if the state if true or false
            if (state)
                // Return a negative to positive voltage
                output += "-V+V|";
            // Else...   
            else
                // Return a positive to negative voltage 
                output += "+V-V|";
            }
    }
    // Return the resulting waveform
    return output;
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

    // Route encoding to their own files with their own names
    string output;
    string outputFileName = "OUTPUT";
    cout << "Using encoding ";
    switch(encoding) {
        case 0: 
            cout << "NRZ-L" << endl; 
            output = encodeNRZL(input);
            outputFileName += ".NRZ-L";
            break;
        case 1: 
            cout << "NRZ-I" << endl;
            output = encodeNRZI(input);
            outputFileName += ".NRZ-I";
            break;
        case 2: 
            cout << "B-AMI" << endl; 
            output = encodeBAMI(input);
            outputFileName += ".B-AMI";
            break;
        case 3: 
            cout << "Manchester" << endl; 
            output = encodeManchester(input);
            outputFileName += ".Manchester";
            break;
        case 4: 
            cout << "D-Manchester" << endl; 
            output = encodeDManchester(input);
            outputFileName += ".D-Manchester";
            break;
        default:
            cout << "Error: encoding scheme not recognized." << endl;
            printEncodings();
            return 1;
    }

    // Write result to output files
    ofstream ofs;
    ofs.open(outputFileName);
    ofs << output;
    ofs.close();

    // Print result to console
    cout << "INPUT: " << input << endl;
    cout << "OUTPUT: " << output << endl;

    return 0;

}
