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
           map<string,vector<string> > graph;
           map<string,int> coloring;
           bool colored;

           /* Helper Functions */
           /* Writing helper function */
           string get_color_string(int color,int max_color);
           int find_max_color();
        public:

            GraphColor(map<string, vector<string> > input_graph):colored(false){ 
              graph = input_graph;
            }

            /* Mutators */
            virtual void set_condition(int con) {}

            /* Coloring functions */
            virtual map<string,int> color() = 0;
            bool verify();

            /* Accessors */
            unsigned size() { return graph.size(); }
            map<string,int> get_coloring() { return coloring; }
            virtual string get_algorithm_string() = 0;

            /* Mutators */
            void set_graph(map<string,vector<string> > new_graph) { graph = new_graph; }
            void set_coloring(map<string,int> new_coloring) { coloring = new_coloring; }

            /* Print functions */
            virtual void print_coloring();
            void print_chromatic();
            void write_graph(string graph_name = "");
    };
}

#endif // _GRAPH_COLOR_H_