#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

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
     
     

   
   }

  
