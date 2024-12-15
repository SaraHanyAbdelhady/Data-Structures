#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
void formatXML(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open()) {
        cout << "Error opening input file: " << inputFile << endl;
        return;
    }

    if (!outFile.is_open()) {
        cout << "Error opening output file: " << outputFile << endl;
        return;
    }

    string line;
    int indentLevel = 0;
    const string indent = "    "; // 4 spaces for indentation

    while (getline(inFile, line)) {
        // Remove leading and trailing spaces from the line
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            continue;
        }

        // If the line is a closing tag, reduce the indentation level
        if (line[0] == '<' && line[1] == '/') {
            indentLevel = max(0, indentLevel - 1);
        }

        // Write the line with the current indentation
        outFile << string(indentLevel * indent.length(), ' ') << line << "\n";

        // If the line is an opening tag and not a self-closing tag, increase the indentation level
        if (line[0] == '<' && line[line.length() - 1] != '/' && line[1] != '?' && line.find("</") == string::npos) {
            indentLevel++;
        }
    }

    inFile.close();
    outFile.close();

}

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";

    formatXML(inputFile, outputFile);

    return 0;
}
