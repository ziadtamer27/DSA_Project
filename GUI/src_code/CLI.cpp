#include <bits/stdc++.h>

#include "CLI.h"
#include "CheckXmlFile.h"
#include "CompressingXML.h"
#include "DecompressingXML.h"
#include "MinifyingXMLFile.h"
#include "XMLtoTree.h"
#include "XMLtoJSON.h"
#include "PrettifyingXMLFile.h"
#include "Network_JPG.h"
#include "NetworkBuilder.h"
#include "NetworkAnalysis.h"
#include "PostSearch.h"

using namespace std;

string readFile(const string &path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: file not found or cannot be opened -> " << path << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

static string readFileBinary(const string &path)
{
    ifstream file(path, ios::in | ios::binary);
    if (!file.is_open())
        throw runtime_error("Cannot open input file: " + path);
    return string((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
}

static void writeFileBinary(const string &path, const string &data)
{
    ofstream file(path, ios::out | ios::binary | ios::trunc);
    if (!file.is_open())
        throw runtime_error("Cannot open output file: " + path);
    file.write(data.data(), (streamsize)data.size());
}
static void writeFileText(const string &path, const string &content)
{
    ofstream file(path, ios::out | ios::trunc | ios::binary);
    if (!file.is_open())
        throw runtime_error("Cannot open output file: " + path);
    file << content;
}

static bool fileExists(const string &path)
{
    ifstream f(path, ios::in | ios::binary);
    return f.good();
}

static void printUsage()
{
    cout <<
        R"(Usage:
  .\xml_editor verify             -i <input.xml> [-o <report.txt>]          Checks XML consistency & reports errors
  .\xml_editor verify             -i <input.xml> -f -o <fixed.xml>          Repairs mismatched/missing tags
  .\xml_editor format             -i <input.xml> -o <formatted.xml>         Beautifies XML with indentation
  .\xml_editor mini               -i <input.xml> -o <mini.xml>              Removes whitespace to reduce size
  .\xml_editor json               -i <input.xml> -o <output.json>           Converts XML → JSON
  .\xml_editor compress           -i <input.xml> -o <out.comp>              Custom compression (BPE-like)
  .\xml_editor decompress         -i <in.comp> -o <restored.xml>            Restores full XML
  .\xml_editor draw               -i <input.xml> -o <graph.jpg>             Builds network graph from users/followers
  .\xml_editor most_active        -i <input.xml>                            Prints user with most outgoing connections
  .\xml_editor most_influencer    -i <input.xml>                            Prints user with most followers
  .\xml_editor mutual             -i <input.xml> -ids <id1,id2,...>         Prints common followers
  .\xml_editor suggest            -i <input.xml> -id <user_id>              Recommended users to follow
  .\xml_editor search -w <word>   -i <input.xml>                            Writes a list of posts where the word was mentioned
  .\xml_editor search -t <topic>  -i <input.xml>                            Writes a list of posts where the topic was mentioned
)";
}

struct Args
{
    string cmd;
    string inPath;
    string outPath;
    string word;
    string topic;
    int id = -1;
    vector<int> ids;
};

static Args parseArgs(int argc, char **argv)
{
    if (argc < 2)
        throw runtime_error("Missing command. Use --help");

    Args a;
    a.cmd = argv[1];

    for (int i = 2; i < argc; i++)
    {
        string tok = argv[i];
        if (tok == "-h" || tok == "--help")
        {
            printUsage();
            exit(0);
        }
        else if (tok == "-i" && i + 1 < argc)
        {
            a.inPath = argv[++i];
        }
        else if (tok == "-o" && i + 1 < argc)
        {
            a.outPath = argv[++i];
        }
        else if (tok == "-w" && i + 1 < argc)
        {
            a.word = argv[++i];
        }
        else if (tok == "-t" && i + 1 < argc) // <-- handle topic
        {
            a.topic = argv[++i];
        }
        else if (tok == "-id" && i + 1 < argc)
        {
            a.id = stoi(argv[++i]);
        }
        else if (tok == "-ids" && i + 1 < argc)
        {
            string s = argv[++i];
            stringstream ss(s);
            string x;
            while (getline(ss, x, ','))
                a.ids.push_back(stoi(x));
        }
        else
        {
            throw runtime_error("Unknown argument: " + tok);
        }
    }

    if (a.inPath.empty())
        throw runtime_error("Missing -i <input>.");
    if ((a.cmd == "format" || a.cmd == "mini" || a.cmd == "json" ||
         a.cmd == "compress" || a.cmd == "decompress" || a.cmd == "draw") &&
        a.outPath.empty())
        throw runtime_error("Missing -o <output> for command: " + a.cmd);

    return a;
}

// ----------------- dictionary meta (unsigned char -> string) -----------------
using DictType = map<unsigned char, string>;

static string escapeMeta(const string &s)
{
    string out;
    out.reserve(s.size());
    for (char c : s)
    {
        if (c == '\\')
            out += "\\\\";
        else if (c == '\t')
            out += "\\t";
        else if (c == '\n')
            out += "\\n";
        else
            out += c;
    }
    return out;
}

static string unescapeMeta(const string &s)
{
    string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == '\\' && i + 1 < s.size())
        {
            char n = s[i + 1];
            if (n == '\\')
            {
                out += '\\';
                i++;
            }
            else if (n == 't')
            {
                out += '\t';
                i++;
            }
            else if (n == 'n')
            {
                out += '\n';
                i++;
            }
            else
                out += s[i];
        }
        else
        {
            out += s[i];
        }
    }
    return out;
}

