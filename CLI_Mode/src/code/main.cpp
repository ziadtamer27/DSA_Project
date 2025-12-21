#include <bits/stdc++.h>
#include "..\\header\\CLI.h"
#include "..\\header\\PostSearch.h"
using namespace std;
int main(int argc, char** argv) {
    // return run_cli(argc, argv);
    string filename;
    string word;

    cin >> filename;

    cin >> word;

    ifstream file(filename);

    stringstream buffer;
    buffer << file.rdbuf();
    string xml_content = buffer.str();
    file.close();
    string result = PostSearchWord(xml_content, word);
    cout << result << endl;

}
