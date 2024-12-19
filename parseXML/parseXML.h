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
    vector<int> followers;
    user() {
        ID = 0;
        followers = {};
    }
    user(int x) {
        ID = x;
        followers = {};
    }
    user(int x, vector<int>y) {
        ID = x;
        followers = y;
    }
};


void parseXML(const string& filename, vector<user>& graph);

#endif // _PARSEXML_H_