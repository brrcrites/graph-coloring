#ifndef _MCS_H_
#define _MCS_H_

#include "graph_color.h"

using GraphColoring::GraphColor;
using GraphColoring::Algorithm;

namespace GraphColoring{
	class mcs : public GraphColor {
		public: 
			mcs(map<string, vector<string> > input_graph) :GraphColor(input_graph) { 
				algorithm = kMCS; 
			} 
			map<string,int> color(int condition = 0);
	};
}

#endif