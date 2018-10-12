
#include "../Header/hybrid.hpp"

map<string,int> GraphColoring::Hybrid::color() {
	Lmxrlf* lmxrlf_graph = new Lmxrlf(this->graph, this->condition);
	this->graph_colors = lmxrlf_graph->color();
    int largest = this->get_num_colors();

	Tabucol* tabu_graph = new Tabucol(this->graph, largest);

	map<string,int> best = this->graph_colors;
    map<string,int> tabu_color = tabu_graph->color();
	while(tabu_graph->is_valid()) {
		best = tabu_color;
		largest -= 1;
		tabu_graph->set_condition(largest);
		tabu_color = tabu_graph->color();
	}
	this->graph_colors = best;
	return this->graph_colors;
}

map<string,vector<string>> GraphColoring::Hybrid::get_subgraph(map<string,int> coloring) {
	map<string,vector<string>> subgraph;
	for(map<string,vector<string>>::iterator adj_tuple = this->graph.begin(); adj_tuple != this->graph.end(); adj_tuple++) {
		if(coloring[adj_tuple->first] == -1) {
			vector<string> neighbors;
            for(vector<string>::iterator neighbor = adj_tuple->second.begin(); neighbor != adj_tuple->second.end(); neighbor++) {
				if(coloring[(*neighbor)] == -1)
					neighbors.push_back((*neighbor));
			}
			subgraph[adj_tuple->first] = neighbors;
		}
	}
	return subgraph;
}

