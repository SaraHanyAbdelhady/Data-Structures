#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Function to trim leading and trailing spaces
string trim(const string &str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to format XML
void formatXML(const string &inputFile, const string &outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open()) {
        cout << "Error: Cannot open input file " << inputFile << endl;
        return;
    }

    if (!outFile.is_open()) {
        cout << "Error: Cannot open output file " << outputFile << endl;
        return;
    }

    string line, formattedXML;
    int indentLevel = 0;
    const string indent = "    "; // 4 spaces for indentation
    string buffer;

    while (getline(inFile, line)) {
        buffer += trim(line); // Concatenate lines into a single buffer
    }

    size_t i = 0;
    while (i < buffer.size()) {
        if (buffer[i] == '<') {
            // Write content before the tag
            size_t contentStart = buffer.find_last_of('>', i - 1) + 1;
            string content = trim(buffer.substr(contentStart, i - contentStart));
            if (!content.empty()) {
                formattedXML += string(indentLevel * indent.size(), ' ') + content + "\n";
            }

            // Find the end of the tag
            size_t tagEnd = buffer.find('>', i);
            if (tagEnd == string::npos) {
                cout << "Error: Malformed XML file." << endl;
                return;
            }

            string tag = buffer.substr(i, tagEnd - i + 1);

            // Determine tag type
            if (tag[1] == '/') { // Closing tag
                indentLevel = max(0, indentLevel - 1);
                formattedXML += string(indentLevel * indent.size(), ' ') + tag + "\n";
            } else if (tag[tag.size() - 2] == '/') { // Self-closing tag
                formattedXML += string(indentLevel * indent.size(), ' ') + tag + "\n";
            } else { // Opening tag
                formattedXML += string(indentLevel * indent.size(), ' ') + tag;
                if (tag[tag.size() - 2] != '>') {
                    formattedXML += "\n"; // Separate inline opening tags from nested content
                }
                indentLevel++;
            }

            buffer = buffer.substr(tagEnd + 1); // Remove processed part
            i = 0;                             // Reset index for new buffer
        } else {
            i++;
        }
    }

    outFile << formattedXML;

    inFile.close();
    outFile.close();
}

int main() {
    string inputFile = "input.txt";   // Input XML file
    string outputFile = "output.txt"; // Output XML file

    formatXML(inputFile, outputFile);

    return 0;
}
