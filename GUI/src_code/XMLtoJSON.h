#ifndef XMLTOJSON_H
#define XMLTOJSON_H
#include <bits/stdc++.h>
#include "XMLtoTree.h"
using namespace std;
string XMLtoJSON(Node* node, int indent = 4);
string escapeJson(const string& s);
#endif
