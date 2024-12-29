#pragma once
#ifndef _PARSEXML_H_
#define _PARSEXML_H_


#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
//carry body and topics of posts
class post {
public:
    string body;
    vector<string>topics;
    post() {
        body = "";
        topics = {};
    }
    post(string b, vector<string>t) {
        body = b;
        topics = t;
    }
};
// class to carry id & followers in one item
class user {
public:
    int ID;
    string name;
    vector<int> followers;
    vector<post>posts;
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
    user(int x, vector<int>y, string z, vector<post> p) {
        ID = x;
        name = z;
        followers = y;
        posts = p;
    }
};


void parseXML(const string& filename, vector<user>& users);

#endif // _PARSEXML_H_
