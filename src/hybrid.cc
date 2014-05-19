#include "graph.h"

void GraphColoring::Graph::hybrid(int CARR) {
	lmxrlf_base(CARR);
	//coloring = lmxrlf_base(Graph,CARR);
	
	//*********************************
	//***** Find the Sub Coloring *****
	//*********************************
	int Color_temp = 0;
	for(map< string,int >::iterator i = coloring.begin(); i != coloring.end(); i++) {
		if((*i).second > Color_temp) {
			Color_temp = (*i).second;
		}
	}
	Color_temp += 1;
	
	map< string,int > Colors_temp = coloring;
	
	//coloring = lmxrlf(graph.size());
	lmxrlf(graph.size());
	int Color = 0;
	for(map< string,int >::iterator i = coloring.begin(); i != coloring.end(); i++) {
		if((*i).second > Color) {
			Color = (*i).second;
		}
	}
	
	//******************************************************
	//***** Run Remainder through Tabucol and Recolor *****
	//******************************************************
	int subset_color = Color;
	
	Graph subset("tabucol");
	subset.set_graph(get_subgraph(Colors_temp));
	subset.set_coloring(Colors_temp);
	subset.color(subset_color);
	map<string,int> tabu_color = subset.get_coloring();
	//map< string,vector<string> > Graph_subset = get_subgraph(Colors_temp);
	//map< string,int > tabu_color = tabucol(Graph_subset,subset_color); 
	map< string,int > best;
	while(tabu_color.size() > 0) {
		best = tabu_color;
		subset_color -= 1;
		//tabu_color = tabucol(Graph_subset,subset_color);
		subset.color(subset_color);
		tabu_color = subset.get_coloring();
	}
	if(best.size() > 0) {
		for(map< string,int >::iterator i = best.begin(); i != best.end(); i++) {
			coloring[(*i).first] = Color_temp + (*i).second;
		}
	}
}

map< string,vector<string> > GraphColoring::Graph::get_subgraph(map< string,int > coloring) {
	map< string,vector<string> > subgraph;
	for(map< string,vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		if(coloring[(*i).first] == -1) {
			vector<string> neighbors;
			for(unsigned j=0; j<(*i).second.size(); j++) {
				if(coloring[(*i).second[j]] == -1)
					neighbors.push_back((*i).second[j]);
			}
			subgraph[(*i).first] = neighbors;
		}
	}
	return subgraph;
}


//Starts by using DSATUR to get an approximate coloring and then uses decrementing
//tabucol runs to try and reduce the chromatic number
void GraphColoring::Graph::hybrid_dsatur() {
	dsatur();

	int largest = 0;
	for(map< string, int >::iterator i = coloring.begin(); i != coloring.end(); i++)
	{	
		if((*i).second > largest) { largest = (*i).second; }
	}
	largest += 1;

	map< string,int > best = coloring;
	tabucol(largest);
	map< string,int > tabu_color = coloring;
	while(tabu_color.size() > 0)
	{
		best = tabu_color;
		largest -= 1;
		tabucol(largest);
		tabu_color = coloring;
	}
	coloring = best;
}
