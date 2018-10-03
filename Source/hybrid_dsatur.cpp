
#include "../Header/hybrid_dsatur.hpp"

void GraphColoring::HybridDsatur::set_condition(int con) {
	/* Do Nothing */
	cout << "Hybrid DSATUR has no condition to set" << endl;
}

map<string,int> GraphColoring::HybridDsatur::color() {
	GraphColor* temp_graph = new Dsatur(this->graph);
	coloring = temp_graph->color();

	int largest = 0;
	for(map< string, int >::iterator i = coloring.begin(); i != coloring.end(); i++) {	
		if((*i).second > largest) { largest = (*i).second; }
	}
	largest += 1;

	temp_graph = new Tabucol(this->graph, largest);

	map< string,int > best = coloring;
	map< string,int > tabu_color = temp_graph->color();
	while(tabu_color.size() > 0) {
		best = tabu_color;
		largest -= 1;
		temp_graph->set_condition(largest);
		tabu_color = temp_graph->color();
	}
	coloring = best;
	return coloring;
}
