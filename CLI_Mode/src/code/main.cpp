#include "..\\header\\NetworkBuilder.h"
#include "..\\header\\NetworkAnalysis.h"
#include "..\\header\\CLI.h"
using namespace std;

int main(int argc, char** argv) {
    string xml = readFile("ClI_Mode//inputXMLfiles//sample.xml");
    cout << suggestUser(2,XMLtoGraph(xml)) << endl;
    //return run_cli(argc, argv);
}
