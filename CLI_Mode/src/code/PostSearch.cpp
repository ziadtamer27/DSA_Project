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
