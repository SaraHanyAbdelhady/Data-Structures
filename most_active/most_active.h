#pragma once
#ifndef _MOST_ACTIVE_H_
#define _MOST_ACTIVE_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include "parseXML.h"

// Function to find and print the most active user based on the number of followers and following
// Takes the XML file path as input
void most_active(const std::string& filename);

#endif // _MOST_ACTIVE_H_
