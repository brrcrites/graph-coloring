#ifndef _MY_LMXRLF_H_
#define _MY_LMXRLF_H_

#include "graph_color.h"

using GraphColoring::GraphColor;
using GraphColoring::Algorithm;

namespace GraphColoring{
	class lmxrlf : public GraphColor {
		private:
		    //helper functions
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
			lmxrlf() :GraphColor() { algorithm = kLMXRLF; } 
			map<string,int> color(int condition = 0);
	};
}

#endif