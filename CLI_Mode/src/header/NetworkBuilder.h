#ifndef NetworkBuilder_H
#define NetworkBuilder_H
#include <bits/stdc++.h>
using namespace std;
class User {
    public:
    string name;
    int id;
    User(string n, int id){
        name = n;
        this->id = id;
    }
    void setName(string n) {
        name = n;
    }
    void setId(int id) {
        this->id = id;
    }
    string getName() const {
        return name;
    }
    int getId() const {
        return id;
    }
};
vector<pair<int,vector<int>>> XMLtoGraph(string xmlfile);
vector<User> addusers(string xmlfile);
#endif
