#pragma once
#ifndef _PARSEXML_H_
#define _PARSEXML_H_


#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

// class to carry id & followers in one item
class user {
public:
    int ID;
    string name;
    vector<int> followers;
    user() {
        ID = 0;
        name = "";
        followers = {};
    }
    user(int x) {
        ID = x;
        followers = {};
        name = "";
    }
    user(int x, vector<int>y,string z) {
        ID = x;
        name = z;
        followers = y;
    }
};


void parseXML(const string& filename, vector<user>& graph);

#endif // _PARSEXML_H_