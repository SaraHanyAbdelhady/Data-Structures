#include <iostream>
#include <vector>
#include "parseXML.h"

using namespace std;

// Function to find the most active user based on the number of followers and following
user most_active(const vector<user>& users) {
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

    return mostActiveUser; // Return the user with the most connections
}

int main() {
    vector<user> users; // Vector to store all users

    // Parse the XML file to populate the users vector
    string filename = "input.xml"; // Update with the actual path to your XML file
    parseXML(filename, users);

    try {
        // Find the most active user based on the number of followers and following
        user activeUser = most_active(users);

        // Output the result
        cout << "Most Active User:\n";
        cout << "ID: " << activeUser.ID << "\n"; // Output user ID
        cout << "Name: " << activeUser.name << "\n"; // Output user name
        cout << "Number of Followers: " << activeUser.followers.size() << "\n"; // Output number of followers

        // Calculate and output the number of users the active user is following
        size_t followingCount = 0;
        for (const auto& other : users) {
            // Check if the most active user ID exists in the followers list of another user
            if (find(other.followers.begin(), other.followers.end(), activeUser.ID) != other.followers.end()) {
                followingCount++;
            }
        }
        cout << "Number of Following: " << followingCount << "\n"; // Output number of users they follow

    }
    catch (const exception& e) {
        // Handle any errors that occur (e.g., no users available)
        cout << "Error: " << e.what() << endl;
    }

    return 0; // End of the program
}
