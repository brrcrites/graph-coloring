#ifndef _HYBRID_H_
#define _HYBRID_H_

#include "graph_color.h"
#include "lmxrlf.h"
#include "tabucol.h"

using GraphColoring::Algorithm;
using GraphColoring::GraphColor;
using GraphColoring::lmxrlf;
using GraphColoring::tabucol;

namespace GraphColoring{
	class hybrid : public GraphColor {
		private: 
			map< string,vector<string> > get_subgraph(map< string,int > coloring);
		public: 
			hybrid(map<string,vector<string> > input_graph) :GraphColor(input_graph) {
				algorithm = kHybrid; 
			} 
			map<string,int> color(int condition = 0);
	};
}

#endif