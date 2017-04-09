#ifndef _DSATUR_H_
#define _DSATUR_H_

#include "graph_color.h"

using GraphColoring::GraphColor;

namespace GraphColoring{
	class Dsatur : public GraphColor {
		public: 
			Dsatur(map<string,vector<string> > input_graph) :GraphColor(input_graph) { } 
			map<string,int> color();
			string get_algorithm() { return "DSATUR"; }
	};
}

#endif