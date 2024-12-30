#include <iostream>
#include <vector>
#include <string>
#include "Most_influencer.h"
using namespace std;

void Most_influencers(const string& path) {
    vector<user> users;
    // Parse the XML file and populate the 'users' vector
    parseXML(path, users);

    if (users.empty()) {
        cout << "No users found in the XML file." << endl;
        return; // Early return to avoid unnecessary code execution
    }

    // Find the user with the most followers
    int max_followers = 0;
    user most_influential_user;

    for (const auto& u : users) {
        if (u.followers.size() > max_followers) {
            max_followers = u.followers.size();
            most_influential_user = u;
        }
    }

    // Output the name and ID of the most influential user and the number of followers
    cout << "Most influential user: " << endl;
    cout << "ID: " << most_influential_user.ID << endl;
    cout << "Name: " << most_influential_user.name << endl;
    cout << "Number of followers: " << max_followers << endl;
}