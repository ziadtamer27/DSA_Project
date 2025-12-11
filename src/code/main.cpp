#include <bits/stdc++.h>
#include "..\\header\\CheckXmlFile.h"
#include "..\\header\\XMLtoJSON.h"
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
    
    //Checkxmlfile(xmlfile);
    string s = CompressingXMLFile(xmlfile);
    auto e = BytePairEncoding(s);
    cout << "Removed Spaces :\n\n" << s <<endl<<endl;
    cout << "Byte Pair :\n\n" << e.first <<endl<<endl;
    ofstream outFile("compresed_file.xml");
    outFile << e.first;
    outFile.close();
}


