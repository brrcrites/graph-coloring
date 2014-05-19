
#ifndef _DSATUR_H_
#define _DSATUR_H_

#include "graph.h"

void GraphColoring::Graph::dsatur() {	
	vector<string> todo;
	string max_degree = "error";
	int degree = -1;
	//find maximal degree vertex to color first and color with 0
	for(map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		if(degree < (int)(*i).second.size()) {
			degree = (*i).second.size();
			max_degree = (*i).first;
		}
	}
	coloring[max_degree] = 0;

	//populate the todo list with the remaining vertices
	for(map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		if((*i).first != max_degree) {
			coloring[(*i).first] = -1;
			todo.push_back((*i).first);
		}
	}

	while(!todo.empty()) {
		int pos = -1;
		int saturation = -1;
		string saturation_name = "error";
		vector<int> saturation_colors;
		//find the vertex with the highest saturation level
		for(unsigned i=0; i<todo.size(); i++) {
			int internal = 0;
			vector<int> internal_colors;
			//iterate over todo vertices neighbors and count how many are colroed
			for(unsigned j=0; j<graph[todo[i]].size(); j++) {
				//a lack of color is denoted with -1, so check it has an actual color
				if(coloring[graph[todo[i]][j]] != -1) {
					internal += 1;
					internal_colors.push_back(coloring[graph[todo[i]][j]]);
				}
			}
			if(saturation < internal) {
				saturation = internal;
				saturation_name = todo[i];
				saturation_colors = internal_colors;
				pos = i;
			}
		}
		//we now know the highest saturated vertex, so remove it from the todo list
		todo.erase(todo.begin()+pos);
		int max_color = 0;
		int done = 0;
		//find the lowest possible value color that isn't used in a neighbor
		//TODO (Brian): might be a place that can be easily optimized, this is kinda ugly
		while(!done) {
			done = 1;
			for(unsigned i=0; i<saturation_colors.size(); i++) {
				if(saturation_colors[i] == max_color) {
					max_color += 1;
					done = 0;
				}
			}
		}
		coloring[saturation_name] = max_color;
	}	
}

#endif // _DSATUR_H_
