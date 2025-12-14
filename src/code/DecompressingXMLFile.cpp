#include "..\\header\\DecompressingXML.h"

string DecompressingXMLFile(string compressed_file ,map<unsigned char , string> pairToSymbol){

    vector<unsigned char> symbols;
    for (auto kv : pairToSymbol) symbols.push_back(kv.first);
    reverse(symbols.begin(), symbols.end());

    for (unsigned char s : symbols) {
        string decompressed_file = "";
        for (int i = 0; i < compressed_file.size(); ++i) {
            unsigned char c = compressed_file[i];
            if (c == s) {
                decompressed_file += pairToSymbol[c];
            } 
            else {
                decompressed_file += compressed_file[i];
            }
        }
        compressed_file = decompressed_file;
    }

    return compressed_file;
}
