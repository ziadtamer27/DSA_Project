#include "../header/PrettifyingXMLFile.h"
#include "..//header//MinifyingXMLFile.h"

using namespace std;

static inline string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\n\r");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\n\r");
    return s.substr(a, b - a + 1);
}

string PrettifyingXMLFile(string xml) {
    string s;
    int n = xml.size();
    int i = 0;
    int level = 0;
    bool f = false;

    while (i < n) {
        if (xml[i] == '<') {
            int j = xml.find('>', i);
            string tag = xml.substr(i, j - i + 1);
            bool isClosing = (tag.size() > 1 && tag[1] == '/');

            if (isClosing) level--;

            if (!isClosing ) {
                int nextPos = j + 1;
                if (nextPos < n && xml[nextPos] != '<') {
                    int textStart = nextPos;
                    int textEnd = (int)xml.find('<', textStart);
                    if (textEnd == string::npos) textEnd = n;

                    int closePos = textEnd;
                    if (closePos < n && xml[closePos] == '<' && closePos + 1 < n && xml[closePos + 1] == '/') {
                        string inside = tag.substr(1, tag.size() - 2);
                        string tagName;
                        for (char c : inside) {
                            if (isspace((unsigned char)c)) break;
                            tagName.push_back(c);
                        }

                        int closeEnd = (int)xml.find('>', closePos);
                        if (closeEnd != (int)string::npos) {
                            string closingTag = xml.substr(closePos + 2, closeEnd - closePos - 2);

                            if (closingTag == tagName) {
                                string openTag = tag; 
                                string closeTag = xml.substr(closePos, closeEnd - closePos + 1);
                                string text = xml.substr(textStart, textEnd - textStart);
                                string innerTrim = trim(text);

                                if (innerTrim.find('\n') == string::npos && innerTrim.size() <= 80) {

                                    if (!s.empty()) s += '\n';
                                    s.append(level * 4, ' ');
                                    s += openTag;
                                    s += innerTrim;
                                    s += closeTag;
                                } else {

                                    vector<string> lines;
                                    size_t p = 0;
                                    while (p < text.size()) {
                                        size_t nl = text.find('\n', p);
                                        if (nl == string::npos) nl = text.size();
                                        string line = text.substr(p, nl - p);
                                        lines.push_back(trim(line));
                                        p = nl + 1;
                                    }

                                    if (!s.empty()) s += '\n';
                                    s.append(level * 4, ' ');
                                    s += openTag;
                                    for (const string &ln : lines) {
                                        if (ln.empty()) continue;
                                        s += '\n';
                                        s.append((level + 1) * 4, ' ');
                                        s += ln;
                                    }
                                    s += '\n';
                                    s.append(level * 4, ' ');
                                    s += closeTag;
                                }

                                i = closeEnd + 1;
                                f = false;
                                continue;
                            }
                        }
                    }
                }
            }

            if (!s.empty() && !f) s += '\n';
            s.append(level * 4, ' ');
            s += tag;
            f = false;

            if (!isClosing ) ++level;

            i = j + 1;
        } else {
            int j = (int)xml.find('<', i);
            if (j == (int)string::npos) j = n;
            string text = xml.substr(i, j - i);
            string t = trim(text);
            if (!t.empty()) {
                if (t.find('\n') == string::npos && t.size() < 200) {
                    s += t;
                    f = true;
                } else {
                    s += '\n';
                    s.append(level * 4, ' ');
                    s += t;
                    f = false;
                }
            }
            i = j;
        }
    }

    return s;
}