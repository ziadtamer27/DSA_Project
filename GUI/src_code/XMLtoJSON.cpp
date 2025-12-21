#include "XMLtoJSON.h"

string escapeJson(const string& s) {
    string out;
    for (char c : s) {
        switch (c) {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            default: out += c; break;
        }
    }
    return out;
}

string XMLtoJSON(Node* node, int indent) {
    if (!node) return "";

    string space(indent, ' ');
    string json;
    

    string trimmed = node->data;
    trimmed.erase(0, trimmed.find_first_not_of(" \n\t"));
    trimmed.erase(trimmed.find_last_not_of(" \n\t") + 1);

    if (node->children.empty()) {
        json = space + "\"" + escapeJson(node->tag) + "\": \"" + escapeJson(trimmed) + "\"";
        return json;
    }


    bool isPlural = (node->tag == "users" || node->tag == "posts" || node->tag == "topics" || node->tag == "followers");


    if (isPlural)
        json = space + "\"" + escapeJson(node->tag) + "\": [\n";
    else
        json = space + "\"" + escapeJson(node->tag) + "\": {\n";

    for (size_t i = 0; i < node->children.size(); i++) {
        string childJson = XMLtoJSON(node->children[i], indent + 4);


        if (isPlural) {
            size_t pos = childJson.find(": ");
            if (pos != string::npos)
                childJson = space + "    " + childJson.substr(pos + 2); 
        }

        json += childJson;
        if (i != node->children.size() - 1) json += ",";
        json += "\n";
    }

    if (isPlural)
        json += space + "]";
    else
        json += space + "}";


    if (indent == 4) return "{\n" + json + "\n}";

    return json;
}
