#include "..\\header\\PostSearch.h"
#include "..\\header\\MinifyingXMLFile.h"

string PostSearchWord(string xml_file, string word) {
    xml_file = Minifyingxmlfile(xml_file);
    string posts = "";
    string post = "";
    bool flag = false;
    string body = "";
    int counter = 1;
    for (int i = 0; i < xml_file.size(); i++) {
        if (xml_file[i] == '<') {
            flag = true;
        }
        else if (flag) {
            body += xml_file[i];
        }
        if (xml_file[i] == '>') {
            if (body == "body>") {
                int x = i + 1;
                bool wordFound = false;
                post = "";
                while (xml_file[x] != '<') {
                        string compare = "";
                        while (xml_file[x] != ' ' && xml_file[x] != '<') {
                            compare += xml_file[x];
                            post += xml_file[x];
                            x++;
                        }
                        if (compare == word)
                            wordFound = true;
                        post += xml_file[x++];
                }
                if (wordFound) {
                    posts += "Post "+ to_string(counter++)+":" + "\n";
                    posts += post + "\n";
                }
            }
            body = "";
            flag = false;
        }
    }
    if(posts.size()>0)return posts;
    else return "Word Not Found In Any Post";
}

string PostSearchTopic(string xml_file, string topic) {
    xml_file = Minifyingxmlfile(xml_file);
    topic = topic + ' ';
    string posts = "";
    string post = "";
    string t ="";
    bool flag = false;
    string tag = "";
    int counter = 1;
    for (int i = 0; i < xml_file.size(); i++) {
        if (xml_file[i] == '<') {
            flag = true;
        }
        else if (flag) {
            tag += xml_file[i];
        }
        if (xml_file[i] == '>') {
            if (tag == "body>") {
                int x = i + 1;
                post = "";
                while (xml_file[x] != '<') {
                        post += xml_file[x++];
                }
            }
            if (tag == "topic>")
            {
                int x = i + 1;
                t = "";
                while (xml_file[x] != '<') {
                    t += xml_file[x++];
                }
                if(topic == t){
                    posts += "Post "+ to_string(counter++)+":" + "\n";
                    posts += post + "\n";
                }
            }
            flag = false;
            tag = "";
        }
    }
    if(posts.size()>0)return posts;
    else return "topic Not Found In Any Post";
}
