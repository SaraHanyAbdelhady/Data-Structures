#ifndef FORMAT_XML_H
#define FORMAT_XML_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Function to trim leading and trailing spaces
string trim(const string &str);

// Function to check if the input XML file is valid (you need to implement this function)
bool isValid(const string &inputFile);

// Function to format XML
void format_XML(const string &inputFile, const string &outputFile);

#endif // FORMAT_XML_H
