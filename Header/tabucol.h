#ifndef _TABUCOL_H_
#define _TABUCOL_H_

#include "graph_color.h"

using GraphColoring::GraphColor;

namespace GraphColoring{
	class Tabucol : public GraphColor {
		private:
			int condition; 
			int f(map<string,int> coloring);
		public: 
			Tabucol(map<string, vector<string> > input_graph) :GraphColor(input_graph) { 
				condition = 0;
			} 
			Tabucol(map<string, vector<string> > input_graph, int con) :GraphColor(input_graph) { 
				condition = con;
			} 
			map<string,int> color();
			void set_condition(int con) { condition = con; }
			string get_algorithm() { return "TABUCOL"; }
			bool verify();
	};
}

#endif