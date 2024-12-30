
#ifndef USER_UTILS_H
#define USER_UTILS_H

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include "parseXML.h"

// Function to parse XML and populate the `most_influencers` vector
void parseXML(const std::string& path, std::vector<user>& users);

// Function to find and display the most influential user
void Most_influencers(const std::string& path);

#endif // USER_UTILS_H
