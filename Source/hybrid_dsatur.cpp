
#include "../Header/hybrid_dsatur.hpp"

map<string,int> GraphColoring::HybridDsatur::color() {
	GraphColor* temp_graph = new Dsatur(this->graph);
	graph_colors = temp_graph->color();

	int largest = 0;
	for(map<string,int>::iterator i = this->graph_colors.begin(); i != this->graph_colors.end(); i++) {	
		if(i->second > largest) { largest = i->second; }
	}
	largest += 1;

	Tabucol* tabu_graph = new Tabucol(this->graph, largest);

	map<string,int> best = this->graph_colors;
	map<string,int> tabu_color = tabu_graph->color();
	while(tabu_color.size() > 0) {
		best = tabu_color;
		largest -= 1;
		tabu_graph->set_condition(largest);
		tabu_color = tabu_graph->color();
	}
	this->graph_colors = best;
	return graph_colors;
}
