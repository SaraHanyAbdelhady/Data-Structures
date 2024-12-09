#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include "../Validity_checker/isValid.h"

using namespace std;

void errorCorrection(const string& input) {
    ifstream inputFile(input);
   
    if (input.empty())
    {
        cout << "The input file path " << input << "is empty. Please provide a valid file.\n";
        return;
    }
    /*if(!valid(input))
    {
        cout << "The input file: " << input << "is invalid please choose another one" << endl;
        return;
    }*/
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << input << endl;
        return;
    }
    // if (!outputFile.is_open())
    // {
    //     cout << "Unable to open output file: " << output << endl;
    //     return;
    // }
        
     

    inputFile.close();
    // outputFile.close();


}

  int main(){
    isValid("../sample4.xml");
       while(!unClosed.empty()){
            cout<<unClosed.top().first<<" "<<unClosed.top().second<<endl;
           unClosed.pop();
         }

             while(!unOpened.empty()){
            cout<<unOpened.top().first<<" "<<unOpened.top().second<<endl;
           unOpened.pop();
         }

   }
