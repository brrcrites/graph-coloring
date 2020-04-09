#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <gflags/gflags.h>

#include "../Header/parse.hpp"
#include "../Header/coloring_algorithm.hpp"
#include "../Header/dsatur.hpp"
#include "../Header/mcs.hpp"
#include "../Header/lmxrlf.hpp"
#include "../Header/hybrid_dsatur.hpp"
#include "../Header/hybrid_lmxrlf.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostringstream;

using GraphColoring::Dsatur;
using GraphColoring::Mcs;
using GraphColoring::Lmxrlf;
using GraphColoring::HybridDsatur;
using GraphColoring::HybridLmxrlf;
using GraphColoring::GraphColor;

DEFINE_string(graph, "", "The path to the graph file to be colored");
DEFINE_string(algorithm, "hybrid dsatur", "The algorithm to execute on chosen benchmark");
DEFINE_string(format, "", "The format of the input graph to be parsed");

GraphColor* parse_algorithm_flag(map<string,vector<string>> graph) {
    if(FLAGS_algorithm == "dsatur") {
        return new Dsatur(graph);
    } else if(FLAGS_algorithm == "mcs") {
        return new Mcs(graph);
    } else if(FLAGS_algorithm == "lmxrlf") {
        return new Lmxrlf(graph);
    } else if(FLAGS_algorithm == "hybrid dsatur") {
        return new HybridDsatur(graph);
    } else if(FLAGS_algorithm == "hybird lmxrlf") {
        return new HybridLmxrlf(graph);
    }
    return nullptr;
}

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    string banner = "This program attempts to color an input graph using one of the available coloring algorithms";
    string usage = "\tUsage: ./color --graph=path_to_graph --format=(matrix|list) [--algorithm=(dsatur|mcs|lmxrlf|hybrid dsatur|hybrid lmxrlf)]";
    gflags::SetUsageMessage(banner + "\n" + usage);

    if(FLAGS_graph == "") {
        gflags::ShowUsageWithFlags(argv[0]);
        return -1;
    }

    map<string,vector<string>> input_graph;
    if(FLAGS_format == "matrix") {
        input_graph = parse_edge_matrix(FLAGS_graph);
    } else if(FLAGS_format == "list") {
        input_graph = parse_edge_list(FLAGS_graph);
    } else {
        cerr << "No Graph Input Type Selected" << endl;
        cerr << "\t* Use \"--format=matrix\" command line flag for edge matrix inputs" << endl;
        cerr << "\t* Use \"--format=list\" command line flag for edge list inputs" << endl;
        return -1;
    }

    if(input_graph.size() == 0) { 
        cerr << "Stopping due to failure to parse input file" << endl;
        return -2; 
    }

    GraphColor *graph = parse_algorithm_flag(input_graph);
    if(!graph) {
        cerr << "Please entere a valid algorithm (DSATUR, MCS, lmXRLF, Hybrid DSATUR, or Hybird lmXRLF)" << endl;
        return -1;
    }

    graph->color();
    graph->print_chromatic();
    if(!graph->is_valid()) {
        cerr << "Graph coloring is invalid" << endl;
    }

    return 0;
}

