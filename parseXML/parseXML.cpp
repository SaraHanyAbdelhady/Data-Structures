
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>

#include "parseXML.h"

using namespace std;



// Function to parse XML and build a graph
void parseXML(const string& filename, vector<user>& graph)
{

    ifstream inputFile(filename);
    // if error in opening xml file
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << filename << std::endl;
        return;
    }
    string line;                //to read line by line from the xml file
    stack<string> tags;         //to store tags
    user User;                  // dammy user to fill graph vector
    bool in_follower = false;   //to see if id is from user or followers
    while (getline(inputFile, line)) {

        if (line.empty()) continue;

        int start_of_tag = line.find('<');
        int end_of_tag = line.find('>');
        string remainder = line.substr(end_of_tag + 1);

        if (start_of_tag < line.size() && start_of_tag >= 0 && end_of_tag < line.size() && end_of_tag >= 0) {
            string tagContent = line.substr(start_of_tag + 1, end_of_tag - start_of_tag - 1);
            // check opening tags
            if (tagContent[0] != '/') {
                tags.push(tagContent);
                if (tagContent == "user") {
                    User = user(); // initialize user
                }
                else if (tagContent == "follower") {
                    in_follower = true;
                }
                else if (tagContent == "id") {
                    // in case the opening and closing are in the same line
                    if (!remainder.empty()) {
                        string id_string = remainder.substr(0, remainder.find('<'));
                        if (in_follower) {
                            User.followers.push_back(stoi(id_string));
                        }
                        else {
                            User.ID = stoi(id_string);
                        }
                        if (!tags.empty()) tags.pop();
                    }
                }
            }
            //check closing tags
            else if (tagContent[0] == '/') {
                string closingTag = tagContent.substr(1, tagContent.length() - 1);
                if (closingTag == "user") {
                    // Add user to vector
                    graph.push_back(User);
                }
                else if (closingTag == "follower") {
                    in_follower = false;
                }

                if (!tags.empty()) tags.pop();
            }
        }
        //in case the tag is opened and not closed in the sme line
        else {
            if (!tags.empty()) {
                string currentTag = tags.top();

                if (currentTag == "id") {
                    if (in_follower) {
                        User.followers.push_back(stoi(line));
                    }
                    else {
                        User.ID = stoi(line);
                    }
                }
            }
        }
    }
    inputFile.close();
}