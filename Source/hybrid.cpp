
#include "../Header/hybrid.hpp"

map<string,int> GraphColoring::Hybrid::color() {
	if (this->condition == 0) {
        this->condition = graph.size() / 2;
    }

	Lmxrlf* lmxrlf_graph = new Lmxrlf(this->graph, this->condition);
	this->graph_colors = lmxrlf_graph->color();

    // Find the Subcoloring
	int color_temp = 0;
	for(map<string,int>::iterator i = this->graph_colors.begin(); i != this->graph_colors.end(); i++) {
		if(i->second > color_temp) {
			color_temp = i->second;
		}
	}
	color_temp += 1;
	
	map<string,int> colors_temp = this->graph_colors;
	
	lmxrlf_graph->set_condition(graph.size());
	this->graph_colors = lmxrlf_graph->color();
	int color = 0;
	for(map<string,int>::iterator i = this->graph_colors.begin(); i != this->graph_colors.end(); i++) {
		if(i->second > color) {
			color = i->second;
		}
	}
	
    // Run Remained through Tabucol and Recolor
	int subset_color = color;
	
	Tabucol* tabu_graph = new Tabucol(get_subgraph(colors_temp));
	tabu_graph->set_coloring(colors_temp);
	tabu_graph->set_condition(subset_color);
	tabu_graph->color();
	map<string,int> tabu_color = tabu_graph->get_coloring();
	
	map< string,int > best;
	while(tabu_color.size() > 0) {
		best = tabu_color;
		subset_color -= 1;
		tabu_graph->set_condition(subset_color);
		tabu_graph->set_coloring(tabu_graph->color());
		tabu_color = tabu_graph->get_coloring();
	}
	if(best.size() > 0) {
		for(map< string,int >::iterator i = best.begin(); i != best.end(); i++) {
			this->graph_colors[i->first] = color_temp + i->second;
		}
	}
	return this->graph_colors;
}

map<string,vector<string>> GraphColoring::Hybrid::get_subgraph(map<string,int> coloring) {
	map<string,vector<string>> subgraph;
	for(map<string,vector<string>>::iterator i = this->graph.begin(); i != this->graph.end(); i++) {
		if(coloring[i->first] == -1) {
			vector<string> neighbors;
			for(unsigned j = 0; j < i->second.size(); j++) {
				if(coloring[i->second[j]] == -1)
					neighbors.push_back(i->second[j]);
			}
			subgraph[i->first] = neighbors;
		}
	}
	return subgraph;
}

