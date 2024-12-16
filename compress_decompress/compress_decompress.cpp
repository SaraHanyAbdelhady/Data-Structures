#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Function to compress a file using LZW encoding
void compress(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName, ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, i)] = i;
    }

    string current;
    char c;
    int code = 256;
    vector<int> compressed;

    while (inputFile.get(c)) {
        string next = current + c;
        if (dictionary.find(next) != dictionary.end()) {
            current = next;
        }
        else {
            compressed.push_back(dictionary[current]);
            if (code < 4096) {
                dictionary[next] = code++;
            }
            current = string(1, c);
        }
    }

    if (!current.empty()) {
        compressed.push_back(dictionary[current]);
    }

    for (int num : compressed) {
        outputFile.write(reinterpret_cast<char*>(&num), sizeof(num));
    }

    inputFile.close();
    outputFile.close();
}

// Main function to handle command-line arguments
int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << argv[0];
        cerr << "Usage: xml_editor <operation> -i <input_file> -o <output_file>\n";
        return 1;
    }

    string operation = argv[1];
    string inputFileName, outputFileName;

    for (int i = 2; i < argc; i += 2) {
        string flag = argv[i];
        if (flag == "-i") {
            inputFileName = argv[i + 1];
        }
        else if (flag == "-o") {
            outputFileName = argv[i + 1];
        }
    }

    if (operation == "compress") {
        compress(inputFileName, outputFileName);
    }
    /*
    else if (operation == "decompress") {
        decompress(inputFileName, outputFileName);
    }
    */
    else {
        cerr << "Invalid operation. Use 'compress' or 'decompress'." << endl;
        return 1;
    }

    return 0;
}
