#ifndef _TABUCOL_HPP_
#define _TABUCOL_HPP_

#include "coloring_algorithm.hpp"

using GraphColoring::GraphColor;

namespace GraphColoring{
	class Tabucol : public GraphColor {
		private:
			int condition; 
			int f(map<string,int> coloring);

		public: 
            /* Constructors */
			Tabucol(map<string, vector<string> > input_graph) :GraphColor(input_graph) { this->condition = 0; } 
			Tabucol(map<string, vector<string> > input_graph, int con) :GraphColor(input_graph) { this->condition = con; } 

            /* Mutators */
			map<string,int> color();
			void set_condition(int con) { this->condition = con; }
            void set_coloring(map<string,int> coloring) { this->graph_colors = coloring; }

            /* Accessors */
			string get_algorithm() { return "TABUCOL"; }
			bool verify();
	};
}

#endif //_TABUCOL_HPP_
