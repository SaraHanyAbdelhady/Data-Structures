
#ifndef isValid_H
#define isValid_H

#include <string>
#include <stack>
# include <vector>
using namespace std;

extern stack<pair<string, long long>> unClosed; // Declaration of global variable
extern vector<pair<long long, string>> unOpened;
bool isValid(const string& input);            // Declaration of function

#endif
