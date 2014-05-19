
#ifndef _GRAPH_H_
#define _GRAPH_H_

//#include "graph_coloring.h"

#include <map>
#include <stack>
#include <locale>
#include <vector>
#include <string>
#include <utility>

using std::map;
using std::pair;
using std::stack;
using std::string;
using std::vector;

namespace GraphColoring {
	enum Algorithm {kNone,kDSATUR,kChordal,kHybrid,kLMXRLF,kTabuCol};
	class Graph {
		private:
			Algorithm algorithm;
			map<string,vector<string> > graph;
			map<string,int> coloring;
			bool colored;

			/* Helper Functions */
			/* Parsing Helper Functions */
			vector< vector<string> > get_input(char* input_file);
			vector<string> split(string to_split);
			bool is_valid_input(char input);

			/* Coloring algorithms */
			void dsatur();
			void chordal();
			stack<string> mcs(); //Chordal Helper function
			void hybrid(int CARR);//TODO: Default?
			void hybrid_dsatur();
			void lmxrlf(int endcond);//TODO: Default?
			void lmxrlf_base(int endcond);//TODO: Default?
			void tabucol(int k); //TODO: Default?
			/* LMXRLF Helper functions */
			int objf(vector<string> set);
			vector<string> make_independent_set();
			vector<string> get_independent(vector<string> set); 
			int min_objf(vector< vector<string> > list_of_best);
			int max_objf(vector< vector<string> > list_of_best);
			int min_pos_objf(vector< vector<string> > list_of_best); 
			int max_pos_objf(vector< vector<string> > list_of_best); 
			vector<string> uncolored_neighbor(vector<string> new_set); 
			/* TabuCol helper functions */
			int f(map<string,int> coloring);
			/* Hybrid helper functions */
			map< string,vector<string> > get_subgraph(map< string,int > coloring);
			/* Writing helper function */
			string get_color_string(int color,int max_color);
			int find_max_color();
		public:
			//Default coloring algorithm is DSATUR
			Graph():colored(false){ algorithm = kDSATUR; }
			explicit Graph(Algorithm new_algorithm) { algorithm = new_algorithm; }
			explicit Graph(string new_algorithm);

			/* Mutators */
			void add_edge(string source,string sink);
			void add_node(string new_node) { graph.insert(pair<string,vector<string> >(new_node,vector<string>())); }
			void set_algorithm(Algorithm new_algorithm) { algorithm = new_algorithm; }

			/* Coloring functions */
			map<string,int> color(int condition = 0);
			bool verify();
			/* Parsing functions */
			void parse_edge_list(char* input_file);
			void parse_edge_matrix(char* input_file);

			/* Accessors */
			unsigned size() { return graph.size(); }
			Algorithm get_algorithm() { return algorithm; }
			map<string,int> get_coloring() { return coloring; }
			string get_algorithm_string();

			/* Mutators */
			void set_graph(map<string,vector<string> > new_graph) { graph = new_graph; }
			void set_coloring(map<string,int> new_coloring) { coloring = new_coloring; }

			/* Print functions */
			void print_coloring();
			void print_chromatic();
			void write_graph(string graph_name = "");
	};
}

#endif // _GRAPH_H_
