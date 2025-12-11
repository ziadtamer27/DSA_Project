#include "..\\header\\CheckXmlFile.h"

void Checkxmlfile(string xmlfile){
    vector<string>errors;
    stack<string>st;
    bool valid=1;
    int line=1,errCount=0;
    for(int i=0;i<xmlfile.size();i++){
        if(xmlfile[i]=='\n')line++;
        if(xmlfile[i]=='<' && xmlfile[i+1]=='/'){
            i+=2;
            string temp="";
            while(xmlfile[i]!='>'){
                temp+=xmlfile[i];
                i++;
            }
            cout<<"close: "<<temp<<endl;

            if(!st.empty() && st.top()==temp)st.pop();
            else {
                valid=0;
                errCount++;
                errors.push_back("Unmatched Closing Tag in Line: "+to_string(line));
                if(!st.empty()){
                    st.pop();

                    if(!st.empty() && st.top()==temp)st.pop();
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
            cout<<"open: "<<temp<<endl;
            if(!st.empty()){
                if(st.top()!=temp)st.push(temp);
                else {
                    errCount++;
                    errors.push_back("Unmatched Closing Tag in Line: "+to_string(line));
                }
            }
            else st.push(temp);

        }
    }
    if(st.empty()&&valid) cout<<"Valid xmlfile file\n";
    else {
        cout<<"not Valid xmlfile file\n";
        cout<<"Number of errors: "<<errCount<<endl;
        for (int i = 0; i < errors.size(); i++)
        {
            cout<<"error: "<<i+1<<": "<<errors[i]<<endl;
        }
        
    }
}