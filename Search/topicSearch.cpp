#include"../parseXML/parseXML.h"
#include <bits/stdc++.h>

using namespace std;

void topicSearch(const string& filename,string topic)

{

ifstream inputFile(filename);
    // if error in opening xml file
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << filename << std::endl;
        return;
    }

    vector<user> users;
    parseXML(filename,users);

    int found =0;
    for(long long i=0; i<users.size(); i++){
        for(long long j=0; j<users[i].posts.size(); j++){
           unordered_set<string> topicSet(users[i].posts[j].topics.begin(), users[i].posts[j].topics.end());
                if (topicSet.find(topic) != topicSet.end()) {
                found = 1;
                cout << "User: " << users[i].name 
                     << " Post index: " << j + 1 
                     << " (Topic found)" << endl;
            }
            }
        }
    

    if(found==0) cout<<"Topic not found"<<endl;




}




int main()

{
   topicSearch("Test_samples/Xml_to_json/sample.xml","blabla");
}