#include "CompressingXML.h"
string CompressingXMLFile(string xmlfile){
    string compressedXML = "";
    bool tag = false;
    for (int i = 0; i < xmlfile.length(); ++i) {
        if (xmlfile[i] == '<') {
            tag = true;
            compressedXML += xmlfile[i];
            continue;
        }
        if (xmlfile[i] == '>') {
            tag = false;
            compressedXML += xmlfile[i];
            continue;
        }

        if (tag) {
            compressedXML += xmlfile[i];
            continue;
        }

        // Outside tag or between tags
        if (xmlfile[i] == ' ' || xmlfile[i] == '\t' || xmlfile[i] == '\n') {
            int j = i;
            while (j + 1 < xmlfile.length() && (xmlfile[j + 1] == ' ' || xmlfile[j + 1] == '\t')) j++;

            if (xmlfile[j + 1] == '<') i = j; //skip
                
            else if (compressedXML.back() != '>') compressedXML += ' ';
        }

        // Not Tag or Space or \n 
        else {
            compressedXML += xmlfile[i];
        }
    }
    return compressedXML;
}

pair<string, map<unsigned char, string>> BytePairEncoding(string compressedXML) {
    map<unsigned char, string> pairToSymbol;
    unsigned char replace = 128; 
    string mostPair =" ";
    int max = 0;
    while(!(mostPair.empty() || max == 1) && replace < 255) {
        
        // Frequency Map
        map<string, int> pairFrequency;
        for (int i = 0; i < compressedXML.length()-1; i++) {
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
        //cout<<mostPair<<" "<<max<<endl;
        
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
        
        pairToSymbol[replace] = mostPair;
        compressedXML = compressedXML_new;
        replace++;
    }
    //cout<<compressedXML;
    return make_pair(compressedXML, pairToSymbol);
}
