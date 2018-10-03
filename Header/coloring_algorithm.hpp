#ifndef _GRAPH_COLOR_HPP_
#define _GRAPH_COLOR_HPP_

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
			map<string,vector<string>> graph;
			map<string,int> graph_colors;

			/* Writing helper function */
			string get_color_string(int color,int max_color); // TODO(brrcrites): remove w/ dotty removal
			int find_max_color();

		public:
			/* Constructors */
            GraphColor();
			GraphColor(map<string, vector<string>> graph);

			/* Mutators */
			virtual map<string,int> color() = 0;
			void set_graph(map<string,vector<string>> new_graph) { this->graph = new_graph; }
			void modify_graph(string node, vector<string> neighbors) { this->graph[node] = neighbors; }
			virtual bool verify();

			/* Accessors */
			virtual string get_algorithm() = 0;
			unsigned size() { return this->graph.size(); }
			bool is_colored();
			map<string,int> get_coloring() { return this->graph_colors; }
			int get_color(string node);

			/* Print functions */
			void print_coloring();
			void print_chromatic();
			void write_graph(string graph_name = ""); // TODO(brrcrites): remove w/ dotty removal
	};
}

#endif // _GRAPH_COLOR_HPP_
