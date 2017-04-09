
#include "../Header/graph_color.h"
#include <fstream>
#include <iostream>
#include <sstream>

using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostringstream;

// Checks that no two adjacent nodes have the same color
bool GraphColoring::GraphColor::verify() {
    for(map< string,vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
        for(unsigned j=0; j<(*i).second.size(); j++) {
            if(coloring[(*i).first] == coloring[(*i).second[j]]) {
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
	if(this->coloring.find(node) != this->coloring.end()) {
		return this->coloring.at(node);
	}
	return -1;
}

// Used to print the Chromatic Color
void GraphColoring::GraphColor::print_chromatic() {
    int largest = -2;
    for(map< string, int >::iterator itr = this->coloring.begin(); itr != this->coloring.end(); itr++) {
        if(itr->second > largest) { 
            largest = itr->second; 
        }
    }
    cout << this->get_algorithm() << " Chromatic Number: " << largest+1 << endl;
}

// Used to print the color of each node in the graph
void GraphColoring::GraphColor::print_coloring() {
    std::cout << "----------" << this->get_algorithm() << " Colorings----------" << endl;
    for(map< string,int >::iterator itr = coloring.begin(); itr != coloring.end(); itr++) {
        std::cout << itr->first << " " << itr->second << endl;
    }
}

int GraphColoring::GraphColor::find_max_color() {
    map<string,int>::iterator color_it = coloring.begin();
    int max_color = 0;
    for (/*color_it*/;color_it != coloring.end();color_it++) {
        if ((*color_it).second > max_color) {
            max_color = (*color_it).second;
        }
    }
    return max_color;
}

#include "../Header/graph_colors.h"

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
                << coloring.at((*graph_it).first) << "\"";
        if (colored) { 
            outfile << " style=filled fillcolor=\"";
            outfile << get_color_string(coloring.at((*graph_it).first),max_color);
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
