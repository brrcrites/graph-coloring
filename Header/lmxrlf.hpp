#ifndef _LMXRLF_HPP_
#define _LMXRLF_HPP_

#include "coloring_algorithm.hpp"

using GraphColoring::GraphColor;

namespace GraphColoring{
	class Lmxrlf : public GraphColor {
		private:
		    //helper functions
		    int condition;
		    vector<string> get_independent(vector<string> set);
            vector<string> make_independent_set();
            int objf(vector<string> set);
            int min_objf(vector< vector<string> > list_of_best);
            int max_objf(vector< vector<string> > list_of_best);
            int min_pos_objf(vector< vector<string> > list_of_best);
            int max_pos_objf(vector< vector<string> > list_of_best);
            vector<string> uncolored_neighbor(vector<string> new_set);
            map<string,int> lmxrlf_alg(int endcond);
		public: 
			Lmxrlf(map<string, vector<string> > input_graph) :GraphColor(input_graph) { 
				condition = 0;
			} 
			Lmxrlf(map<string, vector<string> > input_graph, int con) :GraphColor(input_graph){ 
				condition = con;
			}
			map<string,int> color();
			string get_algorithm() { return "LMXRLF"; }
			void set_condition(int con) { condition = con; }
	};
}

#endif //_LMXRLF_HPP_
