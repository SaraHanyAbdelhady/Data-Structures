
#include <list>
#include <cmath>
#include <algorithm>
#include "parseXML.h"

list<string> mutual(const string& input_file, int id1, int id2, int id3)
{
    list<string> mutual_users;
    vector<int> followers1, followers2, followers3;
    vector<user> user_IDS;
    parseXML(input_file, user_IDS);
    for (user User : user_IDS)
    {
        if (User.ID == id1)
            followers1 = User.followers;
        if (User.ID == id2)
            followers2 = User.followers;
        if (User.ID == id3)
            followers3 = User.followers;
    }
    for (int f1 : followers1)
    {
        //if in followers2 we didnt find f1 so it will return followers2.end so as long as it does not return followers2.end so it found f1
        //same for followers3
        if (find(followers2.begin(), followers2.end(), f1) != followers2.end() && find(followers3.begin(), followers3.end(), f1) != followers3.end())
        {
            for (user u : user_IDS)
            {
                if (u.ID == f1)
                    mutual_users.push_back(u.name);
            }
        }
    }
    return mutual_users;
}
int main()
{
    const string file = "sample1.xml";
    list<string> mutual_users;
    int id1 = 1, id2 = 2, id3 = 3;
    mutual_users = mutual(file, id1, id2, id3);
    if (mutual_users.empty())
        cout << "No Mutual Friends between User IDs: " << id1 << ", " << id2 << ", and " << id3 << endl;
    else
    {
        cout << "Mutual Friends of User IDs: " << id1 << ", " << id2 << " and " << id3 << " are:";
        for (string user_name : mutual_users)
            cout << endl << user_name;
    }

    return 0;
}
