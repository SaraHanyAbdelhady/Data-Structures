#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
#include "isValid.h"

using namespace std;

stack <pair<string,long long>> indices;

   void isValid(const string& input) {
    ifstream inputFile(input);
   
    if (input.empty())
    {
        cout << "The input file path " << input << "is empty. Please provide a valid file.\n";
        return;
    }
    
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << input << endl;
        return;
    }

     string inputStream;

     stack<pair<string,long long>> openings;

     queue <pair<string,long long>> closings;
     

    long long counter = 0;
     while(getline(inputFile,inputStream)){
        counter++;
      for(long long i=0; i<inputStream.size();){
        if(inputStream[i] == '<'  && inputStream[i+1] != '/') {
            string tagOpen="";
            i++;
            while(inputStream[i]!='>' && inputStream[i]!=' '){
                tagOpen+=inputStream[i];
                i++;
            }
             i++;
            openings.push(make_pair(tagOpen,counter));
           
          
        }
        else if(inputStream[i] == '<' && inputStream[i+1] == '/'){
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

   long long quSze= closings.size();
     while(!openings.empty()){
bool flag=0;
   while((quSze--)&&(!closings.empty()))
{
if(openings.top()==closings.front())
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
indices.push(make_pair(openings.top().first,openings.top().second));
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
          
        // while(!indices.empty()){
        //     cout<<indices.top().first<<" "<<indices.top().second<<endl;
        //    indices.pop();
        //  }
          
   
   
     inputFile.close();
     return;


   
   }

//    int main(){
//     isValid("../sample4.xml");
//    }

  
