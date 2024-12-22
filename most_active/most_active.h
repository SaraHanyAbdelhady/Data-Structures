#pragma once
#ifndef MOST_ACTIVE_USER_H
#define MOST_ACTIVE_USER_H

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "parseXML.h"

// Function to find the most active user based on the number of followers and following
user most_active(const std::vector<user>& users);

#endif // MOST_ACTIVE_USER_H
