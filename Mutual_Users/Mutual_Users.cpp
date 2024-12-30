#include <list>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include "parseXML.h"
#include "Mutual_Users.h"

list<std::string> mutual(const string& input_file, int id1, int id2, int id3)
{
    list<std::string> mutual_users;
    std::unordered_set<int> followers1, followers2, followers3;
    std::vector<user> user_IDS;
    parseXML(input_file, user_IDS);

    // Find the followers for each user based on their ID
    for (const user& User : user_IDS)
    {
        if (User.ID == id1)
            followers1 = std::unordered_set<int>(User.followers.begin(), User.followers.end());
        if (User.ID == id2)
            followers2 = std::unordered_set<int>(User.followers.begin(), User.followers.end());
        if (User.ID == id3)
            followers3 = std::unordered_set<int>(User.followers.begin(), User.followers.end());
    }

    // Find mutual followers across the 3 users
    for (int f1 : followers1)
    {
        if (followers2.find(f1) != followers2.end() && followers3.find(f1) != followers3.end())
        {
            // Find the user corresponding to the follower ID
            auto userIter = std::find_if(user_IDS.begin(), user_IDS.end(),
                                         [f1](const user& u) { return u.ID == f1; });

            if (userIter != user_IDS.end()) {
                mutual_users.push_back(userIter->name);
            }
        }
    }

    return mutual_users;
}
