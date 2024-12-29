#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "parseXML.h"

using namespace std;

// Function to find and print the most active user based on the number of followers and following
void most_active(const string& filename) {
    vector<user> users; // Vector to store all users

    // Parse the XML file to populate the users vector
    parseXML(filename, users);

    if (users.empty()) {
        throw runtime_error("No users available to determine the most active user.");
    }

    // Define the most active user as the one with the greatest number of followers and following
    user mostActiveUser; // Placeholder for the most active user
    size_t maxConnections = 0; // Variable to track the maximum number of connections

    // Iterate through each user to calculate their connections
    for (const auto& u : users) {
        // Calculate the number of followers for the current user
        size_t connections = u.followers.size();

        // Calculate how many users the current user is following
        size_t followingCount = 0;
        for (const auto& other : users) {
            // Check if the current user ID exists in the followers list of another user
            if (find(other.followers.begin(), other.followers.end(), u.ID) != other.followers.end()) {
                followingCount++;
            }
        }

        // Add the number of users they are following to their connections
        connections += followingCount;

        // Update the most active user if the current user has more connections
        if (connections > maxConnections) {
            maxConnections = connections;
            mostActiveUser = u;
        }
    }

    // Print the most active user's details
    //cout << "Most Active User:\n";
    cout << "ID: " << mostActiveUser.ID << "\n";
    cout << "Name: " << mostActiveUser.name << "\n";
   // cout << "Number of Followers: " << mostActiveUser.followers.size() << "\n";
    /*
    // Calculate and output the number of users the active user is following
    size_t followingCount = 0;
    for (const auto& other : users) {
        if (find(other.followers.begin(), other.followers.end(), mostActiveUser.ID) != other.followers.end()) {
            followingCount++;
        }
    }
    cout << "Number of Following: " << followingCount << "\n";
    */
}

int main() {
    string filename = "input.xml"; // Update with the actual path to your XML file

    try {
        // Find and print the most active user
        most_active(filename);
    }
    catch (const exception& e) {
        // Handle any errors that occur (e.g., no users available)
        cout << "Error: " << e.what() << endl;
    }

    return 0; // End of the program
}
