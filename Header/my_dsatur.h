#ifndef _MY_DSATUR_H_
#define _MY_DSATUR_H_

#include "graph_color.h"

using GraphColoring::GraphColor;
using GraphColoring::Algorithm;

namespace GraphColoring{
	class dsatur : public GraphColor {
		public: 
			dsatur() :GraphColor() { algorithm = kDSATUR; } 
			map<string,int> color(int condition = 0);
	};
}

#endif