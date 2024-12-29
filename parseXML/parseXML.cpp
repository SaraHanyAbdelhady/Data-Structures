
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>

#include "parseXML.h"
#include "../Validity_checker/isValid.h"

using namespace std;



// Function to parse XML and build a vector of users
void parseXML(const string& filename, vector<user>& users)
{

    ifstream inputFile(filename);
    if (!isValid(filename))                   //if xml file not valid
    {
        cout << "The input file: " << filename << " is invalid please choose another one" << endl;
        return;
    }
    if (!inputFile.is_open())               // if there is no file with this name in this path
    {
        cout << "Unable to open input file: " << filename << endl;
        return;
    }
    string line;                //to read line by line from the xml file
    stack<string> tags;         //to store tags
    user User;                  // dummy user to fill users vector
    post Post;                  // dummy user to fill posts vector
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
                else if (tagContent == "post") {
                     Post = post(); // initialize user
                }
                else if (tagContent == "follower") {
                    in_follower = true;
                }
                else if (tagContent == "name") {
                    // in case the opening and closing are in the same line
                    if (!remainder.empty()) {
                        string name = remainder.substr(0, remainder.find('<'));
                        name = name.erase(0, name.find_first_not_of(' '));
                        User.name = name;
                        if (!tags.empty()) tags.pop();
                    }
                }
                else if (tagContent == "topic") {
                    // in case the opening and closing are in the same line
                    if (!remainder.empty()) {
                        string topic = remainder.substr(0, remainder.find('<'));
                        topic = topic.erase(0, topic.find_first_not_of(' '));
                        Post.topics.push_back(topic);
                        if (!tags.empty()) tags.pop();
                    }
                }
                else if (tagContent == "body") {
                    // in case the opening and closing are in the same line
                    if (!remainder.empty()) {
                        string post = remainder.substr(0, remainder.find('<'));
                        post = post.erase(0, post.find_first_not_of(' '));
                        Post.body = post;
                        if (!tags.empty()) tags.pop();
                    }
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
                    users.push_back(User);
                }
                else if (closingTag == "post") {
                    // Add user to vector
                    User.posts.push_back(Post);
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
                else if (currentTag == "name") {
                    line = line.erase(0, line.find_first_not_of(' '));
                    User.name = line;
                }
                else if (currentTag == "topic") {
                    line = line.erase(0, line.find_first_not_of(' '));
                    Post.topics.push_back(line);
                }
                else if (currentTag == "body") {
                    line = line.erase(0, line.find_first_not_of(' '));
                    Post.body = line;
                }
            }
        }
    }
    inputFile.close();
}
