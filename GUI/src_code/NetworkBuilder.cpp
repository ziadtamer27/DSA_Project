#include "NetworkBuilder.h"


vector<User> addusers(string xmlfile){
    vector<User> users;
    for(int i=0;i<xmlfile.size();i++){
        if(xmlfile[i]=='<'){
            i++;
            string tag="";
            while(xmlfile[i]!='>'){
                tag+=xmlfile[i];
                i++;
            }
            if(tag=="user"){
                bool flag=1;
                string name="", id="";
                while(true){
                    i++;
                    if(xmlfile[i]=='<'){
                        i++;
                        string innerTag="";
                        while(xmlfile[i]!='>'){
                            innerTag+=xmlfile[i];
                            i++;
                        }
                        if(innerTag=="name"){
                            i++;
                            while(xmlfile[i]!='<'){
                                name+=xmlfile[i];
                                i++;
                            }
                        }
                        else if(innerTag=="id" && flag){
                            i++;
                            while(xmlfile[i]!='<'){
                                id+=xmlfile[i];
                                i++;
                            }
                            flag=0;
                        }
                        else if(innerTag=="/user"){
                            break;
                        }
                    }
                }
                User user(name, stoi(id));
                users.push_back(user);
            }
        }
    }
    return users;
}

vector<pair<int,vector<int>>> XMLtoGraph(string xmlfile) {
    vector<pair<int,vector<int>>> connections;
    for(int i=0;i<xmlfile.size();i++){
        if(xmlfile[i]=='<'){
            i++;
            string tag="";
            while(xmlfile[i]!='>'){
                tag+=xmlfile[i];
                i++;
            }
            if(tag=="user"){
                string id="";
                while(true){
                    i++;
                    if(xmlfile[i]=='<'){
                        i++;
                        string innerTag="";
                        while(xmlfile[i]!='>'){
                            innerTag+=xmlfile[i];
                            i++;
                        }
                        if(innerTag=="id"){
                            i++;
                            while(xmlfile[i]!='<'){
                                id+=xmlfile[i];
                                i++;
                            }
                        }
                        else if(innerTag=="followers"){
                            vector<int> conns;
                            while(true){
                                i++;
                                if(xmlfile[i]=='<'){
                                    i++;
                                    string connTag="";
                                    while(xmlfile[i]!='>'){
                                        connTag+=xmlfile[i];
                                        i++;
                                    }
                                    if(connTag=="id"){
                                        string connId="";
                                        i++;
                                        while(xmlfile[i]!='<'){
                                            connId+=xmlfile[i];
                                            i++;
                                        }
                                        conns.push_back(stoi(connId));
                                    }
                                    else if(connTag=="/followers"){
                                        break;
                                    }
                                }
                            }
                            connections.push_back({stoi(id), conns});
                        }
                        else if(innerTag=="/user"){
                            break;
                        }
                    }
                }
            }
        }
    }
    return connections;
}

