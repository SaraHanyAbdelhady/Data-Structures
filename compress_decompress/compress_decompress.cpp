#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Function to compress a file using LZW encoding
void compressing(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName, ios::binary | ios::ate);

    // Check if the input file could be opened
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return;
    }

    // Check the file size to ensure it's greater than 5 KB (5120 bytes)
    streamsize fileSize = inputFile.tellg();
    if (fileSize < 5120) {
        cerr << "File size is smaller than 5 KB. Compression skipped." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg); // Move the file pointer back to the beginning

    ofstream outputFile(outputFileName, ios::binary);
    // Check if the output file could be opened
    if (!outputFile.is_open()) {
        cerr << "Error opening output file." << endl;
        inputFile.close();
        return;
    }

    // Initialize the dictionary with single-character entries
    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, i)] = i;
    }

    string current; // Tracks the current sequence being processed
    char c;
    int code = 256; // Starting code for new entries in the dictionary
    vector<int> compressed; // Stores the compressed output

    // Process the input file character by character
    while (inputFile.get(c)) {
        string next = current + c;
        // Check if the sequence exists in the dictionary
        if (dictionary.find(next) != dictionary.end()) {
            current = next;
        } else {
            // Add the current sequence's code to the output
            compressed.push_back(dictionary[current]);
            // Add the new sequence to the dictionary if within the limit
            if (code < 4096) {
                dictionary[next] = code++;
            }
            current = string(1, c);
        }
    }

    // Add the last sequence to the output
    if (!current.empty()) {
        compressed.push_back(dictionary[current]);
    }

    // Write the compressed data to the output file
    for (int num : compressed) {
        outputFile.write(reinterpret_cast<char*>(&num), sizeof(num));
    }

    // Close the input and output files
    inputFile.close();
    outputFile.close();
}

// Function to decompress a file using LZW encoding
void decompressing(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName, ios::binary);

    // Check if the input or output file could be opened
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    // Initialize the dictionary with single-character entries
    unordered_map<int, string> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, i);
    }

    int oldCode, newCode; // Codes read from the compressed file
    inputFile.read(reinterpret_cast<char*>(&oldCode), sizeof(oldCode));
    string current = dictionary[oldCode]; // Decoded string for the first code
    string output = current;
    outputFile << output;

    int code = 256; // Starting code for new entries in the dictionary

    // Read the rest of the compressed data
    while (inputFile.read(reinterpret_cast<char*>(&newCode), sizeof(newCode))) {
        string entry;
        if (dictionary.find(newCode) != dictionary.end()) {
            // Retrieve the entry from the dictionary
            entry = dictionary[newCode];
        } else if (newCode == code) {
            // Handle the special case where the new code is equal to the current dictionary size
            entry = current + current[0];
        } else {
            // Handle decompression errors
            cerr << "Decompression error." << endl;
            return;
        }

        // Write the decoded entry to the output file
        outputFile << entry;

        // Add the new sequence to the dictionary
        if (code < 4096) {
            dictionary[code++] = current + entry[0];
        }

        current = entry; // Update the current sequence
    }

    // Close the input and output files
    inputFile.close();
    outputFile.close();
}

// Main function to handle command-line arguments
/*
int main(int argc, char* argv[]) {
    // Check for valid command-line arguments
    if (argc < 5) {
        cerr << "Usage: xml_editor <operation> -i <input_file> -o <output_file>\n";
        return 1;
    }

    string operation = argv[1];
    string inputFileName, outputFileName;

    // Parse command-line arguments
    for (int i = 2; i < argc; i += 2) {
        string flag = argv[i];
        if (flag == "-i") {
            inputFileName = argv[i + 1];
        } else if (flag == "-o") {
            outputFileName = argv[i + 1];
        }
    }

    // Perform the requested operation
    if (operation == "compress") {
        compressing(inputFileName, outputFileName);
    } else if (operation == "decompress") {
        decompressing(inputFileName, outputFileName);
    } else {
        cerr << "Invalid operation. Use 'compress' or 'decompress'." << endl;
        return 1;
    }

    return 0;
}
*/
