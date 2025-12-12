#include <bits/stdc++.h>
#include "..\\header\\CheckXmlFile.h"
#include "..\\header\\XMLtoJSON.h"
#include "..\\header\\CompressingXML.h"
#include "..\\header\\DecompressingXML.h"
#include "..\\header\\NetworkBuilder.h"
#include "..\\header\\MinifyingXMLFile.h"
#include "..\\header\\XMLtoTree.h"
#include "..\\header\\XMLtoJSON.h"


using namespace std;

string readFile(const string& path) {
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
    string xmlfile = readFile("..\\..\\inputXMLfiles\\sample.xml");

    ///////////////////////////////////////////
    // ALL FUNCTION CALLS CAN BE TESTED HERE //
    ///////////////////////////////////////////

    // 1. Minifying XML File
    string minifiedXML = Minifyingxmlfile(xmlfile);
    cout << "Minified XML:\n" << minifiedXML << endl;
    cout << "-----------------------------------\n\n";
    
    // 2. Converting XML to Tree Structure
    Node* root = XMLtoTree(xmlfile);
    printTree(root,0);
    cout << "-----------------------------------\n\n";

    // 3.Converting XML to JSON
    cout << "JSON Output\n" << XMLtoJSON(root);

    ofstream outjson("..\\..\\outputfiles\\JSON_output.json");
    outjson << XMLtoJSON(root);
    outjson.close();
    cout << "\n-----------------------------------\n\n";

    // 4. Checking XML File
    Checkxmlfile(xmlfile);
    cout << "-----------------------------------\n\n";
    
    // 5. Compressing XML File
    string s = CompressingXMLFile(xmlfile);
    auto e = BytePairEncoding(s);
    cout << "Removed Spaces :\n\n" << s <<endl<<endl;
    cout << "Byte Pair :\n\n" << e.first <<endl<<endl;
    ofstream outFile("..\\..\\outputfiles\\compresed_file.xml");
    outFile << e.first;
    outFile.close();
    cout << "-----------------------------------\n\n";

    // 6. Decompressing XML File
    string decompressed = DecompressingXMLFile(e.first, e.second);
    cout << "Decompressed XML :\n\n" << decompressed << endl<<endl;
    ofstream outFile2("..\\..\\outputfiles\\decompressed_file.xml");
    outFile2 << decompressed;
    outFile2.close();
    cout << "-----------------------------------\n\n";

}



