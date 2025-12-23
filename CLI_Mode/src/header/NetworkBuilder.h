#ifndef NetworkBuilder_H
#define NetworkBuilder_H
#include <bits/stdc++.h>
using namespace std;
class User;
vector<pair<int,vector<int>>> NetworkBuilder(string xmlfile);
vector<User> addusers(string xmlfile);
#endif