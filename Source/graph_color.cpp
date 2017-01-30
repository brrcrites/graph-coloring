
#include "../Header/graph_color.h"
#include <fstream>
#include <iostream>
#include <sstream>
//TODO: Change atoi, remove this header
#include <cstdlib>

using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostringstream;

string GraphColoring::GraphColor::get_algorithm_string() { 
    switch (algorithm) {
        case kDSATUR:
            return "DSATUR";
            break;
        case kMCS:
            return "MCS";
            break;
        case kLMXRLF:
            return "LMXRLF";
            break;
        case kHybrid:
            return "Hybrid";
            break;
        case kHybridDSATUR:
            return "HybridDSATUR";
            break;
        case kNone:
            break;
        default:
            break;
    }
    return "None";
}

//TODO: What conditions are needed for each algorithm?
map<string,int> GraphColoring::GraphColor::color(int condition) {
    
    return coloring;
} 


bool GraphColoring::GraphColor::verify() {
    for(map< string,vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) 
    {
        for(unsigned j=0; j<(*i).second.size(); j++) 
        {
            if(coloring[(*i).first] == coloring[(*i).second[j]]) 
            {
                cerr << "Graph is not colored correctly" << endl;
                return false;
            }
        }
    }
    cerr << "Graph is colored correctly" << endl;
    return true;
}

//Used to print the Chromatic Color
void GraphColoring::GraphColor::print_chromatic() {
    int largest = 0;
    for(map< string, int >::iterator i = coloring.begin(); i != coloring.end(); i++) 
    {  
        if((*i).second > largest) 
        { 
            largest = (*i).second; 
        }
    }

    std::cout << get_algorithm_string() << " Chromatic Number: " << largest+1 << endl;
}

//Used to print the color of each node in the graph
void GraphColoring::GraphColor::print_coloring() {
    std::cout << "----------" << algorithm << " Colorings----------" << endl;
    for(map< string,int >::iterator i = coloring.begin(); i != coloring.end(); i++) {
        std::cout << (*i).first << " " << (*i).second << endl;
    }
}

void GraphColoring::GraphColor::add_edge(string source,string sink) {
    map<string,vector<string> >::iterator source_node;
    map<string,vector<string> >::iterator sink_node;
    // Find each node. find will insert the node if it does not exist in the
    // graph
    source_node = graph.insert(pair<string,vector<string> >(source,vector<string>())).first;
    sink_node = graph.insert(pair<string,vector<string> >(sink,vector<string>())).first;
    // Add the opposite node to the edge list for each node
    (*source_node).second.push_back(sink);
    (*sink_node).second.push_back(source);
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
