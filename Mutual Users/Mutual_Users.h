#ifndef MUTUAL_UTILS_H
#define MUTUAL_UTILS_H

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include "parseXML.h" // Ensure parseXML.h defines `user` struct and `parseXML` function

// Function to find mutual friends of three users based on their IDs
std::list<std::string> mutual(const std::string& input_file, int id1, int id2, int id3);

#endif // MUTUAL_UTILS_H
