
#include "graph.h"
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

ifstream& Getline(ifstream& ifs,string& line) {
    getline(ifs,line);
    if (!line.empty()) {
        while (isspace(line.at(line.size()-1))) {
            line = line.substr(0,line.size()-1);
        }
    }
    return ifs;
}

//TODO: What conditions are needed for each algorithm?
map<string,int> GraphColoring::Graph::color(int condition) {
    switch(algorithm) {
        case kDSATUR:
            dsatur();
            break;
        case kMCS:
            mcs();
            break;
        case kLMXRLF:
            if (condition == 0) {
                condition = graph.size();
            }
            lmxrlf_base(condition);
            break;
        case kHybrid:
            if (condition == 0) {
                condition = graph.size() / 2;
            }
            hybrid(condition);
            break;
        case kHybridDSATUR:
            hybrid_dsatur();
            break;
        default:
            cerr << "Warning: No algorithm selected. Continuing with DSATUR." << endl;
            dsatur();
            break;
    }
    colored = true;
    return coloring;
} 

string GraphColoring::Graph::get_algorithm_string() { 
    switch (algorithm) {
        case kDSATUR:
            return "DSATUR";
        case kMCS:
            return "MCS";
        case kLMXRLF:
            return "LMXRLF";
        case kHybrid:
            return "Hybrid";
        case kHybridDSATUR:
            return "HybridDSATUR";
        case kNone:
        default:
            return "None";
    }
}

GraphColoring::Graph::Graph(string new_algorithm) {
    if (new_algorithm.compare("DSATUR")) {
        algorithm = kDSATUR;
    } else {
        algorithm = kDSATUR;
    }
}

vector<string> GraphColoring::Graph::split(string to_split) {
    vector<string> split_string;
    unsigned index_start;
    for (unsigned i = 0;i < to_split.length();i++) {
        index_start = i;
        while(i < to_split.length() && !isspace(to_split.at(i))) { i++; }
        split_string.push_back(to_split.substr(index_start,i - index_start));
    }
    return split_string;
}

void GraphColoring::Graph::parse_edge_list(char* input_file) {
    ifstream file(input_file);
    if(file.is_open()) {
        string line;
        int vertices = -1;
        int flag = 0;
        while(!flag && Getline(file,line)) {
            while(line.size() == 0) {
                Getline(file,line);
            }
            vector<string> words = GraphColoring::Graph::split(line);
            if(words.size() != 0) {
                if(words[0] == "p") {
                    vertices = atoi(words[2].c_str());
                    flag = 1;
                }
            }
        }
        if(!flag || vertices == -3) {
            cerr << "File is missing parameter line before edge list" << endl;
            cerr << "Should be: \"p edge <number of vertices> <number of edges>\"" << endl;
            return;
        }
        for(int i=0; i<vertices; i++) {
            string pre = "v";
            string temp;
            std::ostringstream convert;
            convert << (i+1);
            temp = convert.str();
            pre.append(temp);
            vector<string> base;
            graph[pre] = base;
        }
        while(Getline(file,line))
        {
            vector<string> words = GraphColoring::Graph::split(line);
            if(words[0] == "e")
            {
                string arg1 = "v";
                arg1.append(words[1]);
                string arg2 = "v";
                arg2.append(words[2]);
                vector<string> base;
                vector<string> base2;
		graph[arg1].push_back(arg2);
		graph[arg2].push_back(arg1);
            }
        }
    } else {
        cerr << "Input File Not Found" << endl;
        return;
    }
}

//Used to parse test inputs where the first line is the number of
//vertices, and the next lines are the edge matrix
void GraphColoring::Graph::parse_edge_matrix(char* input_file) {
    string pre = "v";

    ifstream file(input_file);
    if(file.is_open()) {
        string line;
        Getline(file,line);
        int n = atoi(line.c_str());
        int i = 0;
        while(Getline(file,line)) {
            i += 1;
            vector<string> words = GraphColoring::Graph::split(line);
            if((int)words.size() != n) {
                cerr << "Invalid Input, line " << i << " is not the correct length (" 
                     << words.size() << "," << n << "): " << line << endl;
                for (unsigned i = 0;i < words.size();i++) { cerr << "\t" << words.at(i) << endl; }
                graph.clear();
                return;
            }
            vector<string> edges;
            for(int j = 0; j < n; j++) {
                if(words[j] == "1") {
                    pre = "v";
                    string temp;
                    ostringstream convert;
                    convert << (j+1);
                    temp = convert.str();
                    edges.push_back(pre.append(temp));
                }
            }
            pre = "v";
            string temp;
            ostringstream convert;
            convert << i;
            temp = convert.str();
            graph[pre.append(temp)] = edges;
        }
        if(i != n) {
            cerr << "Input is not the right length" << endl;
            graph.clear();
            return;
        }
        file.close();
    } else {
        cerr << "Input File Not Found" << endl;
        return;
    }
    return;
}

vector< vector<string> > GraphColoring::Graph::get_input(char* input_file) {
    vector< vector<string> > Input;

    ifstream file(input_file);
    if(file.is_open()) {
        string line;
        while(Getline(file,line)) {
            vector<string> words = GraphColoring::Graph::split(line);
            if(words.size() > 1) {
                for(unsigned i=1; i<words.size(); i++) {
                    if(words[i] != "0" && words[i] != "1" && words[i] != "x" && words[i] != "X") {
                        cerr << "Problem with this Input Line: " << line << endl;
                        cerr << "Problem is with word: \"" << words[i] << "\" at position " << i << endl;
                        Input.clear();
                        return Input;
                    }
                }
            } else {
                cerr << "No Actuation Data Found, Please Check Input File" << endl;
                Input.clear();
                return Input;
            }
            Input.push_back(words);
        }
        file.close();
    } else {
        cerr << "Input File Not Found" << endl;
    }
    return Input;
}

bool GraphColoring::Graph::verify() {
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
void GraphColoring::Graph::print_chromatic() {
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
void GraphColoring::Graph::print_coloring() {
    std::cout << "----------" << algorithm << " Colorings----------" << endl;
    for(map< string,int >::iterator i = coloring.begin(); i != coloring.end(); i++) {
        std::cout << (*i).first << " " << (*i).second << endl;
    }
}

void GraphColoring::Graph::add_edge(string source,string sink) {
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

int GraphColoring::Graph::find_max_color() {
    map<string,int>::iterator color_it = coloring.begin();
    int max_color = 0;
    for (/*color_it*/;color_it != coloring.end();color_it++) {
        if ((*color_it).second > max_color) {
            max_color = (*color_it).second;
        }
    }
    return max_color;
}

#include "graph_colors.h"

string GraphColoring::Graph::get_color_string(int color,int max_color) {
    return ColorArray[color];
    const int MaxColor = 1023;
    color = color * (MaxColor / max_color);
    std::stringstream color_changer;
    color_changer << "0x" << std::hex << color;
    return color_changer.str();
}

void GraphColoring::Graph::write_graph(string graph_name) {
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
