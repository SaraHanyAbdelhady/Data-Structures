
#ifndef isValid_H
#define isValid_H

#include <string>
#include <stack>
using namespace std;

extern stack<pair<string, long long>> unClosed; // Declaration of global variable
extern stack<pair<string, long long>> unOpened;
void isValid(const string& input);            // Declaration of function

#endif
