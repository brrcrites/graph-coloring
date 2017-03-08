#ifndef _HYBRID_DSATUR_H_
#define _HYBRID_DSATUR_H_

#include "graph_color.h"
#include "dsatur.h"
#include "tabucol.h"

using GraphColoring::GraphColor;
using GraphColoring::Dsatur;
using GraphColoring::Tabucol;

namespace GraphColoring{
	class HybridDsatur : public GraphColor {
		public: 
			HybridDsatur(map<string, vector<string> > input_graph) :GraphColor(input_graph) { }
			map<string,int> color();
			string get_algorithm_string() { return "HYBRIDDSATUR"; }
	};
}

#endif