#include "..\\header\\NetworkBuilder.h"
#include "..\\header\\NetworkAnalysis.h"
#include "..\\header\\CLI.h"
using namespace std;

int main(int argc, char** argv) {
    string xml = readFile("ClI_Mode//inputXMLfiles//sample.xml");
    cout << suggestUser(2,XMLtoGraph(xml)) << endl;
    //return run_cli(argc, argv);

auto graph = XMLtoGraph(xml);
auto users = addusers(xml);

auto MostActive = mostActiveUser(graph, users);

cout << "Most Active User\n";
cout << "ID: " << MostActive.first << endl;
cout << "Name: " << MostActive.second << endl;

}
