#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include "../Validity_checker/isValid.h"

using namespace std;

void errorCorrection(const string& input , const string& output) {
    ifstream inputFile(input);
    ofstream outputFile(output); 

   
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

    if (!outputFile.is_open())
    {
        cout << "Unable to open output file: " << output << endl;
        return;
    }

     string inputStream;
     stack<pair<string,long long>> openings;
     queue <pair<string,long long>> closings;
     

    long long counter = 0;
     while(getline(inputFile,inputStream)){
        counter++;
      for(long long i=0; i<inputStream.size();){
    if (inputStream[i] == '<' && (i + 1 < inputStream.size()) && inputStream[i + 1] != '/')
      {     
            outputFile << inputStream[i];
            string tagOpen="";
        
            i++;
            while(inputStream[i]!='>' && inputStream[i]!=' '){
                outputFile << inputStream[i];
                tagOpen+=inputStream[i];
                i++;
            }
            outputFile<<inputStream[i];
            
            if(!unClosed.empty() && unClosed.top().first == tagOpen && unClosed.top().second == counter){
               string close = "</" + tagOpen + ">";
            //    cout<<close<<endl;
               outputFile << close;
               unClosed.pop();
            }
             i++;
            //openings.push(make_pair(tagOpen,counter));
           
          
        }
        else if (inputStream[i] == '<' && (i + 1 < inputStream.size()) && inputStream[i + 1] == '/')
{  
    //   if(!unOpened.empty() && unOpened.top().second == counter){
    //             string open = "<" + unOpened.top().first + ">";
    //             cout<<unOpened.top().first;
    //             //  cout<<open<<endl;
    //             outputFile<<open;
    //             unOpened.pop();
    //         }
            outputFile<<inputStream[i];
            outputFile<<inputStream[i+1];
            string tagClose="";
            i++;
            i++;
            while(inputStream[i]!='>'){
                tagClose+=inputStream[i];
                outputFile<<inputStream[i];
                i++;
            }
             outputFile<<inputStream[i];
            i++;
           
            if(!unOpened.empty() && unOpened.top().first == tagClose && unOpened.top().second == counter){
                string open = "<" + tagClose + ">";
                 cout<<open<<endl;
                outputFile<<open;
                unOpened.pop();
            }
           closings.push(make_pair(tagClose,counter));
            
        }
        else{
            outputFile<<inputStream[i];
            i++;
        }
        outputFile<<"\n";
      }
         
     
       
     }
   inputFile.close();
   outputFile.close();
}

  int main(){
   cout<<isValid("../Test_samples/Xml_to_Json/sample4.xml")<<"\n";
   errorCorrection("../Test_samples/Xml_to_Json/sample4.xml", "../sample4Soln.txt");

   }
