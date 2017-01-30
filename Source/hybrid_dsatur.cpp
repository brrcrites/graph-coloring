#include "../Header/hybrid_dsatur.h"

map<string,int> GraphColoring::hybrid_dsatur::color(int condition) {
	GraphColor *temp_graph = new dsatur();
	temp_graph->set_graph(this->graph);
	coloring = temp_graph->color();
	delete temp_graph;

	int largest = 0;
	for(map< string, int >::iterator i = coloring.begin(); i != coloring.end(); i++)
	{	
		if((*i).second > largest) { largest = (*i).second; }
	}
	largest += 1;

	temp_graph = new tabucol(this->graph);

	map< string,int > best = coloring;
	map< string,int > tabu_color = temp_graph->color(largest);
	while(tabu_color.size() > 0)
	{
		best = tabu_color;
		largest -= 1;
		tabu_color = temp_graph->color(largest);
	}
	coloring = best;
	delete temp_graph;
	return coloring;
}
