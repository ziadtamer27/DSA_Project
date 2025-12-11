#include "..\\header\\CompressingXML.h"
string CompressingXMLFile(string xmlfile){
    string compressedXML;
    for (int i = 0; i < xmlfile.length(); i++) {
        if (xmlfile[i] == '<') {
            compressedXML += xmlfile[i];
        } else if (xmlfile[i] == '>') {
            compressedXML += xmlfile[i];
        } else if (xmlfile[i] == ' ' || xmlfile[i] == '\n' || xmlfile[i] == '\t') {
            continue;
        } else {
            compressedXML += xmlfile[i];
        }
    }
    // cout << compressedXML << endl;
    return compressedXML;
}

pair<string, map<string, char>> BytePairEncoding(string compressedXML) {
    map<string, char> pairToSymbol;
    char replace = 128; 
    string mostPair =" ";
    int max = 0;
    while(!(mostPair.empty() || max == 1)) {
        
        // Frequency Map
        map<string, int> pairFrequency;
        for (int i = 0; i < compressedXML.length() - 1; i++) {
            string pair = "";
            pair += compressedXML[i];
            pair += compressedXML[i + 1];
            pairFrequency[pair]++;
        }

        // Most repeated pair
        mostPair = "";
        max = 1;
        for (auto p : pairFrequency) {
            if (p.second > max) {
                max = p.second;
                mostPair = p.first;
            }
        }
        cout<<mostPair<<" "<<max<<endl;
        
        // Replace 
        string compressedXML_new = "";
        for (int i = 0; i < compressedXML.length(); i++) {
            if (compressedXML[i] == mostPair[0] && compressedXML[i + 1] == mostPair[1]) {
                compressedXML_new += replace;
                i++;
            } else {
                compressedXML_new += compressedXML[i];
            }
        }
        
        pairToSymbol[mostPair] = replace;
        compressedXML = compressedXML_new;
        replace++;
    }
    
    return make_pair(compressedXML, pairToSymbol);
}