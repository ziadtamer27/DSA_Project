#include "CheckXmlFile.h"

string Checkxmlfile(string xmlfile){
    vector<string>errors;
    stack<string>st;
    bool valid=1;
    int line=1,errCount=0;

    for(int i=0;i<xmlfile.size();i++){
        if(xmlfile[i]=='\n') line++;

        if(xmlfile[i]=='<' && xmlfile[i+1]=='/'){
            i+=2;
            string temp="";
            while(xmlfile[i]!='>'){
                temp+=xmlfile[i];
                i++;
            }

            if(!st.empty() && st.top()==temp) st.pop();
            else {
                valid = 0;
                errCount++;
                errors.push_back("Unmatched closing tag at line " + to_string(line));

                if(!st.empty()){
                    string last=st.top();
                    st.pop();
                    if(!st.empty() && st.top()==temp) st.pop();
                    else st.push(last);
                }
            }
        }

        else if(xmlfile[i]=='<'){
            i++;
            string temp="";
            while(xmlfile[i]!='>'){
                temp+=xmlfile[i];
                i++;
            }

            if(!st.empty()){
                if(st.top()!=temp) st.push(temp);
                else {
                    errCount++;
                    errors.push_back("Missing closing tag at line " + to_string(line));
                }
            }
            else st.push(temp);
        }
    }
    string output="";
    if(st.empty() && valid)
        output="XML file structure is valid.\n";
    else {
        output="XML file structure is NOT valid.\n";
        output+="Total errors detected: " + to_string(errCount) + "\n";

        for(const string& err : errors){
            output+=err + "\n";
        }
    }
    return output;
}
