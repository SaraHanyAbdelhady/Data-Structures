#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

void Xml_to_Json(const string& input, const string& output) {
    ifstream inputFile(input);
    ofstream outputFile(output);
    if (input.empty())
    {
        cout << "The input file path " << input << "is empty. Please provide a valid file.\n";
        return;
    }
    /*if(!valid(input))
    {
        cout << "The input file: " << input << "is invalid please choose another one" << endl;
        return;
    }*/
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << input << endl;
        return;
    }
    if (!outputFile.is_open())
    {
        cout << "Unable to open output file: " << output << endl;
        return;
    }


    inputFile.close();
    outputFile.close();
}