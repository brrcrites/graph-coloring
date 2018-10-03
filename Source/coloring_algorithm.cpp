
#include <fstream>
#include <iostream>
#include <sstream>

#include "../Header/coloring_algorithm.hpp"
#include "../Header/colors.hpp"

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

// TODO(brrcrites): remove the next two functions w/ dotty removal
string GraphColoring::GraphColor::get_color_string(int color,int max_color) {
    return ColorArray[color];
    const int MaxColor = 1023;
    color = color * (MaxColor / max_color);
    std::stringstream color_changer;
    color_changer << "0x" << std::hex << color;
    return color_changer.str();
}

void GraphColoring::GraphColor::write_graph(string graph_name) {
    int max_color = find_max_color();
    if(max_color > COLOR_ARRAY_SIZE)
    {
        cerr << "Error: Graph has too many colors to be written" << endl;
        return;
    }
    if (graph_name.empty()) {
        graph_name = "colored_graph";
    }
    string filename = graph_name+".dot";
    ofstream outfile(filename.c_str());
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open \"" << filename << "\"." << endl;
        return;
    }
    outfile << "graph " << graph_name << " {\n";
    map <string,vector<string> >::iterator graph_it;
    graph_it = graph.begin();
    for (/*graph_it*/;graph_it != graph.end();graph_it++) {
        outfile << (*graph_it).first << "[label=\"" << (*graph_it).first << "\\n"
                << graph_colors.at((*graph_it).first) << "\"";
        if (this->is_colored()) { 
            outfile << " style=filled fillcolor=\"";
            outfile << get_color_string(graph_colors.at((*graph_it).first),max_color);
            outfile << "\"";
        }   
        outfile << "];\n";
    }
    graph_it = graph.begin();
    for (/*graph_it*/;graph_it != graph.end();graph_it++) {
        string start_node = (*graph_it).first;
        vector<string> connections = (*graph_it).second;
        for (unsigned i = 0;i < connections.size();i++) {
            if (connections.at(i) < start_node) {
                outfile << start_node << " -- " << connections.at(i) << endl;
            }
        }
    }
    outfile << "}" << endl;
    outfile.close();
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
