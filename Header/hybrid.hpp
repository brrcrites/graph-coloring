#ifndef _HYBRID_HPP_
#define _HYBRID_HPP_

#include "coloring_algorithm.hpp"
#include "lmxrlf.hpp"
#include "tabucol.hpp"

using GraphColoring::GraphColor;
using GraphColoring::Lmxrlf;
using GraphColoring::Tabucol;

namespace GraphColoring{
	class Hybrid : public GraphColor {
		private: 
			int condition;
			map<string,vector<string>> get_subgraph(map<string,int> coloring);

		public: 
            /* Constructors */
			Hybrid(map<string,vector<string> > graph) : GraphColor(graph) { this->condition = 0; } 
			Hybrid(map<string,vector<string> > graph, int condition) : GraphColor(graph) { this->condition = condition; } 

            /* Mutators */
			void set_condition(int condition) { this->condition = condition; }
			map<string,int> color();

            /* Accessors */
			string get_algorithm() { return "HYBRID"; }
	};
}

#endif //_HYBRID_HPP_
