#include "..\\header\\XMLtoTree.h"

Node* XMLtoTree(string xmlfile){
    Node* root = nullptr;
    stack<Node*> nodeStack;
    for (int i = 0; i < xmlfile.size(); i++)
    {
        if (xmlfile[i] == '<') {
            if (xmlfile[i + 1] == '/') {
                i += 2;
                string closingTag = "";
                while (xmlfile[i] != '>') {
                    closingTag += xmlfile[i];
                    i++;
                }
                if (!nodeStack.empty()) {
                    Node* completedNode = nodeStack.top();
                    nodeStack.pop();
                    if (!nodeStack.empty()) {
                        nodeStack.top()->addChild(completedNode);
                    } else {
                        root = completedNode;
                    }
                }
            } else {
                i++;
                string openingTag = "";
                while (xmlfile[i] != '>') {
                    openingTag += xmlfile[i];
                    i++;
                }
                Node* newNode = new Node(openingTag);
                nodeStack.push(newNode);
            }
        } else {
            string textData = "";
            while (i < xmlfile.size() && xmlfile[i] != '<') {
                textData += xmlfile[i];
                i++;
            }
            i--;
            if (!nodeStack.empty()) {
                nodeStack.top()->setData(textData);
            }
        }
    }
    return root;
}

void printTree(Node* node, int depth = 0) {
    if (node == nullptr) return;
    cout << string(depth * 2, ' ') << "<" << node->tag << ">";
    if (!node->data.empty()) {
        cout << node->data;
    }
    cout << endl;
    for (Node* child : node->children) {
        printTree(child, depth + 1);
    }
    cout << string(depth * 2, ' ') << "</" << node->tag << ">" << endl;
}
