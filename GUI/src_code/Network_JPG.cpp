#include "Network_JPG.h"

void Network_JPG(const vector<pair<int, vector<int>>> &connections)
{
    ofstream file("network.dot");
    if (!file)
    {
        cerr << "Failed to create DOT file\n";
        return;
    }

    file << "digraph Network {\n";
    file << "  rankdir=LR;\n";
    file << "  node [\n"
        "    shape=circle,\n"
        "    style=\"filled,rounded\",\n"
        "    fillcolor=\"#1e293b\",\n"
        "    color=\"#3b82f6\",\n"
        "    penwidth=1.5,\n"
        "    fontname=\"Segoe UI\",\n"
        "    fontsize=11,\n"
        "    fontcolor=\"#e2e8f0\"\n"
        "  ];\n";


    for (auto &user : connections)
    {
        int userId = user.first;
        file << "  " << userId << ";\n";

        for (int follower : user.second)
        {
            file << "  " << follower << " -> " << userId << ";\n";
        }
    }

    file << "}\n";
    file.close();

    system("\"Graphviz\\bin\\dot.exe\" -Tjpg network.dot -o network.jpg");
}
