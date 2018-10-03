
#include <fstream>
#include <iostream>
#include <sstream>

#include "../Header/coloring_algorithm.hpp"
#include "../Header/colors.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostringstream;

GraphColoring::GraphColor::GraphColor() {
    this->graph = map<string,vector<string>>();
    this->graph_colors = map<string,int>();
}

GraphColoring::GraphColor::GraphColor(map<string,vector<string>> graph) {
    this->graph = graph;
    for(map<string,vector<string>>::iterator itr = graph.begin(); itr != graph.end(); itr++) {
        this->graph_colors[itr->first] = -1;
    }
}

// Checks that no two adjacent nodes have the same color
bool GraphColoring::GraphColor::verify() {
    for(map< string,vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
        for(unsigned j=0; j<(*i).second.size(); j++) {
            if(graph_colors[(*i).first] == graph_colors[(*i).second[j]]) {
                cerr << "Graph is not colored correctly" << endl;
                return false;
            }
        }
    }
    cout << "Graph is colored correctly" << endl;
    return true;
}

// Returns the color of an individual node, if that node isn't colored it returns -1
int GraphColoring::GraphColor::get_color(string node) {
	if(this->graph_colors.find(node) != this->graph_colors.end()) {
		return this->graph_colors.at(node);
	}
	return -1;
}

// Used to print the Chromatic Color
void GraphColoring::GraphColor::print_chromatic() {
    int largest = -2;
    for(map< string, int >::iterator itr = this->graph_colors.begin(); itr != this->graph_colors.end(); itr++) {
        if(itr->second > largest) { 
            largest = itr->second; 
        }
    }
    cout << this->get_algorithm() << " Chromatic Number: " << largest+1 << endl;
}

// Used to print the color of each node in the graph
void GraphColoring::GraphColor::print_coloring() {
    std::cout << "----------" << this->get_algorithm() << " Colorings----------" << endl;
    for(map< string,int >::iterator itr = graph_colors.begin(); itr != graph_colors.end(); itr++) {
        std::cout << itr->first << " " << itr->second << endl;
    }
}

int GraphColoring::GraphColor::find_max_color() {
    map<string,int>::iterator color_it = graph_colors.begin();
    int max_color = 0;
    for (/*color_it*/;color_it != graph_colors.end();color_it++) {
        if ((*color_it).second > max_color) {
            max_color = (*color_it).second;
        }
    }
    return max_color;
}

bool GraphColoring::GraphColor::is_colored() {
    if(this->graph_colors.size() < 1) {
        return false;
    } else {
        for(map<string,int>::iterator itr = this->graph_colors.begin(); itr != this->graph_colors.end(); itr++) {
            if(itr->second == -1) {
                return false;
            }
        }
        return true;
    }
}
