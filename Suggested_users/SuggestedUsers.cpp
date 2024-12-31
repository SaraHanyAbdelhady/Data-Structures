#include <list>
#include <unordered_set>
#include <algorithm>
#include "../parseXML/parseXML.h"
#include "Suggested_users.h"

list<std::string> suggested_users(const std::string& input_file, int id) {
    list<std::string> suggested_users;
    std::unordered_set<int> followers_of_user;
    std::unordered_set<int> unique_suggestions;
    std::vector<user> user_IDS;
    parseXML(input_file, user_IDS);

    // Find the followers for the user based on their ID
    for (const user& User : user_IDS) {
        if (User.ID == id) {
            followers_of_user = std::unordered_set<int>(User.followers.begin(), User.followers.end());
            break;
        }
    }

    // Find suggestions: followers of followers who are not already followed
    for (const user& User : user_IDS) {
        if (followers_of_user.find(User.ID) != followers_of_user.end()) {
            for (int follower_of_follower : User.followers) {
                // Check if this follower of a follower is not the original user and is not already followed
                if (follower_of_follower != id && followers_of_user.find(follower_of_follower) == followers_of_user.end()) {
                    unique_suggestions.insert(follower_of_follower);
                }
            }
        }
    }

    // Convert set of suggested users' IDs to their names
    for (int suggested_id : unique_suggestions) {
        auto userIter = std::find_if(user_IDS.begin(), user_IDS.end(),
                                     [suggested_id](const user& u) { return u.ID == suggested_id; });
        if (userIter != user_IDS.end()) {
            suggested_users.push_back(userIter->name);
        }
    }

    // If no suggestions, add "none" to the list
    if (suggested_users.empty()) {
        suggested_users.push_back("none");
    }

    return suggested_users;
}