static void saveDictMeta(const string &metaPath, const DictType &dict)
{
    ofstream f(metaPath, ios::out | ios::trunc | ios::binary);
    if (!f.is_open())
        throw runtime_error("Cannot write meta file: " + metaPath);

    for (const auto &kv : dict)
    {
        f << (int)kv.first << "\t" << escapeMeta(kv.second) << "\n";
    }
}

static DictType loadDictMeta(const string &metaPath)
{
    ifstream f(metaPath, ios::in | ios::binary);
    if (!f.is_open())
        throw runtime_error("Cannot open meta file: " + metaPath);

    DictType dict;
    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;

        size_t tab = line.find('\t');
        if (tab == string::npos)
            continue;

        string left = line.substr(0, tab);
        string right = line.substr(tab + 1);

        int code = stoi(left);
        if (code < 0 || code > 255)
            continue;

        dict[(unsigned char)code] = unescapeMeta(right);
    }
    return dict;
}

// ----------------- CLI runner -----------------
int run_cli(int argc, char **argv)
{
    try
    {
        Args args = parseArgs(argc, argv);

        // verify
        if (args.cmd == "verify")
        {
            string xml = readFile(args.inPath);
            string report = Checkxmlfile(xml);

            if (args.outPath.empty())
                cout << report << "\n";
            else
                writeFileText(args.outPath, report);
            return 0;
        }

        // mini
        if (args.cmd == "mini")
        {
            string xml = readFile(args.inPath);
            string mini = Minifyingxmlfile(xml);
            writeFileText(args.outPath, mini);
            return 0;
        }

        // json
        if (args.cmd == "json")
        {
            string xml = readFile(args.inPath);
            Node *root = XMLtoTree(xml);
            string json = XMLtoJSON(root);
            writeFileText(args.outPath, json);
            return 0;
        }

        // prettify
        if (args.cmd == "format")
        {
            string xml = readFile(args.inPath);
            string p = PrettifyingXMLFile(xml);
            writeFileText(args.outPath, p);
            return 0;
        }

        // compress (single file: out.comp contains dict + data)
        if (args.cmd == "compress")
        {
            string xml = readFile(args.inPath);

            string s = CompressingXMLFile(xml);
            auto e = BytePairEncoding(s); // e.first = compressed data, e.second = dict

            ofstream out(args.outPath, ios::binary | ios::trunc);
            if (!out.is_open())
                throw runtime_error("Cannot open output file: " + args.outPath);

            // write dict size
            uint32_t dictSize = (uint32_t)e.second.size();
            out.write(reinterpret_cast<const char *>(&dictSize), sizeof(dictSize));

            // write dict entries: [symbol][len][string bytes]
            for (auto &kv : e.second)
            {
                unsigned char symbol = kv.first;
                uint32_t len = (uint32_t)kv.second.size();
                out.write(reinterpret_cast<const char *>(&symbol), sizeof(symbol));
                out.write(reinterpret_cast<const char *>(&len), sizeof(len));
                out.write(kv.second.data(), len);
            }

            // write compressed data bytes
            uint32_t dataSize = (uint32_t)e.first.size();
            out.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));
            out.write(e.first.data(), dataSize);

            out.close();
            return 0;
        }

        // decompress (single file: in.comp contains dict + data)
        if (args.cmd == "decompress")
        {
            ifstream in(args.inPath, ios::binary);
            if (!in.is_open())
                throw runtime_error("Cannot open input file: " + args.inPath);

            DictType dict;

            // read dict size
            uint32_t dictSize = 0;
            in.read(reinterpret_cast<char *>(&dictSize), sizeof(dictSize));

            // read dict entries
            for (uint32_t i = 0; i < dictSize; ++i)
            {
                unsigned char symbol;
                uint32_t len;
                in.read(reinterpret_cast<char *>(&symbol), sizeof(symbol));
                in.read(reinterpret_cast<char *>(&len), sizeof(len));

                string value(len, '\0');
                in.read(&value[0], len);

                dict[symbol] = value;
            }

            // read compressed data size + data
            uint32_t dataSize = 0;
            in.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));

            string comp(dataSize, '\0');
            in.read(&comp[0], dataSize);

            in.close();

            // EXACT same algorithm call as main.cpp
            string restored = DecompressingXMLFile(comp, dict);

            writeFileText(args.outPath, restored);
            return 0;
        }

        if (args.cmd == "draw")
        {
            Network_JPG(XMLtoGraph(readFile(args.inPath)));
            cout << "Network graph generated as network.jpg\n";
            return 0;
        }
        if (args.cmd == "most_active")
        {
            auto MostActive = mostActiveUser(
                XMLtoGraph(readFile(args.inPath)),
                addusers(readFile(args.inPath)));
            cout << "Most Active User\n";
            cout << "ID: " << MostActive.first << endl;
            cout << "Name: " << MostActive.second << endl;
            return 0;
        }
        if (args.cmd == "most_influencer")
        {
            cout << mostInfluencer(
                        XMLtoGraph(readFile(args.inPath)),
                        addusers(readFile(args.inPath)))
                 << "\n";
            return 0;
        }
        if (args.cmd == "mutual")
        {
            if (args.ids.size() < 2)
                throw runtime_error("mutual requires -ids id1,id2");

            cout << mutualUsers(args.ids[0], args.ids[1],
                                XMLtoGraph(readFile(args.inPath)))
                 << "\n";
            return 0;
        }
        if (args.cmd == "suggest")
        {
            if (args.id == -1)
                throw runtime_error("suggest requires -id");

            cout << suggestUser(args.id,
                                XMLtoGraph(readFile(args.inPath)))
                 << "\n";
            return 0;
        }
        if (args.cmd == "search")
        {
            if (args.word.empty() && args.topic.empty())
                throw runtime_error("search requires -w <word> or -t <topic>");

            string results;
            string xml = readFile(args.inPath);
            if (!args.word.empty())
            {
                results = PostSearchWord(xml, args.word);
            }
            else if (!args.topic.empty())
            {
                results = PostSearchTopic(xml, args.topic);
            }

            cout << results << "\n";
            return 0;
        }

        throw runtime_error("Unknown command: " + args.cmd);
    }
    catch (const exception &ex)
    {
        cerr << "Error: " << ex.what() << "\n\n";
        printUsage();
        return 1;
    }
}