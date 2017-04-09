#ifndef _GRAPH_COLOR_H_
#define _GRAPH_COLOR_H_

#include <map>
#include <stack>
#include <locale>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <queue>

using std::queue;
using std::map;
using std::pair;
using std::stack;
using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

namespace GraphColoring {
	class GraphColor {
		protected:
			/* Internal Members */
			map<string,vector<string> > graph;
			map<string,int> coloring;
			bool colored;

			/* Writing helper function */
			string get_color_string(int color,int max_color); // TODO(brrcrites): remove w/ dotty removal
			int find_max_color();

		public:
			/* Constructors */
			GraphColor(map<string, vector<string> > input_graph): graph(input_graph), colored(false) {}

			/* Mutators */
			virtual void set_condition(int con) = 0;
			virtual map<string,int> color() = 0;
			void set_graph(map<string,vector<string> > new_graph) { this->graph = new_graph; this->colored = false; }
			void modify_graph(string node, vector<string> neighbors) { this->graph[node] = neighbors; this->colored = false; }
			virtual bool verify();

			/* Accessors */
			virtual string get_algorithm() = 0;
			unsigned size() { return this->graph.size(); }
			bool is_colored() { return this->colored; }
			map<string,int> get_coloring() { return this->coloring; }
			int get_color(string node);

			/* Print functions */
			void print_coloring();
			void print_chromatic();
			void write_graph(string graph_name = ""); // TODO(brrcrites): remove w/ dotty removal
	};
}

#endif // _GRAPH_COLOR_H_
