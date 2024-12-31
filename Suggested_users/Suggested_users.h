#pragma once
#ifndef SUGGESTED_USERS_H
#define SUGGESTED_USERS_H

#include <list>
#include <string>

// Function to suggest users based on the given user's ID
std::list<std::string> suggested_users(const std::string& input_file, int id);

#endif // SUGGESTED_USERS_H
