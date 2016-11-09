#include "../Header/graph_color.h"
#include "../Header/my_dsatur.h"
#include "../Header/my_mcs.h"
#include "../Header/my_lmxrlf.h"
#include "../Header/my_hybrid_dsatur.h"
#include "../Header/my_hybrid.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using GraphColoring::dsatur;
using GraphColoring::mcs;
using GraphColoring::lmxrlf;
using GraphColoring::hybrid_dsatur;
using GraphColoring::hybrid;
using GraphColoring::GraphColor;
using GraphColoring::Algorithm;

int main(int argc, char** argv)
{
    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " file_input" << endl;
        return -1;
    }
    
    GraphColor *graph = new dsatur();

    if(argc >= 3 && string(argv[2]) == "-m") {
        graph->parse_edge_matrix(argv[1]);
        if(graph->size() == 0) { return -2; }
    } else if(argc >= 3 && string(argv[2]) == "-l") {
        graph->parse_edge_list(argv[1]);
        if(graph->size() == 0) { return -2; }
    } else {
        cout << "No Graph Input Type Selected" << endl;
        return -1;  }

    graph->color();
    graph->print_chromatic();
    graph->verify();
    graph->write_graph();

    return 0;
}
