
#ifndef _GLOBAL_GUARD_
#define _GLOBAL_GUARD_
#include "parse.h"
#include "dsatur.h"
#include "smallest_stack.h"
#include "chordal.h"
#include "hybrid.h"
#endif

#ifndef _TABU_GUARD_
#define _TABU_GUARD_
#include "tabucol.h"
#endif

#ifndef _LMXRLF_GUARD_
#define _LMXRLF_GUARD_
#include "lmxrfl.h"
#endif

using std::map;
using std::cout;
using std::cerr;
using std::string;
using std::vector;

void correct(map< string,vector<string> > Graph,map< string,int> Colors)
{
	if(verify(Graph,Colors))
	{
		cout << "Graph Correct" << endl;
	}
	else
	{
		cout << "Graph Incorrect" << endl;
	}
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cerr << "Usage: " << argv[0] << " file_input" << endl;
		return -1;
	}
	
	map< string, vector<string> > Graph;
	
	if(argc >= 3 && string(argv[2]) == "-t")
	{
		cout << "String Parse" << endl;
		Graph = parse_edge_matrix(argv[1]);
		if(Graph.size() == 0)
			return -2;
	}
	else if(argc >= 3 && string(argv[2]) == "-e")
	{
		Graph = parse_edge_list(argv[1]);
		if(Graph.size() == 0)
			return 2;
	}
	else
	{
		vector< vector<string> > Input = get_input(argv[1]);
		if(Input.size() == 0)
			return -2;
		Graph = build_graph(Input);
	}
	
	//********************
	//**** Run Tests *****
	//********************
	srand(time(NULL));

	map< string,int > Colors = dsatur(Graph);
	print_fullstats(Colors,start,end,"DSATUR");
	cout << endl;

	Colors = smallest_stack(Graph);
	print_fullstats(Colors,start,end,"Smallest Stack");
	cout << endl;

	Colors = chordal(Graph);
	print_fullstats(Colors,start,end,"Chordal");
	cout << endl;

	Colors = lmxrlf_base(Graph,Graph.size());
	print_fullstats(Colors,start,end,"lmXRLF #1");
	cout << endl;

	Colors = lmxrlf_base(Graph,Graph.size());
	print_fullstats(Colors,start,end,"lmXRLF #2");
	cout << endl;

	Colors = lmxrlf_base(Graph,Graph.size());
	print_fullstats(Colors,start,end,"lmXRLF #3");
	cout << endl;

	start = clock();
	Colors = hybrid(Graph,Graph.size()/2);
	end = clock();
	print_fullstats(Colors,start,end,"Hybrid #1");
	cout << endl;

	start = clock();
	Colors = hybrid(Graph,Graph.size()/2);
	end = clock();
	print_fullstats(Colors,start,end,"Hybrid #2");
	cout << endl;

	start = clock();
	Colors = hybrid(Graph,Graph.size()/2);
	end = clock();
	print_fullstats(Colors,start,end,"Hybrid #3");
	cout << endl;

	start = clock();
	Colors = hybrid_dsatur(Graph);
	end = clock();
	print_fullstats(Colors,start,end,"Hybrid DSATUR #1");
	cout << endl;

	start = clock();
	Colors = hybrid_dsatur(Graph);
	end = clock();
	print_fullstats(Colors,start,end,"Hybrid DSATUR #2");
	cout << endl;

	start = clock();
	Colors = hybrid_dsatur(Graph);
	end = clock();
	print_fullstats(Colors,start,end,"Hybrid DSATUR #3");
	cout << endl;

	return 0;
}
