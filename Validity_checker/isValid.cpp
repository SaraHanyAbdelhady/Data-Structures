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

    if (inputFile.tellg() == 0)
    {
        cout << "The input file path " << input << "is empty. Please provide a valid file.\n";
        return false;
    }
    
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << input << endl;
        return false;
    }
// unClosed.clear();
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


    //  while(!openings.empty()){
    //         cout<<openings.top().first<<" "<<openings.top().second<<endl;
    //         openings.pop();
    //      }


    //        while(!closings.empty()){
    //         cout<<closings.front().first<<" "<<closings.front().second<<endl;
    //        closings.pop();
    //      }
     
   
   while(!closings.empty()){
unOpened.push_back(make_pair(closings.front().second,closings.front().first));
closings.pop();
}
    inputFile.close();
    if(!unClosed.empty())
    cout<<"Unclosed not empty"<<"\n";
    if(!unOpened.empty())
    cout<<"UnOpened not empty"<<"\n";
    cout<< "The Number of errors are "<<unOpened.size()+ unClosed.size()<< "\n";
    int x = unOpened.size()
    for(int i = 0; i < x; i++)
    {

    }
    cout<< unOpened.size()+ unClosed.size()<< "\n";
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


  

