#ifndef _MCS_H_
#define _MCS_H_

#include "graph_color.h"

using GraphColoring::GraphColor;

namespace GraphColoring{
	class Mcs : public GraphColor {
		public: 
			/* Constructors */
			Mcs(map<string, vector<string> > input_graph) :GraphColor(input_graph) {} 

			/* Mutators */
			void set_condition(int con);
			map<string,int> color();

			/* Accessors */
			string get_algorithm() { return "MCS"; }
	};
}

#endif