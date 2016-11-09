#ifndef _MY_MCS_H_
#define _MY_MCS_H_

#include "graph_color.h"

using GraphColoring::GraphColor;
using GraphColoring::Algorithm;

namespace GraphColoring{
	class mcs : public GraphColor {
		public: 
			mcs() :GraphColor() { algorithm = kMCS; } 
			map<string,int> color(int condition = 0);
	};
}

#endif