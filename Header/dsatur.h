#ifndef _DSATUR_H_
#define _DSATUR_H_

#include "graph_color.h"

using GraphColoring::GraphColor;

namespace GraphColoring{
	class Dsatur : public GraphColor {
		public: 
			/* Constructors */
			Dsatur(map<string,vector<string> > input_graph);

			/* Mutators */
			void set_condition(int con);
			map<string,int> color();

			/* Accessors */
			string get_algorithm() { return "DSATUR"; }
	};
}

#endif //_DSATUR_H_
