#ifndef _MY_HYBRID_H_
#define _MY_HYBRID_H_

#include "graph_color.h"
#include "my_lmxrlf.h"
#include "my_tabucol.h"

using GraphColoring::Algorithm;
using GraphColoring::GraphColor;
using GraphColoring::lmxrlf;
using GraphColoring::tabucol;

namespace GraphColoring{
	class hybrid : public GraphColor {
		private: 
			map< string,vector<string> > get_subgraph(map< string,int > coloring);
		public: 
			hybrid() :GraphColor() { algorithm = kHybrid; } 
			map<string,int> color(int condition = 0);
	};
}

#endif