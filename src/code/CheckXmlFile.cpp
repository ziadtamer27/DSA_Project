#include "..\\header\\CheckXmlFile.h"

void Checkxmlfile(string xmlfile){
    vector<string>errors;
    stack<string>st;
    bool valid=1;
    int line=1,errCount=0;

    for(int i=0;i<xmlfile.size();i++){
        if(xmlfile[i]=='\n') line++;

        // Closing tag
        if(xmlfile[i]=='<' && xmlfile[i+1]=='/'){
            i+=2;
            string temp="";
            while(xmlfile[i]!='>'){
                temp+=xmlfile[i];
                i++;
            }
            cout << "Closing tag found: </" << temp << ">" << endl;

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
            cout << "Opening tag found: <" << temp << ">" << endl;

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

    if(st.empty() && valid)
        cout << "XML file structure is valid.\n";
    else {
        cout << "XML file structure is NOT valid.\n";
        cout << "Total errors detected: " << errCount << endl;

        for (int i = 0; i < errors.size(); i++){
            cout << "Error " << i+1 << ": " << errors[i] << endl;
        }
    }
}
