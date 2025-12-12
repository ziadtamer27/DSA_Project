#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string tag;
    string data;
    vector<Node*> children;
    bool leaf=1;
    Node(string t) {
        tag = t;
        data = "";
    }
    void setData(string d) {
        data = d;
    }
    void addChild(Node* child) {
        children.push_back(child);
    }
};
void printTree(Node* node,int depth);
Node* XMLtoTree(string xmlfile);