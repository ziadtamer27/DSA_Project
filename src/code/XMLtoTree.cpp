#include "..\\header\\XMLtoTree.h"

class Node {
public:
    string tag;
    string data;
    vector<Node*> children;
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

