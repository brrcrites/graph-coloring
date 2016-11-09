#ifndef _MY_HYBRID_DSATUR_H_
#define _MY_HYBRID_DSATUR_H_

#include "graph_color.h"
#include "my_dsatur.h"
#include "my_tabucol.h"

using GraphColoring::Algorithm;
using GraphColoring::GraphColor;
using GraphColoring::dsatur;
using GraphColoring::tabucol;

namespace GraphColoring{
	class hybrid_dsatur : public GraphColor {
		public: 
			hybrid_dsatur() :GraphColor() { algorithm = kHybridDSATUR; } 
			map<string,int> color(int condition = 0);
	};
}

#endif