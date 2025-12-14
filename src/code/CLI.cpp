#include <bits/stdc++.h>

#include "..\\header\\cli.h"
#include "..\\header\\CheckXmlFile.h"
#include "..\\header\\CompressingXML.h"
#include "..\\header\\DecompressingXML.h"
#include "..\\header\\MinifyingXMLFile.h"
#include "..\\header\\XMLtoTree.h"
#include "..\\header\\XMLtoJSON.h"
#include "../header/PrettifyingXMLFile.h"


using namespace std;

string readFile(const string &path)
{
    ifstream file(path);
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
  .\xml_editor verify     -i <input.xml> [-o <report.txt>]
  .\xml_editor format     -i <input.xml> -o <formatted.xml>
  .\xml_editor mini       -i <input.xml> -o <mini.xml>
  .\xml_editor json       -i <input.xml> -o <output.json>
  .\xml_editor compress   -i <input.xml> -o <out.comp>
  .\xml_editor decompress -i <in.comp>   -o <restored.xml>

)";
}

// ----------------- args parsing -----------------
struct Args
{
    string cmd;
    string inPath;
    string outPath; // optional for verify
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
        else
        {
            throw runtime_error("Unknown argument: " + tok);
        }
    }

    if (a.inPath.empty())
        throw runtime_error("Missing -i <input>.");
    if (a.cmd != "verify" && a.outPath.empty())
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
            string mini = Minifyingxmlfile(xml); // requires string&
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
        if (args.cmd == "prettify")
        {
            string xml = readFile(args.inPath);
            string p=PrettifyingXMLFile(xml);
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

        throw runtime_error("Unknown command: " + args.cmd);
    }
    catch (const exception &ex)
    {
        cerr << "Error: " << ex.what() << "\n\n";
        printUsage();
        return 1;
    }
}
