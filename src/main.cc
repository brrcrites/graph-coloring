
#include "graph.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using GraphColoring::Graph;
using GraphColoring::Algorithm;

int main(int argc, char** argv)
{
	if(argc < 2) {
		cerr << "Usage: " << argv[0] << " file_input" << endl;
		return -1;
	}
	
	Graph graph(GraphColoring::kDSATUR);
	
	if(argc >= 3 && string(argv[2]) == "-t") {
		graph.parse_edge_matrix(argv[1]);
		if(graph.size() == 0) { return -2; }
	} else if(argc >= 3 && string(argv[2]) == "-e") {
		graph.parse_edge_list(argv[1]);
		if(graph.size() == 0) { return -2; }
	} else {
		cout << "No Graph Input Type Selected" << endl;
		return -1;	}
	
	graph.color();
	graph.print_chromatic();
	graph.write_graph();

	return 0;
}
