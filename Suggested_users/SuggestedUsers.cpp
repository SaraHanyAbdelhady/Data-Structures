#include <list>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "parseXML.h"

#include <unordered_set>

list<string> suggested_users(const std::string& input_file, int id) {
    list<string> suggested_users;
    std::vector<user> users_of_file;
    user User;

    parseXML(input_file, users_of_file);

    if (users_of_file.empty()) {
        std::cerr << "Error: No users found in the input file." << std::endl;
        return suggested_users;
    }

    bool user_found = false;
    for (const auto& u : users_of_file) {
        if (u.ID == id) {
            User = u;
            user_found = true;
            break;
        }
    }

    if (!user_found) {
        std::cerr << "Error: User with ID " << id << " not found." << std::endl;
        return suggested_users;
    }

    std::unordered_set<std::string> unique_suggestions;

    for (int follower_id : User.followers) {
        for (const auto& follower_user : users_of_file) {
            if (follower_user.ID == follower_id) {
                for (int followersoffollowers : follower_user.followers) {
                    if (followersoffollowers != id &&
                        std::find(User.followers.begin(), User.followers.end(), followersoffollowers) == User.followers.end()) {
                        for (const auto& u : users_of_file) {
                            if (u.ID == followersoffollowers) {
                                unique_suggestions.insert(u.name);
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
    }

    suggested_users.assign(unique_suggestions.begin(), unique_suggestions.end());
    return suggested_users;
}


int main() {
    const std::string file = "sample1.xml";
    int id = 3;

    list<string> suggestions = suggested_users(file, id);

    // Print the suggested users
    std::cout << "Suggested users for user " << id << ": ";
    for (string user_name : suggestions) {
        std::cout << user_name << " ";
    }
    std::cout << std::endl;

    return 0;
}