#include "..\\header\\Network_JPG.h"

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
    file << "  node [shape=circle, style=filled, color=lightblue];\n";

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

    system("\"CLI_Mode\\Graphviz\\bin\\dot.exe\" -Tjpg network.dot -o network.jpg");
}
