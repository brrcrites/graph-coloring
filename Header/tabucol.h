#ifndef _TABUCOL_H_
#define _TABUCOL_H_

#include "graph_color.h"

using GraphColoring::GraphColor;

namespace GraphColoring{
	class Tabucol : public GraphColor {
		private:
			int f(map<string,int> coloring);
			int condition;
		public: 
			Tabucol(map<string, vector<string> > input_graph) :GraphColor(input_graph) { } 
			Tabucol(map<string, vector<string> > input_graph, int con) :GraphColor(input_graph){ 
				condition = con;
			} 
			map<string,int> color();
			string get_algorithm_string() { return "TABUCOL"; }
			void set_condition(int con) { condition = con; }
	};
}

#endif