
#include "graph.h"

// TODO: The following optimization can be made via a note in the paper
// The procedure MCS can be implemented to run in O(|V | + |E|) time. To 
// see that, notice that the first loop executes |V | iterations. In the 
// second loop, for each vertex of G, all its neighbors are visited. After 
// a vertex is evaluated, it is removed from the remaining graph. Therefore, 
// the weight λ is increased exactly |E| times. By keeping vertices in an 
// array of buckets indexed by λ, the vertex of highest weight can be found 
// in O(1) time.


//Maximum Cardinal Search
void GraphColoring::Graph::mcs() {

	map<string,vector<string> > temp_graph = graph;
	map< string,int> weight;
	queue<string> ordering;

	// Initially set the weight of each node to 0
	for(map< string, vector<string> >::iterator i = temp_graph.begin(); i != temp_graph.end(); i++) 
	{
		weight[(*i).first] = 0;
	}

	// Work through all the ndoes in the graph, choosing the node
	// with maximum weight, then add that node to the queue. Increase
	// the weight of the queued nodes neighbors by 1. Continue until
	// every node in the graph has been added to the queue
	for(int i = 0; i < graph.size(); i++) 
	{
		int max_weight = -1;
		string max_vertex = "";

		// Out of the remaining nodes, find the node with the highest weight
		for(map< string, vector<string> >:: iterator j = temp_graph.begin(); j != temp_graph.end(); j++) 
		{
			if(weight[(*j).first] > max_weight)
			{
				max_weight = weight[(*j).first];
				max_vertex = (*j).first;
			}
		}
		if(max_vertex == "")
		{
			cerr << "Error: Could not find a max weight node in the graph (reason unknown)" << endl;
			return;
		}

		// Add highest weight node to the queue and increment all of its
		// neighbors weights by 1
		ordering.push(max_vertex);
		for(unsigned j = 0; j<graph[max_vertex].size(); j++) 
		{
			weight[temp_graph[max_vertex][j]] += 1;
		}

		// Remove the maximum weight node from the graph so that it won't
		// be accidentally added again
		temp_graph.erase(max_vertex);
	}

	// Work through the queue in order and color each node
	while(!ordering.empty()) 
	{
		int color = 0;
		int done = 0;

		// Find the lowest possible coloring for this node between
		// its neighbors
		string min = ordering.front();
		while(!done) {
			done = 1;
			for(unsigned i=0; i<graph[min].size(); i++) 
			{
				if(coloring[graph[min][i]] == color) 
				{
					color += 1;
					done = 0;
				}
			}
		}
		coloring[min] = color;
		ordering.pop();
	}	
}
