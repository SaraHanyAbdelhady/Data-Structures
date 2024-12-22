#include"../parseXML/parseXML.h"
#include <bits/stdc++.h>

using namespace std;

void wordSearch(const string& filename,string word)

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
          string s=users[i].posts[j].body;
          string token=""; 
    for (char c : s) {
        if (c == ' '||c == '.'||c == ',') {
       if(token==word)
          { 
            found=1;
           cout << "User: " << users[i].name  << " Post index: " << j + 1<<" ";
          cout<<word<<" has been found"<<"\n";
          }       
            token = "";
        }
        else {
            token += c;
        }
    }
       }
}
 if(found==0) cout<<"Word not found"<<endl;
}



int main()

{
   wordSearch("../Test_samples/Xml_to_json/sample.xml","amet");
}