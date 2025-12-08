#include <list>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include "parseXML.h"
#include "Mutual_Users.h"

/*list<std::string> mutual(const string& input_file, int id1, int id2, int id3)
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
}*/

vector<int> intersect_vectors(const vector<int>& vec1, const vector<int>& vec2) {
    vector<int> intersection;
    set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(intersection));
    return intersection;
}

std::vector<std::string> mutual(const std::string& input_file, vector<int> id)
{
    if (id.empty()) {
        cout << "Please enter 2 or more users to see Mutual users :).\n";
        return {};
    }
    if (id.size() == 1) {
        cout << "Please enter more than 1 user.\n";
        return {};
    }
    std::vector<user> user_IDS;
    parseXML(input_file, user_IDS);

    vector<vector<int>> Followers;
    int i;
    for (i = 0; i < id.size(); i++) {
        for (int j = 0; j < user_IDS.size(); j++) {
            if (id[i] == user_IDS[j].ID) {
                Followers.push_back(user_IDS[j].followers);
                break;
            }
        }
    }

    vector<int> result = Followers[0];

    for (i = 1; i < Followers.size(); ++i) {
        result = intersect_vectors(result, Followers[i]);
    }
    if (result.empty()) {
        cout << "There is no Mutual users between given users.\n";
    }
    vector<string> Mutual;

    for (i = 0; i < result.size(); i++) {
        for (int j = 0; j < user_IDS.size(); j++) {
            if (result[i] == user_IDS[j].ID) {
                Mutual.push_back(user_IDS[j].name);
                break;
            }
        }
    }
    return Mutual;
}

//int main() {
//    string inputFile = "../Test_samples/Xml_to_Json/sample.xml";
//    vector<int>id = {2,3};
//    vector <std::string> x = mutual(inputFile, id);
//    for (const std::string& element : x) {
//        std::cout << element << std::endl;
//    }
//}
