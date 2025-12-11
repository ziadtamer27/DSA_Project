#include <bits/stdc++.h>
#include "..\\header\\CheckXmlFile.h"
#include "..\\header\\CompressingXML.h"
using namespace std;

string readFile(const string& path) {
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
    string xmlfile = readFile("..\\..\\input\\sample.xml");
    Checkxmlfile(xmlfile);
    while(1);
}


