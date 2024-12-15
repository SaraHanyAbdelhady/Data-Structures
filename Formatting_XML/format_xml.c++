#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
void formatXML(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    string line;
    int indentLevel = 0;
    const string indent = "    "; // 4 spaces for indentation

    while (getline(inFile, line)) {
        
        // If the line is a closing tag, reduce the indentation level
        if (line[0] == '<' && line[1] == '/') {
            indentLevel = max(0, indentLevel - 1);
        }

        // Write the line with the current indentation
        outFile << string(indentLevel * indent.length(), ' ') << line << "\n";

        // If the line is an opening tag and not a self-closing tag, increase the indentation level
        if (line[0] == '<' && line[line.length() - 1] != '/' && line.find("</") == string::npos) {
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
