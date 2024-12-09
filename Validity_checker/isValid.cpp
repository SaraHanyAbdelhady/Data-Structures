#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;



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
     queue<string> closings;
     stack<long long> indices;
     
      //<Name>Amany</Name>
    long long counter = 0;
     while(getline(inputFile,inputStream)){
        counter++;
      for(long long i=0; i<inputStream.size();){
        cout<<inputStream.size();
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
            openings.push(make_pair(tagClose,counter));
            
        }
        else i++;
      }
         
     
       
     }

     while(!openings.empty()){
            cout<<openings.top().first<<" "<<openings.top().second<<endl;
            openings.pop();
         }
          

     inputFile.close();
     return;


   
   }

   int main(){
    isValid("../sample4.xml");
   }

  
