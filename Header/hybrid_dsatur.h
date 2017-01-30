#ifndef _HYBRID_DSATUR_H_
#define _HYBRID_DSATUR_H_

#include "graph_color.h"
#include "dsatur.h"
#include "tabucol.h"

using GraphColoring::Algorithm;
using GraphColoring::GraphColor;
using GraphColoring::dsatur;
using GraphColoring::tabucol;

namespace GraphColoring{
	class hybrid_dsatur : public GraphColor {
		public: 
			hybrid_dsatur(map<string, vector<string> > input_graph) :GraphColor(input_graph) { 
				algorithm = kHybridDSATUR; 
			} 
			map<string,int> color(int condition = 0);
	};
}

#endif