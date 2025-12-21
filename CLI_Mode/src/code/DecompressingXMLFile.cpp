#include "..\\header\\DecompressingXML.h"
#include "..\\header\\PrettifyingXMLFile.h"


string DecompressingXMLFile(string compressed_file ,map<unsigned char , string> pairToSymbol){

    vector<unsigned char> symbols;
    for (auto v : pairToSymbol) symbols.push_back(v.first);
    reverse(symbols.begin(), symbols.end());
    //for(auto c : symbols) cout<<c<<endl;
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
    string c ="";
    for (int i = 0; i < compressed_file.size(); i++) {
        if(compressed_file[i] == '>' && compressed_file[i+1] == '<'){
            c+=compressed_file[i];
            c+="\n";
        }
        else if(compressed_file[i] == '<' && !c.empty() && c.back() == '>'){
            c+="\n";
            c+=compressed_file[i];
        }
        else{
            c+=compressed_file[i];
        }
    }
    return PrettifyingXMLFile(c);
}
