#include <bits/stdc++.h>
#include "..\\header\\CheckXmlFile.h"
#include "..\\header\\XMLtoJSON.h"
#include "..\\header\\CompressingXML.h"
#include "..\\header\\NetworkBuilder.h"
#include "..\\header\\MinifyingXMLFile.h"
#include "..\\header\\XMLtoTree.h"


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

    ///////////////////////////////////////////
    // ALL FUNCTION CALLS CAN BE TESTED HERE //
    ///////////////////////////////////////////

    // 1. Minifying XML File
    string minifiedXML = Minifyingxmlfile(xmlfile);
    cout << "Minified XML:\n" << minifiedXML << endl;
    cout << "-----------------------------------\n\n";
    
    // 2. Converting XML to Tree Structure
    Node* root = XMLtoTree(xmlfile);
    printTree(root);
    cout << "-----------------------------------\n\n";
    
    // 3. Checking XML File
    Checkxmlfile(xmlfile);
    cout << "-----------------------------------\n\n";
    
    // 3. Compressing XML File
    string s = CompressingXMLFile(xmlfile);
    auto e = BytePairEncoding(s);
    cout << "Removed Spaces :\n\n" << s <<endl<<endl;
    cout << "Byte Pair :\n\n" << e.first <<endl<<endl;
    ofstream outFile("compresed_file.xml");
    outFile << e.first;
    outFile.close();
    cout << "-----------------------------------\n\n";
    

}


