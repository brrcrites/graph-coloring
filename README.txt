Graph Coloring library (Nodes are represented as strings)
	map<string,vector<string> >: A map of the node, to the list of nodes connected to it
	Graph(): Creates a new graph with no nodes/edges and uses default DSATUR coloring algorithm
	add_node(string new_node): Creates a node <new_node> in the graph with no edges
	add_edge(string source,string sink): Adds sink to the list of nodes connected to source
		:Adds source to the list of nodes connected to sink
		:If either source or sink don't exist in the graph, they will be added.
	color(int condition): Colors the graph using condition as a stopping condition (for specific algorithms)
		:Returns a map of nodes, to their colors (map<string,int>)
	verify(): verifies coloring of the graph

Available Algorithms: (See reference papers for descriptions)
	(set_algorithm(Algorithm new_algorithm))
	DSATUR (New Methods to Color the Vertices of a Graph - Brelaz et al.): kDSATUR
	Chordal (Register Allocation via Coloring of Chordal Graphs - Magno et al.): kChordal
	lmxRLF (Efficient Coloring of a Large Spectrum of Graphs - Kirovski et al.): kLMXRLF
	Hybrid Tabu (Custom, based on Efficient Coloring... - Kirovski et al.): kHybrid
	Hybrid DSATUR (Custom, based on Efficient Coloring... - Kirovski et al.): kHybridDSATUR
	
	[k-coloring] TabuCol (Using Tabu Search Techniques for Graph Coloring - Hertz et al.): tabucol

Text file input:
	parse_edge_list:
		c FILE: <filename.col>

		c SOURCE: <source>

		c DESCRIPTION: <description>

		p edge <|#nodes|> <|#edges|>
		e <source> <sink>

	parse_edge_matrix:
		<|#nodes|>
		<|#nodes|x|#nodes| matrix>

		1 indicates an edge between column node and row node
		0 indicates a lack of an edge

Visualizer output:
	write_graph(string graph_name): Will write a .dot file named graph_name.dot
	If no argument is provided, writes to colored_graph.dot. The .dot file has
	nodes colored appropriately and with the second line showing the color id
	in case the colors are too close.

Example usage: (Without text file input)
	//Create the graph
	Graph new_graph();
	//Add all of the nodes/edges
	string node1 = "node1";
	string node2 = "node2";
	new_graph.add_node(node1);
	new_graph.add_node(node2);
	new_graph.add_edge(node1,node2);
	...
	//Color the graph
	map<int,string> coloring = new_graph.color();

