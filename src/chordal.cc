
#include "graph.h"

stack<string> GraphColoring::Graph::mcs() {
	map< string, int > weight;
	stack<string> ordering;
	int size = 0;
	for(map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		size += 1;
		weight[(*i).first] = 0;
	}
	for(int i = 0; i < size; i++) {
		int max_weight = -1;
		string max_vertex = "error";
		for(map< string, vector<string> >:: iterator j = graph.begin(); j != graph.end(); j++) {
			if(weight[(*j).first] > max_weight)
				max_vertex = (*j).first;
		}
		ordering.push(max_vertex);
		for(unsigned j = 0; j<graph[max_vertex].size(); j++) {
			weight[graph[max_vertex][j]] += 1;
		}
		graph.erase(max_vertex);
	}
	return ordering;
}

void GraphColoring::Graph::chordal() {
	stack<string> todo = mcs();
	
	while(!todo.empty()) {
		string min = todo.top();
	
		//find the minimum coloring number from the neighbors
		int color = 0;
		int done = 0;
		while(!done) {
			done = 1;
			for(unsigned i=0; i<graph[min].size(); i++) {
				if(coloring[graph[min][i]] == color) {
					color += 1;
					done = 0;
				}
			}
		}
		//color with lowest color and remove the minimum from the todo list
		coloring[min] = color;
		todo.pop();
	}	
}
