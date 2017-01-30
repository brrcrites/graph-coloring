#ifndef _DSATUR_H_
#define _DSATUR_H_

#include "graph_color.h"

using GraphColoring::GraphColor;
using GraphColoring::Algorithm;

namespace GraphColoring{
	class dsatur : public GraphColor {
		public: 
			dsatur(map<string,vector<string> > input_graph) :GraphColor(input_graph) { 
				algorithm = kDSATUR; 
			} 
			map<string,int> color(int condition = 0);
	};
}

#endif