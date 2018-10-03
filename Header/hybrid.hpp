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
			map< string,vector<string> > get_subgraph(map< string,int > coloring);
		public: 
			Hybrid(map<string,vector<string> > input_graph) :GraphColor(input_graph) { 
				condition = 0;
			} 
			Hybrid(map<string,vector<string> > input_graph, int con) :GraphColor(input_graph) { 
				condition = con;
			} 
			map<string,int> color();
			void set_condition(int con) { condition = con; }
			string get_algorithm() { return "HYBRID"; }
	};
}

#endif //_HYBRID_HPP_
