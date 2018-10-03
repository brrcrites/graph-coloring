#ifndef _MCS_HPP_
#define _MCS_HPP_

#include "coloring_algorithm.hpp"

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

#endif //_MCS_HPP_
