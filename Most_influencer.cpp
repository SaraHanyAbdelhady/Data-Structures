
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include "parseXML"
#include "parseXML.h"

using namespace std;


int main() {
    vector<user> most_influencers;
    string path = "ex1.txt";

    // Parse the XML file and populate the 'most_influencers' vector
    parseXML(path, most_influencers);

    if (most_influencers.empty()) {
        cout << "No users found in the XML file." << endl;
        return 0;
    }

    // Find the user with the most followers
    int max_followers = 0;
    user most_influential_user;

    for (const auto& u : most_influencers) {
        if (u.followers.size() > max_followers) {
            max_followers = u.followers.size();
            most_influential_user = u;
        }
    }

    // Output the name and ID of the most influential user
    cout << "Most influential user: " << endl;
    cout << "ID: " << most_influential_user.ID << endl;
    cout << "Name: " << most_influential_user.name << endl;

    return 0;
}



