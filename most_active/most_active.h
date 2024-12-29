#pragma once
#ifndef _MOST_ACTIVE_H_
#define _MOST_ACTIVE_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include "parseXML.h"

// Function to find and print the most active user based on the number of followers and following
void most_active(const std::vector<user>& users);

#endif // _MOST_ACTIVE_H_
