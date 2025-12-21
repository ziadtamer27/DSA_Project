#include "..\\header\\MinifyingXMLFile.h"

string Minifyingxmlfile(string& xmlfile) {
    string minified;
    bool inTag = false;
    for (char ch : xmlfile) {
        if (ch == '<') {
            inTag = true;
            minified += ch;
        } 
        else if (ch == '>') {
            inTag = false;
            minified += ch;
        } 
        else if (!isspace(ch) || inTag)
            minified += ch;
            
        else if(isspace(ch) && !inTag) {
            if(minified.back()=='>')
                continue;
            else if (!minified.empty() && !isspace(minified.back())) 
                minified += ' ';
        }
    }
    return minified;
}