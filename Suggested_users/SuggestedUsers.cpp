#include <list>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include "parseXML.h"

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

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: xml_editor suggest -i <input_file.xml> -id <user_id>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string input_flag = argv[2];
    std::string input_file = argv[3];
    std::string id_flag = argv[4];
    int id = std::stoi(argv[5]);

    // Validate command and flags
    if (command != "suggest" || input_flag != "-i" || id_flag != "-id") {
        std::cerr << "Error: Invalid command or flags." << std::endl;
        return 1;
    }

    list<string> suggestions = suggested_users(input_file, id);

    // Print the suggested users
    std::cout << "Suggested users for user " << id << ": ";
    for (const std::string& user_name : suggestions) {
        std::cout << user_name << " ";
    }
    std::cout << std::endl;

    return 0;
}
