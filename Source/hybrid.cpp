#include "../Header/hybrid.h"

map<string,int> GraphColoring::Hybrid::color() {
	if (this->condition == 0) {
        this->condition = graph.size() / 2;
    }

	GraphColor *alg_graph = new Lmxrlf(this->graph, this->condition);
	coloring = alg_graph->color();
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
	alg_graph->set_condition(graph.size());
	coloring = alg_graph->color();
	int Color = 0;
	for(map< string,int >::iterator i = coloring.begin(); i != coloring.end(); i++) {
		if((*i).second > Color) {
			Color = (*i).second;
		}
	}
	delete alg_graph;
	
	//******************************************************
	//***** Run Remainder through Tabucol and Recolor *****
	//******************************************************
	int subset_color = Color;
	
	alg_graph = new Tabucol(get_subgraph(Colors_temp));
	alg_graph->set_coloring(Colors_temp);
	alg_graph->set_condition(subset_color);
	alg_graph->color();
	map<string,int> tabu_color = alg_graph->get_coloring();
	
	//map< string,vector<string> > Graph_subset = get_subgraph(Colors_temp);
	//map< string,int > tabu_color = tabucol(Graph_subset,subset_color); 
	map< string,int > best;
	while(tabu_color.size() > 0) {
		best = tabu_color;
		subset_color -= 1;
		alg_graph->set_condition(subset_color);
		//tabu_color = tabucol(Graph_subset,subset_color);
		alg_graph->set_coloring(alg_graph->color());
		tabu_color = alg_graph->get_coloring();
	}
	if(best.size() > 0) {
		for(map< string,int >::iterator i = best.begin(); i != best.end(); i++) {
			coloring[(*i).first] = Color_temp + (*i).second;
		}
	}
	return coloring;
}


map< string,vector<string> > GraphColoring::Hybrid::get_subgraph(map< string,int > coloring) {
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
