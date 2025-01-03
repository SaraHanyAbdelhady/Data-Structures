#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
#include "isValid.h"

using namespace std;

stack <pair<string,long long>>unClosed;
vector <pair<long long,string>>unOpened;

   bool isValid(const string& input) {
    ifstream inputFile(input);

    if (inputFile.peek()== std::ifstream::traits_type::eof())
    {
        cout << "The input file path " << input << " is empty. Please provide a valid file.\n";
        return false;
    }
    
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << input << endl;
        return false;
    }
    while(!unClosed.empty())
 {
     unClosed.pop();
    }
unOpened.clear();
     string inputStream;
     stack<pair<string,long long>> openings;
     queue <pair<string,long long>> closings;
     

    long long counter = 0;
     while(getline(inputFile,inputStream)){
        counter++;
      for(long long i=0; i<inputStream.size();){
    if (inputStream[i] == '<' && (i + 1 < inputStream.size()) && inputStream[i + 1] != '/'&&inputStream[i + 1] != '!')
      {
            string tagOpen="";
            i++;
            while(inputStream[i]!='>' && inputStream[i]!=' '){
                tagOpen+=inputStream[i];
                i++;
            }
             i++;
            openings.push(make_pair(tagOpen,counter));
           
          
        }
        else if (inputStream[i] == '<' && (i + 1 < inputStream.size()) && inputStream[i + 1] == '/')
{
            string tagClose="";
            i++;
            i++;
            while(inputStream[i]!='>'){
                tagClose+=inputStream[i];
                i++;
            }
            i++;
           closings.push(make_pair(tagClose,counter));
            
        }
        else i++;
      }
         
     
       
     }


     while(!openings.empty()){
    bool flag=0;
   long long quSze= closings.size();
   while((quSze--)&&(!closings.empty()))
{
if(openings.top().first==closings.front().first && openings.top().second<=closings.front().second)
{
   openings.pop();
   closings.pop();
   flag=1;
   break;

}else{
string st=closings.front().first;
long long num=closings.front().second;
closings.pop();
closings.push(make_pair(st,num));
}
}
if(!flag){
unClosed.push(make_pair(openings.top().first,openings.top().second));
openings.pop();
}

     }

   
   while(!closings.empty()){
unOpened.push_back(make_pair(closings.front().second,closings.front().first));
closings.pop();
}
    inputFile.close();
    // if(!unClosed.empty())
    // cout<<"Unclosed not empty"<<"\n";
    // if(!unOpened.empty())
    // cout<<"UnOpened not empty"<<"\n";
    if(!(unClosed.empty()||unOpened.empty())){
        cout<< "The XML file is not valid "<<endl;
        cout<< "The Number of errors are "<<unOpened.size()+ unClosed.size()<< "\n";

    }
    else cout<< "The XML file is valid "<<"\n";
    return unClosed.empty()&&unOpened.empty();

   }

//   int main() {
//     cout << "Starting tag validation..." << endl;
//     isValid("../sample4.xml");

//     cout << "Unclosed tags:" << endl;
//     while (!unClosed.empty()) {
//         cout << unClosed.top().first << " " << unClosed.top().second << endl;
//         unClosed.pop();
//     }

//     cout << "Unopened tags:" << endl;
//     while (!unOpened.empty()) {
//         cout << unOpened.top().first << " " << unOpened.top().second << endl;
//         unOpened.pop();
//     }

//     return 0;
// }


  

