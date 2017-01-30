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
    enum Algorithm {kNone,kDSATUR,kMCS,kTABUCOL,kHybrid,kLMXRLF,kHybridDSATUR};
    class GraphColor {
        protected:
           Algorithm algorithm;
           map<string,vector<string> > graph;
           map<string,int> coloring;
           bool colored;

           /* Helper Functions */
           /* Writing helper function */
           string get_color_string(int color,int max_color);
           int find_max_color();
        public:
            //Default coloring algorithm is DSATUR
            GraphColor(map<string, vector<string> > input_graph):colored(false){ 
              graph = input_graph;
              algorithm = kNone; 
            }

            /* Mutators */
            void add_edge(string source,string sink);
            void add_node(string new_node) { graph.insert(pair<string,vector<string> >(new_node,vector<string>())); }
            void set_algorithm(Algorithm new_algorithm) { algorithm = new_algorithm; }

            /* Coloring functions */
            virtual map<string,int> color(int condition = 0) = 0;
            bool verify();

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

#endif // _GRAPH_COLOR_H_
